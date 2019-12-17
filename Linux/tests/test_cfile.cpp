#include "catch2/catch.hpp"

//! include explicitely since we are not using the pre-compiled header for tests
//! may change this in the future
#include "stdafx.h" 

#include "cfile.h"

#include <boost/filesystem.hpp>

TEST_CASE("CFile operations", "[port]") {
    
    CStdioFile file ("/tmp/dummy.txt", CFile::modeWrite);
    file.WriteString("This is a single line file\n");
    file.Close();

    SECTION("Read dummy file") {
        
        CStdioFile file ("/tmp/dummy.txt", CFile::modeRead);

        CString content;
        file.ReadString(content);
        CHECK(content == "This is a single line file");

        file.Close();
    }

    SECTION("Tell and Seek in read mode") {

        CStdioFile file ("/tmp/dummy.txt", CFile::modeRead);

        CHECK(file.GetPosition() == 0);

        file.SeekToBegin();        
        CHECK(file.GetPosition() == 0);
        
        CHECK(file.Seek(0, CFile::end) == 27);
        CHECK(file.GetPosition() == 27);
        
        CHECK(file.Seek(10, CFile::begin) == 10);
        CHECK(file.GetPosition() == 10);
        
        CString content;
        file.ReadString(content);
        CHECK(content == "single line file");

        file.Close();
    }

    SECTION("Tell and Seek in write mode") {

        CStdioFile file ("/tmp/dummy.txt", CFile::modeWrite);

        CHECK(file.GetPosition() == 0);
        CHECK(file.Seek(10, CFile::begin) == 10);
        CHECK(file.GetPosition() == 10);

        file.WriteString("double single line file");
        CHECK(file.GetPosition() == 33);
        
        file.Close();
    }

    SECTION("Tell and Seek in read/write mode") {

        CStdioFile file ("/tmp/dummy.txt", CFile::modeReadWrite);

        CString content;
        file.ReadString(content);
        CHECK(content == "This is a single line file"); 

        CHECK(file.GetPosition() == 27);
        CHECK(file.Seek(0, CFile::end) == 27);
        CHECK(file.GetPosition() == 27);

        file.WriteString("This is a second line in the file\n");
        CHECK(file.GetPosition() == 61);

        file.Close();

        SECTION("Iterate on the file content") {
            
            CStdioFile file ("/tmp/dummy.txt", CFile::modeRead);

            std::vector<std::string> fileContent = {
                "This is a single line file",
                "This is a second line in the file"
            };

            size_t lineIt = 0;
            
            CString content;
            while(file.ReadString(content)) {

                CHECK(content == fileContent[lineIt]);
                lineIt++;
            }

            CHECK(lineIt == 2);

            file.Close();
        }

        SECTION("Get file status") {

            CStdioFile file;
            CFileException error;

            CHECK(file.Open("/tmp/dummy.txt", CFile::modeRead, &error));
            CHECK(file.GetFileName() == "/tmp/dummy.txt");

            CFileStatus status;
            file.GetStatus(status);
            CHECK(status.m_size == 61);
            
            file.Close();
        }

        SECTION("Get file exception") {

            CStdioFile file;
            CFileException error;

            CHECK_FALSE(file.Open("/tmp/dummy-not-exists.txt", CFile::modeRead, &error));
            CHECK(file.GetFileName() == "");

            char buffer[12];
            CHECK(error.GetErrorMessage(buffer, sizeof(buffer)));
            
            file.Close();
        }

        SECTION("Rename") {

            CStdioFile::Rename("/tmp/dummy.txt", "/tmp/dummy-rename.txt");

            CStdioFile file;
            CFileException error;

            CHECK_FALSE(file.Open("/tmp/dummy.txt", CFile::modeRead, &error));
            CHECK(file.GetFileName() == "");

            file.Close();

            CHECK(file.Open("/tmp/dummy-rename.txt", CFile::modeRead, &error));
            CHECK(file.GetFileName() == "/tmp/dummy-rename.txt");
            
            file.Close();
        }
    }
}

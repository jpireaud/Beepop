#include "cfile.h"

size_t CFile::begin = 0;

size_t CFile::Seek(size_t lOff, size_t nFrom)
{
    NOT_IMPLEMENTED(); 
    return 0;
}

void CFile::GetStatus(CFileStatus& status) const
{
    NOT_IMPLEMENTED(); 
}

CStdioFile::CStdioFile()
{
    NOT_IMPLEMENTED(); 
}
CStdioFile::CStdioFile(const char* lpszFileName, uint32_t nOpenFlags)
{
    NOT_IMPLEMENTED(); 
}

bool CStdioFile::Open(const char* lpszFileName, uint32_t nOpenFlags, CFileException* pError)
{
    NOT_IMPLEMENTED(); 
    return false;
}

bool CStdioFile::ReadString(CString& str)
{
    NOT_IMPLEMENTED(); 
    return false;
}
void CStdioFile::WriteString(const CString& str)
{
    NOT_IMPLEMENTED(); 
}

CString CStdioFile::GetFileName() const
{
    NOT_IMPLEMENTED(); 
    return CString();
}
void CStdioFile::Close()
{
    NOT_IMPLEMENTED(); 
}

void CStdioFile::Rename(const CString& original, const CString& target)
{
    NOT_IMPLEMENTED(); 
}

void CStdioFile::SeekToBegin()
{
    NOT_IMPLEMENTED(); 
}
    
size_t CStdioFile::GetPosition() const
{
    NOT_IMPLEMENTED();
    return 0;
}

CString CFileException::GetErrorMessage(char* buffer, uint32_t bufferSize) const
{
    NOT_IMPLEMENTED(); 
    return CString();
}

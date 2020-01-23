#include "cfile.h"

#include <boost/filesystem.hpp>
namespace bfs = boost::filesystem;

#include <iostream>

void CStdioFile::Rename(const CString& original, const CString& target)
{
    bfs::rename(original.ToString(), target.ToString());
}

CStdioFile::CStdioFile()
{
}

CStdioFile::CStdioFile(LPCTSTR lpszFileName, UINT nOpenFlags)
{
    m_fileStream.open(lpszFileName, static_cast<std::ios_base::openmode>(nOpenFlags));
    m_fileName = lpszFileName;
}

BOOL CStdioFile::Open(LPCTSTR lpszFileName, UINT nOpenFlags, CFileException* pError)
{
    try 
    {
        m_fileStream.exceptions(std::ifstream::failbit);
        m_fileStream.open(lpszFileName, static_cast<std::ios_base::openmode>(nOpenFlags));
        m_fileName = lpszFileName;
    }
    catch(const std::ios_base::failure& exception)
    {
        pError->SetErrorMessage(exception.what());
    }
    return m_fileStream.is_open();
}

BOOL CStdioFile::ReadString(CString& str)
{
    // JULIEN find a way to detect end of file
    std::string data;
    if (!m_fileStream.eof())
    {
        std::getline(m_fileStream, data);
    }
    str = data;
    return !m_fileStream.eof();
}

void CStdioFile::WriteString(LPCTSTR str)
{
    std::string lStr (str);
    m_fileStream.write(lStr.c_str(), lStr.length());
}

CString CStdioFile::GetFileName() const
{
    return CString(m_fileName);
}

void CStdioFile::Close()
{
    if (m_fileStream.is_open())
    {
        m_fileStream.close();
    }
    m_fileStream.clear();
}

void CStdioFile::SeekToBegin()
{
    m_fileStream.seekp(0);
}
    
ULONGLONG CStdioFile::Seek(LONGLONG lOff, UINT nFrom)
{
    m_fileStream.seekp(lOff, static_cast<std::ios_base::seekdir>(nFrom));
    return m_fileStream.tellp();
}

ULONGLONG CStdioFile::GetPosition()
{
    return m_fileStream.tellp();
}

void CStdioFile::GetStatus(CFileStatus& status) const
{
    // If we need more status information about the file than the size
    // auto fileStatus = bfs::status(m_fileName);
    
    status.m_size = bfs::file_size(m_fileName);
}

BOOL CFileException::GetErrorMessage(LPTSTR buffer, UINT bufferSize) const
{
    bool hasErrorMessage = !m_message.empty();
    if (hasErrorMessage)
    {
        snprintf(buffer, bufferSize, "%s", m_message.c_str());
    }
    return hasErrorMessage;
}

void CFileException::SetErrorMessage(const std::string& message)
{
    m_message = message;
}


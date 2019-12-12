#pragma once
#ifndef CFILE_CUSTOM_H
#define CFILE_CUSTOM_H

#include "cstring.h"

#include <fstream>

struct CFileStatus
{
	uint64_t m_size;
};

class CFile
{
public:

	// Flag values
	enum OpenFlags {
		modeRead = std::ios_base::in,
		modeWrite = std::ios_base::out,
		modeReadWrite = modeRead | modeWrite,
		modeCreate = 0, // default is C++
		modeNoTruncate = std::ios_base::app,
		typeText = 0, // used in derived classes (e.g. CStdioFile) only
		typeBinary = std::ios_base::binary, // used in derived classes (e.g. CStdioFile) only

		// shared access to file will be defaulted to C++ standard behavior which is shareDenyNone
		shareCompat = 0, 
		shareExclusive = 0,
		shareDenyWrite = 0,
		shareDenyRead = 0,
		shareDenyNone = 0
	};
    
    static size_t begin;

    virtual size_t Seek(size_t lOff, size_t nFrom);

	void GetStatus(CFileStatus& status) const;
};

class CFileException
{
public:
	CString GetErrorMessage(char* buffer, uint32_t bufferSize) const;
};

class CStdioFile : public CFile
{
public:
	CStdioFile();
	CStdioFile(const char* lpszFileName, uint32_t nOpenFlags);

	bool Open(const char* lpszFileName, uint32_t nOpenFlags, CFileException* pError);

	bool ReadString(CString& str);
	void WriteString(const CString& str);

	CString GetFileName() const;
	void Close();
	void Rename(const CString& original, const CString& target);

	void SeekToBegin();
		
	size_t GetPosition() const;
};

#endif // CFILE_CUSTOM_H

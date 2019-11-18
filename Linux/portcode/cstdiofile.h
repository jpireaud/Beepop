#pragma once
#ifndef CSTDIOFILE_CUSTOM_H
#define CSTDIOFILE_CUSTOM_H

#include "cfile.h"
#include "cobject.h"

#include <cstddef>

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

#endif // CSTDIOFILE_CUSTOM_H

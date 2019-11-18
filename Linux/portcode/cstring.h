#pragma once
#ifndef CSTRING_CUSTOM_H
#define CSTRING_CUSTOM_H

#include <string>

class CString
{
public:
    
	CString();
	CString(const std::string& cStr);
    CString(const char* cStr);

	bool operator==(const CString& str) const;
	bool operator==(const char* str) const;

	CString MakeLower() const;
	CString MakeUpper() const;

	operator const char* () const;

	// To be implemented...

	std::string ToString() const;

	CString& operator+=(const CString& str);
	CString& operator=(const CString& str);

	void Trim();
	void TrimLeft();
	void TrimRight();
	
	template<typename... Args>
	void Format(const char* format, Args... args);

	char& operator[](const size_t& index);
	const char& operator[](const size_t& index) const;

	int GetLength() const;

	int Find(char element) const;
	int Find(const char* element) const;

	void Replace(const CString& toReplace, const CString& with);

	int ReverseFind(char element) const;
	int ReverseFind(const char* element) const;

	CString Left(int position) const;
	CString Right(int position) const;
	CString Mid(int position) const;
	CString Mid(int start, int end) const;

	CString Tokenize(const char* delimiter, int startPosition) const;

	CString SpanExcluding(const char* str) const;

protected:

	std::string m_data;
}; 

CString operator+(const CString& str1, const CString& str2);
CString operator+(const char* str1, const CString& str2);

#endif // CSTRING_CUSTOM_H

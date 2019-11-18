#pragma once
#ifndef CARCHIVE_CUSTOM_H
#define CARCHIVE_CUSTOM_H

#include <cstdint>

class COleDateTime;
class CString;
class CTime;

class CArchive
{
public:

	bool IsLoading() const;
	bool IsStoring() const;

    // Storing

	void operator<<(const float& number);
	void operator<<(const double& number);
	void operator<<(const int32_t& number);
	void operator<<(const uint32_t& number);
	void operator<<(const COleDateTime& date);
	void operator<<(const CString& str);
	void operator<<(const CTime& time);

    // Loading

	void operator>>(float& number);
	void operator>>(double& number);
	void operator>>(int32_t& number);
	void operator>>(uint32_t& number);
	void operator>>(COleDateTime& date);
	void operator>>(CString& str);
	void operator>>(CTime& time);
};

#endif // CARCHIVE_CUSTOM_H

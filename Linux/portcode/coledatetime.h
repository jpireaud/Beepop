#pragma once
#ifndef COLEDATETIME_CUSTOM_H
#define COLEDATETIME_CUSTOM_H

#include "stdafx.h"

#define GetCurrentTime() GetTickCount()

class COleDateTimeSpan
{
public:
	COleDateTimeSpan();

	COleDateTimeSpan(double dblSpanSrc);

	COleDateTimeSpan(size_t lDays,
		int32_t nHours,
		int32_t nMins,
		int32_t nSecs);

	int32_t GetDays();

	bool operator!=(const COleDateTimeSpan& other) const;
};

class COleDateTime
{
public:
	enum DateTimeStatus
	{
		error = -1,
		valid = 0,
		invalid = 1,    // Invalid date (out of range, etc.)
		null = 2,       // Literally has no value
	};

	static COleDateTime GetTickCount();

	COleDateTime();

	COleDateTime(int32_t nYear,
		int32_t nMonth,
		int32_t nDay,
		int32_t nHour,
		int32_t nMin,
		int32_t nSec);

	int32_t GetMonth() const;
	int32_t GetDay() const;
	int32_t GetYear() const;
	int32_t GetHour() const;
	int32_t GetMinute() const;

	int32_t GetDayOfYear() const;

	DateTimeStatus GetStatus() const;

	bool operator < (const COleDateTime& other) const;
	bool operator > (const COleDateTime& other) const;
	bool operator >= (const COleDateTime& other) const;

	CString Format(const char* format) const;
	bool ParseDateTime(const CString& dateTimeStr);

	bool SetDate(int32_t year, int32_t month, int32_t day);

	bool GetAsSystemTime(SYSTEMTIME& time) const;

	COleDateTimeSpan& operator+=(const COleDateTimeSpan& span);
	COleDateTimeSpan& operator-=(const COleDateTimeSpan& span);

	COleDateTime operator+(const COleDateTimeSpan& span);
	COleDateTime operator-(const COleDateTimeSpan& span);

	COleDateTimeSpan operator+(const COleDateTime& date) const;
	COleDateTimeSpan operator-(const COleDateTime& date) const;
};


#endif // COLEDATETIME_CUSTOM_H

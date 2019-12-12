#include "coledatetime.h"

COleDateTimeSpan::COleDateTimeSpan()
{
    NOT_IMPLEMENTED();
}

COleDateTimeSpan::COleDateTimeSpan(double dblSpanSrc)
{
    NOT_IMPLEMENTED();
}

COleDateTimeSpan::COleDateTimeSpan(size_t lDays,
    int32_t nHours,
    int32_t nMins,
    int32_t nSecs)
{
    NOT_IMPLEMENTED();
}

int32_t COleDateTimeSpan::GetDays()
{
    NOT_IMPLEMENTED();
    return 0;
}

bool COleDateTimeSpan::operator!=(const COleDateTimeSpan& other) const
{
    NOT_IMPLEMENTED();
    return false;
}

/*static*/ COleDateTime COleDateTime::GetTickCount()
{
    COleDateTime time;
    NOT_IMPLEMENTED();
    return time;
}

COleDateTime::COleDateTime()
{
    NOT_IMPLEMENTED();
}

COleDateTime::COleDateTime(int32_t nYear,
    int32_t nMonth,
    int32_t nDay,
    int32_t nHour,
    int32_t nMin,
    int32_t nSec)
{
    NOT_IMPLEMENTED();
}

int32_t COleDateTime::GetMonth() const
{
    NOT_IMPLEMENTED();
}

int32_t COleDateTime::GetDay() const
{
    NOT_IMPLEMENTED();
    return 0;
}

int32_t COleDateTime::GetYear() const
{
    NOT_IMPLEMENTED();
    return 0;
}

int32_t COleDateTime::GetHour() const
{
    NOT_IMPLEMENTED();
    return 0;
}

int32_t COleDateTime::GetMinute() const
{
    NOT_IMPLEMENTED();
    return 0;
}

int32_t COleDateTime::GetDayOfYear() const
{
    NOT_IMPLEMENTED();
    return 0;
}

COleDateTime::DateTimeStatus COleDateTime::GetStatus() const
{
    NOT_IMPLEMENTED();
    return DateTimeStatus::error;
}

bool COleDateTime::operator < (const COleDateTime& other) const
{
    NOT_IMPLEMENTED();
    return false;
}

bool COleDateTime::operator > (const COleDateTime& other) const
{
    NOT_IMPLEMENTED();
    return false;
}

bool COleDateTime::operator >= (const COleDateTime& other) const
{
    NOT_IMPLEMENTED();
    return false;
}

CString COleDateTime::Format(const char* format) const
{
    NOT_IMPLEMENTED();
    return CString();
}

bool COleDateTime::ParseDateTime(const CString& dateTimeStr)
{
    NOT_IMPLEMENTED();
    return false;
}

bool COleDateTime::SetDate(int32_t year, int32_t month, int32_t day)
{
    NOT_IMPLEMENTED();
}

bool COleDateTime::GetAsSystemTime(SYSTEMTIME& time) const
{
    NOT_IMPLEMENTED();
    return false;
}

COleDateTimeSpan COleDateTime::operator+=(const COleDateTimeSpan& span)
{
    NOT_IMPLEMENTED();
    return COleDateTimeSpan();
}

COleDateTimeSpan COleDateTime::operator-=(const COleDateTimeSpan& span)
{
    NOT_IMPLEMENTED();
    return COleDateTimeSpan();
}

COleDateTime COleDateTime::operator+(const COleDateTimeSpan& span)
{
    NOT_IMPLEMENTED();
    return COleDateTime();
}

COleDateTime COleDateTime::operator-(const COleDateTimeSpan& span)
{
    NOT_IMPLEMENTED();
    return COleDateTime();
}

COleDateTimeSpan COleDateTime::operator+(const COleDateTime& date) const
{
    NOT_IMPLEMENTED();
    return COleDateTimeSpan();
}

COleDateTimeSpan COleDateTime::operator-(const COleDateTime& date) const
{
    NOT_IMPLEMENTED();
    return COleDateTimeSpan();
}

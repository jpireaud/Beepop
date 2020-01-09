#include "coledatetime.h"

#include <ctime>
#include <iomanip>
#include <sstream>

COleDateTimeSpan::COleDateTimeSpan()
{
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
: COleDateTime(1899, 12, 30, 0, 0, 0)
{
}

COleDateTime::COleDateTime(int32_t nYear,
    int32_t nMonth,
    int32_t nDay,
    int32_t nHour,
    int32_t nMin,
    int32_t nSec)
{
    const char* dateTimeFormat = "%Y-%m-%d %H:%M:%S";
    std::string dateTime = fmt::format("{}-{}-{} {}:{}:{}", nYear, nMonth, nDay, nHour, nMin, nSec);
    std::istringstream stream (dateTime);
    std::tm dt;
    stream >> std::get_time(&dt, dateTimeFormat);
    if (!stream.fail())
    {
        m_time_point = std::chrono::system_clock::from_time_t(std::mktime(&dt));
        m_status = valid;
    }
    else
    {
        m_status = error;
    }
}

int32_t COleDateTime::GetYear() const
{
    SYSTEMTIME st = {0};
    return GetAsSystemTime(st)? st.wYear : error;
}

int32_t COleDateTime::GetMonth() const
{
    SYSTEMTIME st = {0};
    return GetAsSystemTime(st)? st.wMonth : error;
}

int32_t COleDateTime::GetDay() const
{
    SYSTEMTIME st = {0};
    return GetAsSystemTime(st)? st.wDay : error;
}

int32_t COleDateTime::GetHour() const
{
    SYSTEMTIME st = {0};
    return GetAsSystemTime(st)? st.wHour : error;
}

int32_t COleDateTime::GetMinute() const
{
    SYSTEMTIME st = {0};
    return GetAsSystemTime(st)? st.wMinute : error;
}

int32_t COleDateTime::GetDayOfYear() const
{
    SYSTEMTIME st = {0};
    return GetAsSystemTime(st)? st.wDayOfWeek : error;
}

COleDateTime::DateTimeStatus COleDateTime::GetStatus() const
{
    return m_status;
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
	return false;
}

bool COleDateTime::GetAsSystemTime(SYSTEMTIME& time) const
{
    std::time_t l_time = std::chrono::system_clock::to_time_t(m_time_point);
    auto tm = std::localtime(&l_time);
    bool success = tm != nullptr;
    if(success)
    {
        time.wYear = tm->tm_year + 1900;
        time.wMonth = tm->tm_mon + 1;
        time.wDayOfWeek = tm->tm_wday;
        time.wDay = tm->tm_mday;
        time.wHour = tm->tm_hour;
        time.wMinute = tm->tm_min;
        time.wSecond = tm->tm_sec;
        auto tp_no_milliseconds = std::chrono::system_clock::from_time_t(l_time);
        time.wMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(m_time_point-tp_no_milliseconds).count();
    }
    return success;
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

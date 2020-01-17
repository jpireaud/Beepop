#include "coledatetime.h"

#include <ctime>
#include <iomanip>
#include <sstream>

/**
 * COleDateTime
 */

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
    std::string dateTime = fmt::format("{:0>4}-{:0>2}-{:0>2} {:0>2}:{:0>2}:{:0>2}", nYear, nMonth, nDay, nHour, nMin, nSec);
    std::istringstream stream (dateTime);
	std::tm dt = {0};
    dt.tm_isdst = -1; // needs to be set to unspecified otherwise random value is set
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

COleDateTime::COleDateTime(const std::chrono::system_clock::time_point& timePoint)
: m_time_point(timePoint)
, m_status(valid)
{
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
    UDATE date = {0};
    return GetAsUDATE(date)? date.wDayOfYear : error;
}

COleDateTime::DateTimeStatus COleDateTime::GetStatus() const
{
    return m_status;
}

bool COleDateTime::operator < (const COleDateTime& other) const
{
    return m_time_point < other.m_time_point;
}

bool COleDateTime::operator > (const COleDateTime& other) const
{
    return m_time_point > other.m_time_point;
}

bool COleDateTime::operator >= (const COleDateTime& other) const
{
    return m_time_point >= other.m_time_point;
}

bool COleDateTime::operator <= (const COleDateTime& other) const
{
    return m_time_point <= other.m_time_point;
}

CString COleDateTime::Format(const char* format) const
{
    std::time_t l_time = std::chrono::system_clock::to_time_t(m_time_point);
    auto tm = std::localtime(&l_time);
    std::stringstream ss;
    ss << std::put_time(tm, format);
	CString string(ss.str());
    return string;
}

bool COleDateTime::ParseDateTime(const CString& dateTimeStr)
{
    std::istringstream stream(dateTimeStr.ToString());
    std::tm dt = {0};

    const char *dateTimeFormat = "%m/%d/%Y %H:%M:%S";
    dt.tm_isdst = -1; // needs to be set to unspecified otherwise random value is set
    stream >> std::get_time(&dt, dateTimeFormat);
    if (!stream.fail())
    {
        m_time_point = std::chrono::system_clock::from_time_t(std::mktime(&dt));
        m_status = valid;
    }
    else
    {
        // let's try to parse only a date
        const char *dateFormat = "%m/%d/%Y";
        stream >> std::get_time(&dt, dateFormat);
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
    return m_status == valid;
}

bool COleDateTime::SetDate(int32_t year, int32_t month, int32_t day)
{
    const char* dateFormat = "%Y-%m-%d";
    std::string dateStr = fmt::format("{:0>4}-{:0>2}-{:0>2}", year, month, day);
    std::istringstream stream (dateStr);
    std::tm dt = {0};
    dt.tm_isdst = -1; // needs to be set to unspecified otherwise random value is set
    stream >> std::get_time(&dt, dateFormat);
    if (!stream.fail())
    {
        m_time_point = std::chrono::system_clock::from_time_t(std::mktime(&dt));
        m_status = valid;
    }
    else
    {
        m_status = error;
    }
    return m_status == valid;
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

bool COleDateTime::GetAsUDATE(UDATE& date) const
{
    std::time_t l_time = std::chrono::system_clock::to_time_t(m_time_point);
    auto tm = std::localtime(&l_time);
    bool success = tm != nullptr;
    if(success)
    {
        date.st.wYear = tm->tm_year + 1900;
        date.st.wMonth = tm->tm_mon + 1;
        date.st.wDayOfWeek = tm->tm_wday;
        date.wDayOfYear = tm->tm_yday + 1;
        date.st.wDay = tm->tm_mday;
        date.st.wHour = tm->tm_hour;
        date.st.wMinute = tm->tm_min;
        date.st.wSecond = tm->tm_sec;
        auto tp_no_milliseconds = std::chrono::system_clock::from_time_t(l_time);
        date.st.wMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(m_time_point-tp_no_milliseconds).count();
    }
    return success;
}

COleDateTime COleDateTime::operator+(const COleDateTimeSpan& span)
{
    auto time_point = m_time_point + span.m_span;
    return COleDateTime(time_point);
}

COleDateTime COleDateTime::operator-(const COleDateTimeSpan& span)
{
    auto time_point = m_time_point - span.m_span;
    return COleDateTime(time_point);
}

COleDateTimeSpan COleDateTime::operator-(const COleDateTime& date) const
{
    auto time_diff = m_time_point - date.m_time_point;    
    return COleDateTimeSpan(std::chrono::duration_cast<std::chrono::seconds>(time_diff));
}

/**
 * COleDateTimeSpan
 */

COleDateTimeSpan::COleDateTimeSpan()
: m_span(0)
{
}

COleDateTimeSpan::COleDateTimeSpan(double dblSpanSrc)
{
    std::chrono::duration<double, std::ratio<24*3600>> spanInDays (dblSpanSrc);
    m_span = std::chrono::duration_cast<std::chrono::seconds>(spanInDays);
}

COleDateTimeSpan::COleDateTimeSpan(size_t lDays,
    int32_t nHours,
    int32_t nMins,
    int32_t nSecs)
{
    std::chrono::duration<int, std::ratio<24*3600>> spanInDays (lDays);
    std::chrono::hours spanInHours (nHours);
    std::chrono::minutes spanInMin (nMins);
    std::chrono::seconds spanInSecs (lDays);
    m_span = spanInDays+spanInHours+spanInMin+spanInSecs;
}

COleDateTimeSpan::COleDateTimeSpan(const std::chrono::seconds& span)
: m_span(span)
{
}

int32_t COleDateTimeSpan::GetDays()
{
    return std::chrono::duration_cast<std::chrono::duration<int, std::ratio<24*3600>>>(m_span).count();
}

bool COleDateTimeSpan::operator!=(const COleDateTimeSpan& other) const
{
    return m_span != other.m_span;
}
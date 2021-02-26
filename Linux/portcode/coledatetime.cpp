#include "coledatetime.h"

#include <ctime>
#include <iomanip>
#include <sstream>

#include "Poco/Exception.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeParser.h"

/**
 * COleDateTime
 */

/*static*/ COleDateTime COleDateTime::GetTickCount()
{
    Poco::DateTime dateTime;
    COleDateTime date (dateTime);
    return date;
}

COleDateTime::COleDateTime(DATE dateSrc)
{
    // the integer part of dateSrc is the day offset
    double daysShift;
    double dayShift = std::modf(dateSrc, &daysShift);
    COleDateTimeSpan days (daysShift);
    COleDateTimeSpan day (std::abs(dayShift));
    // debug
    // std::cout << "days: " << daysShift << " and hours: " << dayShift << std::endl;
    COleDateTime origin;
    m_date = origin.m_date + days.m_span + day.m_span;
    m_status = valid;
}

COleDateTime::COleDateTime()
: m_date(1899, 12, 30, 0, 0, 0)
{
    m_status = valid;
}

COleDateTime::COleDateTime(const Poco::DateTime& date)
: m_date(date)
{
    m_status = valid;
}

COleDateTime::COleDateTime(int32_t nYear,
    int32_t nMonth,
    int32_t nDay,
    int32_t nHour,
    int32_t nMin,
    int32_t nSec)
{
    try
    {
       m_date = Poco::DateTime(nYear, nMonth, nDay, nHour, nMin, nSec);
       m_status = valid;
    }
    catch(std::exception& exception)
    {
        std::cerr << exception.what() << std::endl; 
        m_status = invalid;
    }
}

int32_t COleDateTime::GetYear() const
{
    return m_date.year();
}

int32_t COleDateTime::GetMonth() const
{
    return m_date.month();
}

int32_t COleDateTime::GetDay() const
{
    return m_date.day();
}

int32_t COleDateTime::GetHour() const
{
    return m_date.hour();
}

int32_t COleDateTime::GetMinute() const
{
    return m_date.minute();
}

int32_t COleDateTime::GetDayOfYear() const
{
    return m_date.dayOfYear();
}

int32_t COleDateTime::GetJulianDay() const
{
    return GetDayOfYear();
}

COleDateTime::DateTimeStatus COleDateTime::GetStatus() const
{
    return m_status;
}

bool COleDateTime::operator < (const COleDateTime& other) const
{
    return m_date < other.m_date;
}

bool COleDateTime::operator > (const COleDateTime& other) const
{
    return m_date > other.m_date;
}

bool COleDateTime::operator >= (const COleDateTime& other) const
{
    return m_date >= other.m_date;
}

bool COleDateTime::operator <= (const COleDateTime& other) const
{
    return m_date <= other.m_date;
}

CString COleDateTime::Format(const char* format) const
{
    return Poco::DateTimeFormatter::format(m_date, format);
}

bool COleDateTime::ParseDateTime(const CString& dateTimeStr, DWORD dwFlags)
{
    try
    {
        bool success = false;
        int timeZoneDifferential = 0;
        if (dwFlags == VAR_DATEVALUEONLY)
        {
            // let's try to parse only a date
            const char* dateFormat = "%m/%d/%Y";
            m_date = Poco::DateTimeParser::parse(dateFormat, dateTimeStr.ToString(), timeZoneDifferential);
            success = true;
        }
        else if (dwFlags == VAR_TIMEVALUEONLY)
        {
            // let's try to parse only a time
            const char* timeFormat = "%H:%M:%S";
            m_date = Poco::DateTimeParser::parse(timeFormat, dateTimeStr.ToString(), timeZoneDifferential);
            success = true;
        }
        else 
        {
            // Handles the 3 supported formats if the dwFlags is not specified
            const std::map<size_t, std::string> supportedDateTimeFormatsLengths = {
                {strlen("00/00/0000 00:00:00"), "%m/%d/%Y %H:%M:%S"},
                {strlen("00/00/0000"), "%m/%d/%Y"},
                {strlen("00:00:00"), "%H:%M:%S"}
            };
            for(auto formatIt=supportedDateTimeFormatsLengths.begin(); !success && formatIt!=supportedDateTimeFormatsLengths.end(); formatIt++) 
            {
                if (formatIt->first == dateTimeStr.GetLength()) 
                {
                    success = Poco::DateTimeParser::tryParse(formatIt->second, dateTimeStr.ToString(), m_date, timeZoneDifferential);
                }
            }
        }
        // debug 
        // std::cout << "parsing: " << dateTimeStr << " resulted in " << Poco::DateTimeFormatter::format(m_date, "%m/%d/%Y %H:%M:%S") << " with success set to " << std::boolalpha << success << std::endl;
        m_date.makeUTC(timeZoneDifferential);
        m_status = success? valid : error;
    }
    catch(std::exception& exception)
    {
        std::cerr << exception.what() << std::endl;
        m_status = error;
    }
    return m_status == valid;
}

int COleDateTime::SetDate(int32_t year, int32_t month, int32_t day)
{
    try
    {
        m_date.assign(year, month, day);
        m_status = valid;
    }
    catch(std::exception& exception)
    {
        std::cerr << exception.what() << std::endl;
        m_status = error;
    }
    return !(m_status == valid);
}

bool COleDateTime::GetAsSystemTime(SYSTEMTIME& time) const
{
    time.wYear = m_date.year();
    time.wMonth = m_date.month();
    time.wDayOfWeek = m_date.dayOfWeek();
    time.wDay = m_date.day();
    time.wHour = m_date.hour();
    time.wMinute = m_date.minute();
    time.wSecond = m_date.second();
    time.wMilliseconds = m_date.millisecond();
    return true;
}

bool COleDateTime::GetAsUDATE(UDATE& date) const
{
    date.st.wYear = m_date.year();
    date.st.wMonth = m_date.month();
    date.st.wDayOfWeek = m_date.dayOfWeek();
    date.wDayOfYear = m_date.dayOfYear();
    date.st.wDay = m_date.day();
    date.st.wHour = m_date.hour();
    date.st.wMinute = m_date.minute();
    date.st.wSecond = m_date.second();
    date.st.wMilliseconds = m_date.millisecond();
    return true;
}

bool COleDateTime::GetAsDATE(DATE& date) const
{
    COleDateTime origin;
    COleDateTimeSpan timespan = m_date - origin.m_date;
    double days = (double)timespan.m_span.days();
    double daySpan = (timespan.m_span.hours() + timespan.m_span.minutes() / 60.0 + timespan.m_span.seconds() / 3600.0) / 24.0;
    date = days + daySpan;
    // debug
    // std::cout << "as DATE with days " << timespan.m_span.days() << " hours " << timespan.m_span.hours() << " minutes " << timespan.m_span.minutes() << " seconds " << timespan.m_span.seconds() << std::endl;
    // std::cout << "as DATE result " << date << " days " << days << " daySpan " << daySpan << std::endl;
    if (date < 0.0)
    {
        daySpan = std::modf(date, &days);
        date = (days<0.0)? days:-1.0 - (1.0 + daySpan);
        // std::cout << "adjusted result " << date << " days " << days << " daySpan " << daySpan << std::endl;
    }
    return true;
}

COleDateTime COleDateTime::operator+(const COleDateTimeSpan& span) const
{
    auto date = m_date + span.m_span;
    return COleDateTime(date);
}

COleDateTime COleDateTime::operator-(const COleDateTimeSpan& span) const
{
    auto date = m_date - span.m_span;
    return COleDateTime(date);
}

COleDateTime& COleDateTime::operator+=(const COleDateTimeSpan& span)
{
    m_date += span.m_span;
    return *this;
}

COleDateTime& COleDateTime::operator-=(const COleDateTimeSpan& span)
{
    m_date -= span.m_span;
    return *this;
}

COleDateTimeSpan COleDateTime::operator-(const COleDateTime& date) const
{
    auto span = m_date - date.m_date;
    return COleDateTimeSpan(span);
}

/**
 * COleDateTimeSpan
 */

COleDateTimeSpan::COleDateTimeSpan()
: m_span()
{
}

COleDateTimeSpan::COleDateTimeSpan(const Poco::Timespan& span)
: m_span(span)
{
}

COleDateTimeSpan::COleDateTimeSpan(double dblSpanSrc)
{
    // convert dblSpanSrc from days to seconds and extract microseconds
    double dblSeconds = dblSpanSrc * 24 * 60 * 60;
    double seconds, microseconds;
    microseconds = modf(dblSeconds, &seconds) * 1000;
    // debug
    // std::cout << dblSpanSrc << " in secs " << dblSeconds << " seconds: " << seconds << " micro: " << microseconds << std::endl;
    m_span.assign(long(seconds), long(microseconds));
}

COleDateTimeSpan::COleDateTimeSpan(size_t lDays,
    int32_t nHours,
    int32_t nMins,
    int32_t nSecs)
{
    m_span.assign(lDays, nHours, nMins, nSecs, 0);
}

int32_t COleDateTimeSpan::GetDays()
{
    return m_span.days();
}

bool COleDateTimeSpan::operator!=(const COleDateTimeSpan& other) const
{
    return m_span != other.m_span;
}
#include "ctime.h"

#include <ctime>

CTime::CTime()
: m_timestamp()
{
}

CTime::CTime(const SYSTEMTIME& time)
{
    COleDateTime dateTime (time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
    m_timestamp = dateTime.Timestamp();
}

COleDateTime CTime::GetTime() const
{
    COleDateTime dateTime (m_timestamp);
    return dateTime;
}

void CTime::FromTimeT(const time_t& time)
{
    m_timestamp = Poco::Timestamp::fromEpochTime(time);
}

time_t CTime::GetAsTimeT() const
{
    return m_timestamp.epochTime();
}

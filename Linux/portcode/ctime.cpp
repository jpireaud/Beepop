#include "ctime.h"


CTime::CTime()
{

}

CTime::CTime(const time_t& time)
{

}

COleDateTime CTime::GetTime() const
{
    COleDateTime time;
    return time;
}

bool CTime::GetAsSystemTime(time_t& time) const
{
    return false;
}

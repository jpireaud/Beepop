#pragma once
#ifndef CTIME_CUSTOM_H
#define CTIME_CUSTOM_H

#include "coledatetime.h"

#include <chrono>

class CTime
{
public:
	CTime();
	CTime(const SYSTEMTIME& time);

	COleDateTime GetTime() const;

protected:

	// here we use a time point to get milliseconds precision
	std::chrono::system_clock::time_point m_time_point;
};

#endif // CTIME_CUSTOM_H

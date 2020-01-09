#pragma once
#ifndef CTIME_CUSTOM_H
#define CTIME_CUSTOM_H

#include "coledatetime.h"

#include <ctime>

class CTime
{
public:
	CTime();
	CTime(const SYSTEMTIME& time);

	COleDateTime GetTime() const;

	bool GetAsSystemTime(time_t& time) const;
};

#endif // CTIME_CUSTOM_H

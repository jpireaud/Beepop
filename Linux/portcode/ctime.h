#pragma once
#ifndef CTIME_CUSTOM_H
#define CTIME_CUSTOM_H

#include "coledatetime.h"

#include "Poco/Timestamp.h"

/**
 * Only supports the necessary interface for the good behavior of VarroaPop
 */
class CTime
{
public:
	CTime();
	CTime(const SYSTEMTIME& time);

	COleDateTime GetTime() const;

	void FromTimeT(const time_t& time);
	time_t GetAsTimeT() const;

protected:

	// here we use a time point to get milliseconds precision
	Poco::Timestamp m_timestamp;
};

#endif // CTIME_CUSTOM_H

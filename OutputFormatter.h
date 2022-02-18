#pragma once

#include "stdafx.h"

class CEvent;
class CColony;
class CVarroaPopSession;
/**
 * Pure virtual function that defines interface of an output formatter
 *
 * This
 */
class COutputFormatter
{
public:
	COutputFormatter(CVarroaPopSession& session);

	virtual ~COutputFormatter();

	virtual void Init(CColony& colony) = 0;

	virtual void Record(CColony& colony, CEvent& event) = 0;

protected:
	CVarroaPopSession& m_Session;
};

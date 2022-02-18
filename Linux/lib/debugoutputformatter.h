#pragma once

#include "customoutputformatter.h"

#include <sstream>

/**
 * Output formatter that will only output the colony size
 */
class DebugOutputFormatter : public CustomOutputFormatter
{
public:
	DebugOutputFormatter(CVarroaPopSession& session);

	virtual ~DebugOutputFormatter();

	virtual void Init(CColony& colony);

	virtual void Record(CColony& colony, CEvent& event);
};

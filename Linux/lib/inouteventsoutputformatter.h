#pragma once

#include "customoutputformatter.h"

#include <sstream>

/**
 * Output formatter that will only output the colony size
 */
class InOutEventsOutputFormatter : public CustomOutputFormatter
{
public:
	InOutEventsOutputFormatter(CVarroaPopSession& session);

	virtual ~InOutEventsOutputFormatter();

	virtual void Init(CColony& colony);

	virtual void Record(CColony& colony, CEvent& event);
};

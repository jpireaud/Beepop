#pragma once

#include "customoutputformatter.h"

#include <sstream>

/**
 * Output formatter that will only output the colony size
 */
class ColonySizeOutputFormatter : public CustomOutputFormatter
{
public:
	ColonySizeOutputFormatter(CVarroaPopSession& session);

	virtual ~ColonySizeOutputFormatter();

	virtual void Init(CColony& colony);

	virtual void Record(CColony& colony, CEvent& event);
};

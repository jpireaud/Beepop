#pragma once

#include "customoutputformatter.h"

#include <sstream>

/**
 * Output formatter that will only output the colony size
 */
class CColonySizeOutputFormatter : public CustomOutputFormatter
{
public:
	CColonySizeOutputFormatter(CVarroaPopSession& session);

	virtual ~CColonySizeOutputFormatter();

	virtual void Init(CColony& colony);

	virtual void Record(CColony& colony, CEvent& event);
};

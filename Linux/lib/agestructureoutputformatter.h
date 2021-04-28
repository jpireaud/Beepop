#pragma once

#include "customoutputformatter.h"

#include <sstream>

/**
 * Output formatter that will only output the colony size
 */
class AgeStructureOutputFormatter : public CustomOutputFormatter
{
public:
	AgeStructureOutputFormatter(CVarroaPopSession& session);

	virtual ~AgeStructureOutputFormatter();

	virtual void Init(CColony& colony);

	virtual void Record(CColony& colony, CEvent& event);
};

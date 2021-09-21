#pragma once

#include "customoutputformatter.h"

#include <limits>
#include <queue>
#include <sstream>

/**
 * Output formatter that will only output the colony size
 */
class MapDataOutputFormatter : public CustomOutputFormatter
{
public:
	MapDataOutputFormatter(CVarroaPopSession& session);

	virtual ~MapDataOutputFormatter();

	virtual void Init(CColony& colony);

	virtual void Record(CColony& colony, CEvent& event);

protected:
	struct MapDataItem
	{
		MapDataItem() {}

		int m_daysBellow7500 = 0;
		int m_daysBellow10000 = 0;
		int m_minColonySize = std::numeric_limits<int>::max();
	};
	MapDataItem m_item;

	// here we need this attribute outside the MapDataItem since it's value
	// is updated accross years
	bool            m_recordDeadForagers = false;
	int             m_deadForagersOverWinter = 0;
	std::queue<int> m_deadForagersOverWinterCounts;
};

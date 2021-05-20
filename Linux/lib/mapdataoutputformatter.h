#pragma once

#include "customoutputformatter.h"

#include <sstream>
#include <limits>

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
        
        int m_daysBellow5000 = 0;
        int m_minColonySize = std::numeric_limits<int>::max();
    };
    MapDataItem m_item;
};

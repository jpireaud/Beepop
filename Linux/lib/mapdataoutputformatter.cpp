
#include "mapdataoutputformatter.h"

#include "colony.h"
#include "weatherevents.h"

MapDataOutputFormatter::MapDataOutputFormatter(CVarroaPopSession& session) : CustomOutputFormatter(session)
{
}

MapDataOutputFormatter::~MapDataOutputFormatter()
{
}

void MapDataOutputFormatter::Init(CColony& colony)
{
	m_writer.write("Year", "Days Bellow 5000", "Min Colony Size");
}

void MapDataOutputFormatter::Record(CColony& colony, CEvent& event)
{
    // gather data
    const int colonySize = colony.GetColonySize();
    if (colonySize < 5000)
    {
        m_item.m_daysBellow5000+=1;
    }
    m_item.m_minColonySize = std::min(m_item.m_minColonySize, colonySize);
    
    if (event.GetTime().GetMonth() == 12 && event.GetTime().GetDay() == 31)
    {
        // output current data
        m_writer.write(event.GetTime().GetYear(), m_item.m_daysBellow5000, m_item.m_minColonySize);
        
        // reset data item
        m_item = MapDataItem();
    }
}

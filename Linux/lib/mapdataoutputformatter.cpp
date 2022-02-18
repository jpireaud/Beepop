
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
	m_writer.write("Year", "Dead Foragers Over Winter", "Days Bellow 7500", "Days Bellow 10000", "Min Colony Size");
}

void MapDataOutputFormatter::Record(CColony& colony, CEvent& event)
{
	// gather data
	const int colonySize = colony.GetColonySize();
	if (colonySize < 7500)
	{
		m_item.m_daysBellow7500 += 1;
	}
	if (colonySize < 10000)
	{
		m_item.m_daysBellow10000 += 1;
	}
	m_item.m_minColonySize = std::min(m_item.m_minColonySize, colonySize);

	const auto currentMonth = event.GetTime().GetMonth();
	const auto currentDay = event.GetTime().GetDay();

    // activate dead foragers counting
	if (!m_recordDeadForagers && currentMonth == 11 && currentDay == 1)
	{
		m_recordDeadForagers = true;
	}

    // count dead foragers
	if (m_recordDeadForagers)
	{
		m_deadForagersOverWinter += colony.m_InOutEvent.m_DeadForagers;

        // end foragers counting
        if (currentMonth == 3 && currentDay == 1)
        {
            m_recordDeadForagers = false;
            m_deadForagersOverWinterCounts.push(m_deadForagersOverWinter);
            m_deadForagersOverWinter = 0;
        }
	}

	if (currentMonth == 12 && currentDay == 31)
	{
		// get the last dead foragers count
		int deadForagers = 0;
		if (!m_deadForagersOverWinterCounts.empty())
		{
            deadForagers = m_deadForagersOverWinterCounts.front();
			m_deadForagersOverWinterCounts.pop();
		}

		// output current data
		m_writer.write(
		    event.GetTime().GetYear(), deadForagers, m_item.m_daysBellow7500, m_item.m_daysBellow10000,
		    m_item.m_minColonySize);

		// reset data item
		m_item = MapDataItem();
	}
}

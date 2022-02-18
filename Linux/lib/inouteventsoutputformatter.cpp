#include "inouteventsoutputformatter.h"

#include "colony.h"
#include "globaloptions.h"
#include "weatherevents.h"

#include <map>
#include <vector>

InOutEventsOutputFormatter::InOutEventsOutputFormatter(CVarroaPopSession& session) : CustomOutputFormatter(session)
{
}

InOutEventsOutputFormatter::~InOutEventsOutputFormatter()
{
}

void InOutEventsOutputFormatter::Init(CColony& colony)
{
    const std::vector<std::string> headers = {
        "Date",
//        "NewDEggs",
//        "DEggsToLarv",
//        "DLarvToBrood",
//        "DBroodToAdult",
//        "DeadDAdults",
        "NewWEggs",
        "WEggsToLarv",
        "WLarvToBrood",
        "WBroodToAdult",
        "WAdultToForagers",
        "DeadForagers",
        "ForagersKilledByPesticide",
        "WinterMortalityForagersLoss",
        "ForageInc",
        "ForageDay",
        "MinTemp",
        "MaxTemp",
        "FlightHours",
        "DaylightHours",
        "Solstice",
        "AdultsBoxcars",
        "AdultsMinAge",
        "AdultsMaxAge",
        "ForagersBoxcars",
        "ForagersMinAge",
        "ForagersMaxAge"};
	bool comma = false;
	for (auto header : headers)
	{
		if (comma) m_stream << ",";
		m_stream << header;
		comma = true;
	}
	m_stream << std::endl;
}

struct BeesStats
{
    INT_PTR count = 0;
    double minAge = 0.0;
    double maxAge = 0.0;
    BeesStats(CAdultlist& list)
    {
        count = list.GetCount();
        POSITION begin = list.GetHeadPosition();
        if (begin != nullptr)
        {
            minAge = ((CAdult*)list.GetAt(begin))->GetCurrentAge();
        }
        POSITION end = list.GetTailPosition();
        if (end != nullptr)
        {
            maxAge = ((CAdult*)list.GetAt(end))->GetCurrentAge();
        }
    }
};

std::ostream& operator<<(std::ostream& ostream, const BeesStats& stats)
{
    ostream << stats.count << "," << stats.minAge << "," << stats.maxAge;
    return ostream;
}

void InOutEventsOutputFormatter::Record(CColony& colony, CEvent& event)
{
	// clang-format off
	m_stream << event.GetDateStg("%m/%d/%Y") << ",";
//	m_stream << colony.m_InOutEvent.m_NewDEggs << ",";
//	m_stream << colony.m_InOutEvent.m_DEggsToLarv << ",";
//	m_stream << colony.m_InOutEvent.m_DLarvToBrood << ",";
//	m_stream << colony.m_InOutEvent.m_DBroodToAdult << ",";
//	m_stream << colony.m_InOutEvent.m_DeadDAdults << ",";
	m_stream << colony.m_InOutEvent.m_NewWEggs << ",";
	m_stream << colony.m_InOutEvent.m_WEggsToLarv << ",";
	m_stream << colony.m_InOutEvent.m_WLarvToBrood << ",";
	m_stream << colony.m_InOutEvent.m_WBroodToAdult << ",";
	m_stream << colony.m_InOutEvent.m_WAdultToForagers << ",";
	m_stream << colony.m_InOutEvent.m_DeadForagers << ",";
	m_stream << colony.m_InOutEvent.m_ForagersKilledByPesticide << ",";
    m_stream << colony.m_InOutEvent.m_WinterMortalityForagersLoss << ",";
    m_stream << event.GetForageInc() << ",";
    m_stream << event.IsForageDay() << ",";
    m_stream << event.GetMinTemp() << ",";
    m_stream << event.GetMaxTemp() << ",";
    m_stream << event.GetFlightHours() << ",";
    m_stream << event.GetDaylightHours() << ",";
    m_stream << event.GetSolstice() << ",";

    BeesStats adults (*colony.Wadl().get());
    m_stream << adults << ",";
    BeesStats foragers (*colony.Foragers().get());
    m_stream << foragers;
	m_stream << std::endl;
	// clang-format on
}

#include "debugoutputformatter.h"

#include "colony.h"
#include "globaloptions.h"
#include "weatherevents.h"

struct Helper
{
	int m_numberOfAdultsBoxcars = 3;

	std::vector<std::string> makeAdultsBoxcarsStrings()
	{
		std::vector<std::string> strings;
		for (int i = 0; i < m_numberOfAdultsBoxcars; i++)
		{
			strings.push_back("N-" + std::to_string(i + 1));
		}
		return strings;
	}

	std::vector<std::string> getValues(CAdultlist* list, std::function<std::string(CAdult* adult)> getter)
	{
		;
		std::vector<std::string> values;
		if (list == nullptr)
		{
			values.insert(values.begin(), m_numberOfAdultsBoxcars, "NA");
		}
        else
        {
            POSITION pos = list->GetTailPosition();
            while (pos != nullptr && values.size() < m_numberOfAdultsBoxcars)
            {
                auto item = (CAdult*)list->GetPrev(pos);
                values.push_back(getter(item));
            }
            values.insert(values.end(), m_numberOfAdultsBoxcars - values.size(), "NA");
        }
		return values;
	}
};

static Helper& Helper()
{
	static struct Helper sInstance;
	return sInstance;
}

DebugOutputFormatter::DebugOutputFormatter(CVarroaPopSession& session) : CustomOutputFormatter(session)
{
}

DebugOutputFormatter::~DebugOutputFormatter()
{
}

void DebugOutputFormatter::Init(CColony& colony)
{
	static const auto adultsStrings = Helper().makeAdultsBoxcarsStrings();
	m_stream << "Date, Forage Inc, Brood to Adults, Adults to Foragers, Dead Foragers";
	if (GlobalOptions::Get().ShouldAdultsAgeBasedOnForageInc())
	{
		std::for_each(adultsStrings.rbegin(), adultsStrings.rend(), [this](const std::string& adultString) {
			m_stream << ", Pending Adult " + adultString;
		});
	}
	else if (GlobalOptions::Get().ShouldAdultsAndForagersAgeBasedOnForageInc())
	{
		std::for_each(adultsStrings.rbegin(), adultsStrings.rend(), [this](const std::string& adultString) {
			m_stream << ", Adult " + adultString;
		});
	}
	m_stream << std::endl;
}

void DebugOutputFormatter::Record(CColony& colony, CEvent& event)
{
	static const auto adultsStrings = Helper().makeAdultsBoxcarsStrings();
	m_stream << event.GetDateStg("%m/%d/%Y");
	m_stream << "," << event.GetForageInc() * (event.IsForageDay() ? 1.0 : 0.0);
	m_stream << "," << colony.m_InOutEvent.m_WBroodToAdult;
	m_stream << "," << colony.m_InOutEvent.m_WAdultToForagers;
	m_stream << "," << colony.m_InOutEvent.m_DeadForagers;
	if (GlobalOptions::Get().ShouldAdultsAgeBasedOnForageInc())
	{
		auto pendingAdults = colony.Wadl()->GetPendingAdults();
		auto values = Helper().getValues(pendingAdults, [](CAdult* adult) {
		  return std::to_string(adult->GetForageInc());
		});
		std::for_each(values.rbegin(), values.rend(), [this](const std::string& value) { m_stream << ", " + value; });
	}
	else if (GlobalOptions::Get().ShouldAdultsAndForagersAgeBasedOnForageInc())
	{
		auto&    adults = colony.Wadl();
        auto values = Helper().getValues(adults.get(), [](CAdult* adult) {
          return std::to_string(adult->GetCurrentAge());
        });
        std::for_each(values.rbegin(), values.rend(), [this](const std::string& value) { m_stream << ", " + value; });
	}

	m_stream << std::endl;
}

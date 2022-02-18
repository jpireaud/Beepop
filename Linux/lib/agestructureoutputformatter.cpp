#include "agestructureoutputformatter.h"

#include "colony.h"
#include "globaloptions.h"
#include "weatherevents.h"

#define AGE_STRUCTURE_ONE_COLUMN_FOR_EACH_BOX_CARD false
#define AGE_STRUCTURE_AGGREGATED_COLUMNS true

AgeStructureOutputFormatter::AgeStructureOutputFormatter(CVarroaPopSession& session) : CustomOutputFormatter(session)
{
}

AgeStructureOutputFormatter::~AgeStructureOutputFormatter()
{
}

void AgeStructureOutputFormatter::Init(CColony& colony)
{
#if AGE_STRUCTURE_ONE_COLUMN_FOR_EACH_BOX_CARD
	m_stream << "Date";
	for (int i = 0; i < EGGLIFE; i++)
		m_stream << ","
		         << "DEgg_" << i;
	for (int i = 0; i < EGGLIFE; i++)
		m_stream << ","
		         << "WEgg_" << i;
	for (int i = 0; i < DLARVLIFE; i++)
		m_stream << ","
		         << "DLarv_" << i;
	for (int i = 0; i < WLARVLIFE; i++)
		m_stream << ","
		         << "WLarv_" << i;
	for (int i = 0; i < DBROODLIFE; i++)
		m_stream << ","
		         << "DBrood_" << i;
	for (int i = 0; i < WBROODLIFE; i++)
		m_stream << ","
		         << "WBrood_" << i;
	for (int i = 0; i < DADLLIFE; i++)
		m_stream << ","
		         << "DAdl_" << i;
	for (int i = 0; i < WADLLIFE; i++)
		m_stream << ","
		         << "WAdl_" << i;
	m_stream << ","
	         << "PF";
	for (int i = 0; i < colony.m_CurrentForagerLifespan; i++)
		m_stream << ","
		         << "F_" << i;
	m_stream << std::endl;
#endif // AGE_STRUCTURE_ONE_COLUMN_FOR_EACH_BOX_CARD
#if AGE_STRUCTURE_AGGREGATED_COLUMNS
	m_stream << "Date, Broods, Nurse Bees, House Bees, Foragers, Colony Size, Foragers SOD, Foragers EOD";
	m_stream << std::endl;
#endif
}
#if AGE_STRUCTURE_ONE_COLUMN_FOR_EACH_BOX_CARD
template <typename Type, typename Container> void OutputAgeStructure(Container& data, std::stringstream& stream)
{
	POSITION  pos = data.GetHeadPosition();
	const int count = data.GetCount();
	for (int i = 0; i < count; i++)
	{
		Type* obj = (Type*)data.GetNext(pos);
		stream << "," << (obj->IsAlive() ? obj->number : 0);
	}
}

void AgeStructureOutputFormatter::Record(CColony& colony, CEvent& event)
{
	m_stream << event.GetDateStg("%m/%d/%Y");
	OutputAgeStructure<CEgg>(colony.Deggs, m_stream);
	OutputAgeStructure<CEgg>(colony.Weggs, m_stream);
	OutputAgeStructure<CLarva>(colony.Dlarv, m_stream);
	OutputAgeStructure<CLarva>(colony.Wlarv, m_stream);
	OutputAgeStructure<CBrood>(colony.CapDrn, m_stream);
	OutputAgeStructure<CBrood>(colony.CapWkr, m_stream);
	OutputAgeStructure<CAdult>(colony.Dadl, m_stream);
	OutputAgeStructure<CAdult>(colony.Wadl, m_stream);
	m_stream << "," << colony.Foragers()->GetPendingQuantity();
	OutputAgeStructure<CAdult>(colony.foragers, m_stream);
	m_stream << std::endl;
}
#endif // AGE_STRUCTURE_ONE_COLUMN_FOR_EACH_BOX_CARD

#if AGE_STRUCTURE_AGGREGATED_COLUMNS
void AgeStructureOutputFormatter::Record(CColony& colony, CEvent& event)
{
	m_stream << event.GetDateStg("%m/%d/%Y");
	m_stream << "," << colony.Weggs.GetQuantity() + colony.Wlarv.GetQuantity() + colony.CapWkr.GetQuantity();
	int  nurseBees = 0;
	int  houseBees = 0;
	auto adultList = dynamic_cast<CForageBasedAgingAdultList*>(colony.Wadl().get());
	if (adultList)
	{
		POSITION pos = adultList->GetHeadPosition();
		while (pos != nullptr)
		{
			auto adult = (CAdult*)adultList->GetNext(pos);
			if (adult->IsAlive())
			{
				if (adult->GetCurrentAge() < 8.0)
				{
					nurseBees += adult->GetNumber();
				}
				else
				{
					houseBees += adult->GetNumber();
				}
			}
		}
	}
	else
	{
		int      index = 0;
		POSITION pos = colony.Wadl()->GetHeadPosition();
		while (pos != nullptr)
		{
			auto adult = (CAdult*)colony.Wadl()->GetNext(pos);
			if (adult->IsAlive())
			{
				if (index < 8)
				{
					nurseBees += adult->GetNumber();
				}
				else
				{
					houseBees += adult->GetNumber();
				}
			}
			index++;
		}

		// Add pending adults if needed
		if (GlobalOptions::Get().ShouldAdultsAgeBasedOnForageInc())
		{
			const auto pendingAdults = colony.Wadl()->GetPendingAdults();
			if (pendingAdults)
			{
				POSITION pos = pendingAdults->GetHeadPosition();
				while (pos != nullptr)
				{
					auto adult = (CAdult*)pendingAdults->GetNext(pos);
					nurseBees += adult->GetNumber();
				}
			}
		}
	}
	m_stream << "," << nurseBees;
	m_stream << "," << houseBees;
	m_stream << "," << colony.Foragers()->GetQuantity();
	m_stream << "," << colony.GetColonySize();
	m_stream << "," << colony.m_InOutEvent.m_ForagersAtTheBeginningOfTheDay;
	m_stream << "," << colony.m_InOutEvent.m_DeadForagers;
	m_stream << std::endl;
}
#endif // AGE_STRUCTURE_AGGREGATED_COLUMNS

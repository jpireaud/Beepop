#include "agestructureoutputformatter.h"

#include "colony.h"
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
	m_stream << "Date, Eggs, Larvae, Broods, Adults 0-7, Adults 8-20, Foragers";
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
	m_stream << "," << colony.foragers.GetPendingQuantity();
	OutputAgeStructure<CAdult>(colony.foragers, m_stream);
	m_stream << std::endl;
}
#endif // AGE_STRUCTURE_ONE_COLUMN_FOR_EACH_BOX_CARD

#if AGE_STRUCTURE_AGGREGATED_COLUMNS
void AgeStructureOutputFormatter::Record(CColony& colony, CEvent& event)
{
	m_stream << event.GetDateStg("%m/%d/%Y");
	m_stream << "," << colony.Weggs.GetQuantity();
	m_stream << "," << colony.Wlarv.GetQuantity();
	m_stream << "," << colony.CapWkr.GetQuantity();
	int  adultsAged0To7Days = 0;
	int  adultsAged7To20Days = 0;
	auto adultList = dynamic_cast<CAdultlist*>(&colony.Wadl);
	if (adultList)
	{
		int      index = 0;
		POSITION pos = adultList->GetHeadPosition();
		while (pos != nullptr)
		{
			index++;
			auto adult = (CAdult*)adultList->GetNext(pos);
			if (adult->IsAlive())
			{
				if (index <= 7)
				{
					adultsAged0To7Days += adult->GetNumber();
				}
				else
				{
					adultsAged7To20Days += adult->GetNumber();
				}
			}
		}
	}
	else
	{
		auto adultList = dynamic_cast<CForageBasedAgingAdultList*>(&colony.Wadl);
		if (adultList)
		{
			POSITION pos = adultList->GetHeadPosition();
			while (pos != nullptr)
			{
				auto adult = (CAdult*)adultList->GetNext(pos);
				if (adult->IsAlive())
				{
					if (adult->age <= 7.0)
					{
						adultsAged0To7Days += adult->GetNumber();
					}
					else
					{
						adultsAged7To20Days += adult->GetNumber();
					}
				}
			}
		}
	}
	m_stream << "," << adultsAged0To7Days;
	m_stream << "," << adultsAged7To20Days;
	m_stream << "," << colony.foragers.GetQuantity();
	m_stream << std::endl;
}
#endif // AGE_STRUCTURE_AGGREGATED_COLUMNS
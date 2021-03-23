#include "agestructureoutputformatter.h"

#include "colony.h"
#include "weatherevents.h"

AgeStructureOutputFormatter::AgeStructureOutputFormatter(CVarroaPopSession& session) : CustomOutputFormatter(session)
{
}

AgeStructureOutputFormatter::~AgeStructureOutputFormatter()
{
}

void AgeStructureOutputFormatter::Init(CColony& colony)
{
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
}

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
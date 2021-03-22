
#include "colonysizeoutputformatter.h"

#include "colony.h"
#include "weatherevents.h"

CColonySizeOutputFormatter::CColonySizeOutputFormatter(CVarroaPopSession& session) : CustomOutputFormatter(session)
{
}

CColonySizeOutputFormatter::~CColonySizeOutputFormatter()
{
}

void CColonySizeOutputFormatter::Init(CColony& colony)
{
	m_writer.write("Date", "Colony Size");
}

void CColonySizeOutputFormatter::Record(CColony& colony, CEvent& event)
{
	m_writer.write(event.GetDateStg("%m/%d/%Y"), colony.GetColonySize());
}
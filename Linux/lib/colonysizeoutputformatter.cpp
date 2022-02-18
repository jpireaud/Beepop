
#include "colonysizeoutputformatter.h"

#include "colony.h"
#include "weatherevents.h"

ColonySizeOutputFormatter::ColonySizeOutputFormatter(CVarroaPopSession& session) : CustomOutputFormatter(session)
{
}

ColonySizeOutputFormatter::~ColonySizeOutputFormatter()
{
}

void ColonySizeOutputFormatter::Init(CColony& colony)
{
	m_writer.write("Date", "Colony Size", "Min Temp", "Max Temp");
}

void ColonySizeOutputFormatter::Record(CColony& colony, CEvent& event)
{
	m_writer.write(event.GetDateStg("%m/%d/%Y"), colony.GetColonySize(), event.GetMinTemp(), event.GetMaxTemp());
}
#include "varroapopcmd.h"

VarroaPopCmd::VarroaPopCmd()
{

}

VarroaPopCmd::~VarroaPopCmd()
{

}

void VarroaPopCmd::Simulate()
{
    if (ReadyToSimulate())
    {

    }
}

bool VarroaPopCmd::ReadyToSimulate()
{
    return (theColony.IsInitialized() && m_pWeather->IsInitialized());
}

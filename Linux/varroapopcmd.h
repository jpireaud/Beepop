#pragma once
#ifndef VARROAPOPCMD_H
#define VARROAPOPCMD_H

#include "colony.h"
#include "weatherevents.h"

class VarroaPopCmd
{
public:

    VarroaPopCmd();
    ~VarroaPopCmd();


    void Simulate();

protected:

    bool ReadyToSimulate();

protected:

    CColony theColony;
    CWeatherEvents* m_pWeather;
};

#endif // VARROAPOPCMD_H
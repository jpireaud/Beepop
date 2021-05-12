#include "GlobalOptions.h"
#include "stdafx.h"

GlobalOptions& GlobalOptions::Get()
{
	static GlobalOptions sGlobalOptions;
	return sGlobalOptions;
}

GlobalOptions::GlobalOptions() : ShouldAgingBasedOnHourlyTemperatureEstimate(*this)
{
}

template <>
void GlobalOptions::AggregateOption<GlobalOptions::ForagerAgingBasedHourlyTemperatureEstimate>::Set(
    const GlobalOptions::ForagerAgingBasedHourlyTemperatureEstimate& value)
{
	m_value = value;
	m_options.ShouldForageDayElectionBasedOnTemperatures.Set(!m_value);
	m_options.ShouldComputeHourlyTemperatureEstimation.Set(m_value);
	m_options.ShouldAdultsAgeBasedOnForageInc.Set(m_value);
}

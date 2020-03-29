#pragma once

#include <string>

// Singleton class to easily add conditional block statements
// and select them by either:
// - changing default value in this class
// - add a command line option 
// to control and validate its impact on results.
class GlobalOptions
{
public:
	// Returns the single instance of GlobalOptions class
	static GlobalOptions& Get();

private:
	GlobalOptions();

public:
	template<typename OptionType>
	class Option
	{
	public:
		Option() {}
		Option(const OptionType& value) { Set(value); }
		const OptionType& operator()() const { return m_value; }
		void Set(const OptionType& value) { m_value = value; }

	private:
		OptionType m_value;
	};

	// Options
public:

	// Forager aging options

	// This option will affect the way we elect a day as a Forage day
	// If true:
	//    12.0 Deg C < MaxTemp < 43.33 Deg C    AND
	//    Windspeed <= 21.12 m/s                AND
	//    Rainfall <= .197 inches
	// else if false:
	//    Windspeed <= 21.12 m/s                AND
	//    Rainfall <= .197 inches
	Option<bool> ForageDayElectionBasedOnTemperatures = true;
	// This option will affect wth weather file data and binary data (Observed, Historical, and RCP)
	// Hourly temperature estimation will be used to enhance Forager aging increment.
	Option<bool> ShouldComputeHourlyTemperatureEstimation = false;
	// This option changes the way forager are processed on non foraging days.
	// Foragers will always be added to the PendingForagers list first so they'll age regarding the Forager increment.
	Option<bool> ShouldAddForagersToPendingForagersFirst = false;

	// Adult aging options

	// This option changes the way adult are aged. Basically, their aging will be the same as the Foragers.
	// Adults will new be added to the PendingAdults list first so they'll age regarding the Forager increment.
	Option<bool> ShouldAdultsAgeBasedOnForageDayElection = false;

	// Weather file options

	// If the weather file to be loaded is in bynary format, this specify which format to use
	// Valid options are:
	// - Observed
	// - Modeled
	// - Rcp85
	Option<std::string> BinaryWeatherFileFormatIdentifier;
};

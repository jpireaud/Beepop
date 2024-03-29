#pragma once

#include <stdexcept>
#include <string>

// Singleton class to easily add conditional block statements
// and select them by either:
// - changing default value in this class
// - add a command line option to control and validate its impact on results.
class GlobalOptions
{
public:
	// Returns the single instance of GlobalOptions class
	static GlobalOptions& Get();

public:
	// The use of this constructor is restricted for testing
	GlobalOptions();

public:
	template <typename OptionType> class Option
	{
	public:
		Option() {}
		Option(const OptionType& value) { Set(value); }
		virtual ~Option() {}
		virtual const OptionType& operator()() const { return m_value; }
		virtual void              Set(const OptionType& value) { m_value = value; }

	protected:
		OptionType m_value;
	};

	template <typename OptionType> class AggregateOption : Option<OptionType>
	{
	public:
		AggregateOption(GlobalOptions& options) : Option<OptionType>(), m_options(options) {}
		virtual void              Set(const OptionType& value);
		virtual const OptionType& operator()() const
		{
			throw std::runtime_error("GlobalOptions::AggregateOption::operator()() should not be called directly");
			return Option<OptionType>::m_value;
		}

	private:
		GlobalOptions& m_options;
	};

	// Options
public:
	// Egg laying options

	// This option affect Egg laying. When bellow threshold no egg will be laid.
	Option<double> DaylightHoursThreshold = 9.5;

	// Adult aging options

	// This option changes the way adult are aged. Adults will be age only when the Queen is laying eggs.
	Option<bool> ShouldAdultsAgeBasedOnLaidEggs = false;

	// Forager aging options

	// This option will affect the way we elect a day as a Forage day
	// If true:
	//    12.0 Deg C < MaxTemp < 43.33 Deg C    AND
	//    Windspeed <= 8.94 m/s                AND
	//    Rainfall <= .197 inches
	// else if false:
	//    Windspeed <= 8.94 m/s                AND
	//    Rainfall <= .197 inches
	//
	// 5/21/2020: Changed the Windspeed from 21.13 meters/sec to 8.94 meters/sec
	Option<bool> ShouldForageDayElectionBasedOnTemperatures = true;

	// This option affect the Windspeed threshold to determinate if the current day can be a Forage Day
	Option<double> WindspeedThreshold = 8.94;

	// This option affect the Rainfall threshold to determinate if the current day can be a Forage Day
	Option<double> RainfallThreshold = 0.197;

	// This option will affect wth weather file data (Observed, Historical, and RCP)
	// Hourly temperature estimation will be used to enhance ForagerInc aging increment.
	Option<bool> ShouldComputeHourlyTemperatureEstimation = false;

	// This option changes aging for both Adults and Foragers at the same time using,
	// a progressive aging based on age only.
	// Instead of using a finite number of boxcars we have unlimited number of boxcars which are based
	// on age only.
	Option<bool> ShouldAdultsAndForagersAgeBasedOnForageInc = false;

	// This option activate forage inc based aging for Foragers using the PendingList implementation.
	// On non-Foraging days, foragers when added to the Foragers list will not age and they will age
	// of ForageInc on the next Foraging day instead of aging 1 full day.
	Option<bool> ShouldForagersAgeBasedOnForageInc = false;

	// This option activate forage inc based aging for Adults using the PendingList implementation.
	// On non-Foraging days, foragers when added to the Foragers list will not age and they will age
	// of ForageInc on the next Foraging day instead of aging 1 full day.
	Option<bool> ShouldAdultsAgeBasedOnForageInc = false;

	// This options controls:
	// - ShouldForageDayElectionBasedOnTemperatures set to !value
	// - ShouldComputeHourlyTemperatureEstimation set to value
	// - ShouldAdultsAndForagersAgeBasedOnForageInc set to value
	// - ShouldApplyWinterMortality set to !value
	// - ShouldApplyLifespanReduction set to !value
	typedef bool                                                ForagerAgingBasedHourlyTemperatureEstimate;
	AggregateOption<ForagerAgingBasedHourlyTemperatureEstimate> ShouldAgingBasedOnHourlyTemperatureEstimate;

	// Weather file options

	// If the weather file to be loaded is in bynary format, this specify which format to use
	// Valid options are:
	// - Observed
	// - Modeled
	// - Rcp45
	// - Rcp85
	Option<std::string> BinaryWeatherFileFormatIdentifier;

	// Additional Output Data
	Option<bool> ShouldOutputInOutCounts = false;

	// Apply winter mortality to colony
	//
	// Right now winter mortality is only applied to Foragers()->
	// This would need to evolve to be apply to all bees, with different impact of different age of adult bees.
	Option<bool> ShouldApplyWinterMortality = true;

	// Apply lifespan reduction
	Option<bool> ShouldApplyLifespanReduction = true;
};

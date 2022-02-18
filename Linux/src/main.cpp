#include "coldstoragesimulator.h"
#include "globaloptions.h"
#include "varroapopcmdbridge.h"

#include "agestructureoutputformatter.h"
#include "colonysizeoutputformatter.h"
#include "customoutputformatter.h"
#include "debugoutputformatter.h"
#include "inouteventsoutputformatter.h"
#include "mapdataoutputformatter.h"

#include "stdafx.h"

#include <boost/filesystem.hpp>
namespace bfs = boost::filesystem;

#include <cxxopts.hpp>

#include <set>

void LoadVRPFile(CVarroaPopSession& session, const CString& filename);

int main(int argc, char** argv)
{
	cxxopts::Options options("VarroaPop", "Command Line version of the VarroaPop app");

	// Here we omit the log file since it is not used in the VarroaPop app

	options.add_options("usage")(
	    "i,input_file", "Input File: Contains initialization data for simulation values",
	    cxxopts::value<std::string>())(
	    "o,output_file", "Output File: Simulation results will be saved at this location",
	    cxxopts::value<std::string>())(
	    "v,vrp_file", "VRP File: If specified the VRP file will be parsed to initialize default simulation values",
	    cxxopts::value<std::string>())(
	    "s,snapshots_dir",
	    "[optional] Snapshots dir: folder to store/load snapshots generated or imported during simulation",
	    cxxopts::value<std::string>())(
	    "w,weather_file",
	    "[optional] Weather File: Simulation will use this weather file instead of the one in the input file",
	    cxxopts::value<std::string>())(
	    "d,working_directory", "[optional] Working Directory: If specified all path provided are relative this path",
	    cxxopts::value<std::string>())(
	    "f,force", "Force overwrite of output file if it exists", cxxopts::value<bool>()->default_value("false"))(
	    "forageDayNoTemp", "A forage day is computed only using wind and rain for a given day",
	    cxxopts::value<bool>()->default_value("false"))(
	    "hourlyTemperaturesEstimation", "Compute hourly temperatures estimation",
	    cxxopts::value<bool>()->default_value("false"))(
	    "adultsAgingBasedOnForageInc", "All adults and foragers age based on ForageInc",
	    cxxopts::value<bool>()->default_value("false"))(
	    "workersAgingBasedOnForageInc", "Adults workers age based on ForageInc",
	    cxxopts::value<bool>()->default_value("false"))(
	    "foragersAgingBasedOnForageInc", "Foragers age based on ForageInc",
	    cxxopts::value<bool>()->default_value("false"))(
	    "adultsAgingBasedOnLaidEggs", "Adults age only if the Queen is laying eggs",
	    cxxopts::value<bool>()->default_value("false"))(
	    "climateChangeScenario",
	    "Activate the following options forageDayNoTemp | hourlyTemperaturesEstimation | adultsAgingBasedOnForageInc",
	    cxxopts::value<bool>()->default_value("false"))(
	    "applyWinterMortality", "Activate/Deactivate winter mortality for adults population",
	    cxxopts::value<bool>()->default_value("true"))(
	    "applyLifespanReduction", "Activate/Deactivate lifespan reduction for adults population",
	    cxxopts::value<bool>()->default_value("true"))(
	    "binaryWeatherFileFormat", "Specifies the binary format of the weather file (Observed|Modeled|Rcp85|Rcp45)",
	    cxxopts::value<std::string>())(
	    "windspeed",
	    "Specifies the windspeed threshold after which the current day will not be considered as Forage Day",
	    cxxopts::value<double>())(
	    "rainfall", "Specifies the rainfall threshold after which the current day will not be considered as Forage Day",
	    cxxopts::value<double>())(
	    "daylighthours", "Specifies the DaylightHours threshold after which the Queen stop laying eggs, default is 9.5",
	    cxxopts::value<double>())(
	    "inOutEvents",
	    "Output additional information adding the following data -- NewWEggs NewDEggs "
	    "WEggsToLarv DEggsToLarv WLarvToBrood DLarvToBrood WBroodToAdult DBroodToAdult "
	    "WAdultToForagers WinterMortalityForagersLoss DeadForagers",
	    cxxopts::value<bool>()->default_value("false"))(
	    "coldStorage", "Activate cold storage", cxxopts::value<bool>()->default_value("false"))(
	    "coldStorageStartDate", "Date at which colony is placed in cold storage with format MM/DD",
	    cxxopts::value<std::string>())(
	    "coldStorageEndDate", "Date at which colony is removed from cold storage with format MM/DD",
	    cxxopts::value<std::string>())(
	    "z,compress", "Compress output in a gzip file", cxxopts::value<bool>()->default_value("false"))(
	    "outputFormat", "Output format can be default / colony / age_structure / mapdata / inout_events / debug ",
	    cxxopts::value<std::string>()->default_value("default"))(
	    "outputEvents", "Output colony events to the standard output", cxxopts::value<bool>()->default_value("false"));

	options.add_options("help")("h,help", "Displays help message")("u,usage", "Displays help message");

	bfs::path inputFile, outputFile, vrpFile, weatherFile;

	boost::system::error_code currentPathError;
	bfs::path                 snapshotsDir = bfs::current_path(currentPathError);
	if (currentPathError != boost::system::errc::success)
	{
		snapshotsDir = "./";
	}
	std::cout << "working directory is " << snapshotsDir << std::endl;

	std::unique_ptr<CustomOutputFormatter> outputFormatter;

	try
	{
		auto arguments = options.parse(argc, argv);

		bool compressOutput = arguments["z"].as<bool>();

		if (arguments.count("i") == 1 && arguments.count("o") == 1)
		{
			// store input and output file in boost paths
			inputFile = bfs::path(arguments["i"].as<std::string>());
			outputFile = bfs::path(arguments["o"].as<std::string>());

			// store vrpFile if present for working directory handling
			if (arguments.count("v") == 1)
			{
				vrpFile = bfs::path(arguments["v"].as<std::string>());
			}

			// store vrpFile if present for working directory handling
			if (arguments.count("v") == 1)
			{
				vrpFile = bfs::path(arguments["v"].as<std::string>());
			}

			// store snapshotsDir if present
			if (arguments.count("s") == 1)
			{
				snapshotsDir = bfs::path(arguments["s"].as<std::string>());
				if (!bfs::exists(snapshotsDir))
				{
					if (!bfs::create_directories(snapshotsDir))
					{
						std::cout << "cannot create directory " << snapshotsDir << std::endl;
					}
				}
			}

			// store weatherFile if present for working directory handling
			if (arguments.count("w") == 1)
			{
				weatherFile = bfs::path(arguments["w"].as<std::string>());
			}

			// handle working directory is specified
			bfs::path workingDirectory;
			if (arguments.count("d") == 1)
			{
				workingDirectory = bfs::path(arguments["d"].as<std::string>());
			}
			if (!workingDirectory.empty())
			{
				if (bfs::exists(workingDirectory))
				{
					inputFile = workingDirectory / inputFile;
					outputFile = workingDirectory / outputFile;
					if (!vrpFile.empty()) vrpFile = workingDirectory / vrpFile;
					if (!weatherFile.empty()) weatherFile = workingDirectory / weatherFile;
				}
				else
				{
					std::cerr << "working directory " << workingDirectory.string() << " does not exists" << std::endl;
					return -1;
				}
			}

			// check input files existance
			bool error = false;
			if (!bfs::exists(inputFile))
			{
				std::cerr << "input file " << inputFile.string() << " does not exists" << std::endl;
				error = true;
			}
			if (!vrpFile.empty() && !bfs::exists(vrpFile))
			{
				std::cerr << "vrp file " << vrpFile.string() << " does not exists" << std::endl;
				error = true;
			}
			if (!weatherFile.empty() && !bfs::exists(weatherFile))
			{
				std::cerr << "weather file " << weatherFile.string() << " does not exists" << std::endl;
				error = true;
			}

			// prevent overwriting output file
			auto outputDirectory = outputFile.parent_path();
			if (!bfs::exists(outputFile))
			{
				if (!outputDirectory.empty() && !bfs::exists(outputDirectory))
				{
					if (!bfs::create_directories(outputDirectory))
					{
						// it is possible that the given directory was created by another processus so
						// let's check if the directory is created in which case no need to set the error
						if (!bfs::exists(outputDirectory))
						{
							std::cerr << "cannot create output directory " << outputDirectory.string() << std::endl;
							error = true;
						}
					}
				}
			}
			else if (arguments.count("f") == 0)
			{
				std::cerr << "output file " << outputFile.string()
				          << " already exists. Do you want to overwrite it? [y/n]: ";
				char answer = 0;
				std::cin >> answer;
				const std::set<char> validAnswer = {'n', 'N', 'y', 'Y', 'q', 'Q'};
				while (validAnswer.find(answer) == validAnswer.end())
				{
					std::cerr << "answer only by y or n (q for exit): ";
					std::cin >> answer;
				}
				if (answer == 'q' || answer == 'Q')
				{
					return 0;
				}
				else if (answer == 'n' || answer == 'N')
				{
					auto              increment = 2;
					auto              outputFilename = outputFile.filename();
					auto              outputExtension = outputFilename.extension();
					std::stringstream replaceString;

					// remove extension temporarely
					outputFilename.replace_extension("");

					// handle increment ouput file (i) index if any
					do
					{
						// try to execute replace regex
						const std::regex  digitRegex("(\\(\\d+\\))");
						const std::regex  digitReplaceRegex("\\(\\d+\\)");
						const std::string filename = outputFilename.string();
						std::smatch       digitMatch;
						if (std::regex_search(filename, digitMatch, digitRegex))
						{
							increment = std::atoi(digitMatch[digitMatch.size() - 1].str().c_str() + 1);
							replaceString << "(" << ++increment << ")";
							outputFilename =
							    std::regex_replace(outputFilename.string(), digitReplaceRegex, replaceString.str());
						}
						else
						{
							replaceString << "(" << increment++ << ")";
							outputFilename = outputFilename.string() + replaceString.str();
						}
						replaceString.str("");

						// restore extension temporarely
						outputFile = outputDirectory / outputFilename;
						outputFile.replace_extension(outputExtension);
					} while (bfs::exists(outputFile));

					std::cout << "output file will be " << outputFile.string() << std::endl;
				}
			}
			if (arguments.count("forageDayNoTemp") == 1)
			{
				GlobalOptions::Get().ShouldForageDayElectionBasedOnTemperatures.Set(
				    !arguments["forageDayNoTemp"].as<bool>());
			}
			if (arguments.count("hourlyTemperaturesEstimation") == 1)
			{
				GlobalOptions::Get().ShouldComputeHourlyTemperatureEstimation.Set(
				    arguments["hourlyTemperaturesEstimation"].as<bool>());
			}
			if (arguments.count("adultsAgingBasedOnForageInc") == 1)
			{
				GlobalOptions::Get().ShouldAdultsAndForagersAgeBasedOnForageInc.Set(
				    arguments["adultsAgingBasedOnForageInc"].as<bool>());
			}
			if (arguments.count("foragersAgingBasedOnForageInc") == 1)
			{
				GlobalOptions::Get().ShouldForagersAgeBasedOnForageInc.Set(
				    arguments["foragersAgingBasedOnForageInc"].as<bool>());
			}
			if (arguments.count("workersAgingBasedOnForageInc") == 1)
			{
				GlobalOptions::Get().ShouldAdultsAgeBasedOnForageInc.Set(
				    arguments["workersAgingBasedOnForageInc"].as<bool>());
			}
			if (arguments.count("binaryWeatherFileFormat") == 1)
			{
				GlobalOptions::Get().BinaryWeatherFileFormatIdentifier.Set(
				    arguments["binaryWeatherFileFormat"].as<std::string>());
			}
			if (arguments.count("adultsAgingBasedOnLaidEggs") == 1)
			{
				GlobalOptions::Get().ShouldAdultsAgeBasedOnLaidEggs.Set(
				    arguments["adultsAgingBasedOnLaidEggs"].as<bool>());
			}
			if (arguments.count("climateChangeScenario") == 1)
			{
				GlobalOptions::Get().ShouldAgingBasedOnHourlyTemperatureEstimate.Set(
				    arguments["climateChangeScenario"].as<bool>());
			}
			if (arguments.count("applyWinterMortality") == 1)
			{
				GlobalOptions::Get().ShouldApplyWinterMortality.Set(arguments["applyWinterMortality"].as<bool>());
			}
			if (arguments.count("applyLifespanReduction") == 1)
			{
				GlobalOptions::Get().ShouldApplyLifespanReduction.Set(arguments["applyLifespanReduction"].as<bool>());
			}
			if (arguments.count("windspeed") == 1)
			{
				GlobalOptions::Get().WindspeedThreshold.Set(arguments["windspeed"].as<double>());
			}
			if (arguments.count("rainfall") == 1)
			{
				GlobalOptions::Get().RainfallThreshold.Set(arguments["rainfall"].as<double>());
			}
			if (arguments.count("daylighthours") == 1)
			{
				GlobalOptions::Get().DaylightHoursThreshold.Set(arguments["daylighthours"].as<double>());
			}
			if (arguments.count("inOutEvents") == 1)
			{
				GlobalOptions::Get().ShouldOutputInOutCounts.Set(arguments["inOutEvents"].as<bool>());
			}
			if (arguments.count("coldStorage") == 1)
			{
				CColdStorageSimulator::Get().SetEnabled(arguments["coldStorage"].as<bool>());

				std::regex  validateDate("(0?[1-9]|1[0-2])/(0?[1-9]|[1-2][0-9]|3[0-1])");
				std::smatch dateElements;
				if (arguments.count("coldStorageStartDate") == 1 && arguments.count("coldStorageEndDate") == 1)
				{
					int         startMonth = -1, startDay = -1, endMonth = -1, endDay = -1;
					std::string startDate = arguments["coldStorageStartDate"].as<std::string>();
					if (std::regex_match(startDate, dateElements, validateDate) && dateElements.size() == 3 &&
					    startDate == *dateElements.begin())
					{
						startMonth = std::stoi(*(dateElements.begin() + 1));
						startDay = std::stoi(*(dateElements.begin() + 2));
					}
					else
					{
						std::cerr << "coldStorageStartDate is not specified correctly " << startDate
						          << " expected MM/DD" << std::endl;
						error = true;
					}

					std::string endDate = arguments["coldStorageEndDate"].as<std::string>();
					if (std::regex_match(endDate, dateElements, validateDate) && dateElements.size() == 3 &&
					    endDate == *dateElements.begin())
					{
						endMonth = std::stoi(*(dateElements.begin() + 1));
						endDay = std::stoi(*(dateElements.begin() + 2));
					}
					else
					{
						std::cerr << "coldStorageEndDate is not specified correctly " << endDate << " expected MM/DD"
						          << std::endl;
						error = true;
					}
					if (startMonth != -1 && startDay != -1 && endMonth != -1 && endDay != -1)
					{
						// In the case of the cold storage year is not relevant, let's set it as the default first year
						CColdStorageSimulator::Get().SetStartDate(COleDateTime(1970, startMonth, startDay, 0, 0, 0));
						CColdStorageSimulator::Get().SetEndDate(COleDateTime(1970, endMonth, endDay, 0, 0, 0));
					}
				}
				else if (arguments.count("coldStorageStartDate") != arguments.count("coldStorageEndDate"))
				{
					std::cerr << "coldStorageStartDate and coldStorageEndDate should be specified together in order "
					             "for the cold storage to work correctly "
					          << std::endl;
					error = true;
				}
			}
			if (error)
			{
				return -1;
			}
		}
		else
		{
			const std::string help = options.help({"usage"});
			std::cout << help << std::endl;
		}

		// now that we processed input arguments let's proceed with the simulation

		CVarroaPopSession session;

		// setup bridge

		VarroaPopCmdBridge bridge(session);

		auto outputFormat = arguments["outputFormat"].as<std::string>();

		const std::vector<std::string> validOutputFormats = {"default", "colony",       "age_structure",
		                                                     "mapdata", "inout_events", "debug"};
		if (std::find(validOutputFormats.begin(), validOutputFormats.end(), outputFormat) == validOutputFormats.end())
		{
			std::cerr
			    << "output format should be default, colony, age_structure, mapdata or inout_events, using default"
			    << std::endl;
		}
		else
		{
			if (outputFormat == "colony")
			{
				outputFormatter.reset(new ColonySizeOutputFormatter(session));
			}
			else if (outputFormat == "age_structure")
			{
				outputFormatter.reset(new AgeStructureOutputFormatter(session));
			}
			else if (outputFormat == "mapdata")
			{
				outputFormatter.reset(new MapDataOutputFormatter(session));
			}
			else if (outputFormat == "inout_events")
			{
				outputFormatter.reset(new InOutEventsOutputFormatter(session));
			}
			else if (outputFormat == "debug")
			{
				outputFormatter.reset(new DebugOutputFormatter(session));
			}
			if (outputFormatter)
			{
				session.SetOutputFormatter(outputFormatter.get());
			}
		}

		session.SetBridge(&bridge);

		session.SetSnapshotsDirectory(snapshotsDir.string().c_str());

		if (!vrpFile.empty())
		{
			LoadVRPFile(session, vrpFile.string().c_str());
		}

		// Read input file
		session.ProcessInputFile(inputFile.string().c_str());

		if (!weatherFile.empty())
		{
			session.LoadWeatherFile(weatherFile.string().c_str());
		}

		// Run simulation
		session.Simulate();

		if (outputFormatter)
		{
			outputFormatter->WriteToFile(outputFile.string(), compressOutput);
		}
		else
		{
			session.StoreResultsFile(outputFile.string().c_str());
		}

		if (arguments["outputEvents"].count() > 0 && arguments["outputEvents"].as<bool>())
		{
			// Output colony events
			const auto events = session.GetColony()->m_ColonyEventList;
			POSITION   pos = events.GetHeadPosition();
			while (pos != NULL)
			{
				const CString& event = events.GetNext(pos);
				std::cout << event.ToString() << std::endl;
			}
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}

void LoadVRPFile(CVarroaPopSession& session, const CString& filename)
{
	CStdioFile file(filename, CFile::modeRead | CFile::typeBinary);
	CArchive   archive(&file, CArchive::load);
	session.Serialize(archive);
}

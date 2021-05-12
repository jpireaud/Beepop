#include "catch2/catch.hpp"

//! include explicitely since we are not using the pre-compiled header for tests
//! may change this in the future
#include "stdafx.h"

#include "carchive.h"

#include "coldstoragesimulator.h"
#include "colony.h"
#include "globaloptions.h"
#include "snapshotinfo.h"
#include "varroapopcmdbridge.h"
#include "varroapopsession.h"

#include "helpers/common.h"
#include "helpers/testoutputformatter.h"

#include "csv.h"

#include <boost/filesystem.hpp>
namespace bfs = boost::filesystem;

TEST_CASE("CArchive operations", "[port]")
{
	struct ToSerialize
	{
		float        aFloat;
		double       aDouble;
		int32_t      aInt32;
		uint32_t     aUInt32;
		int8_t       aInt8;
		COleDateTime aDateTime;
		CString      aString;
		CTime        aTime;
	};

	SYSTEMTIME systemTime;
	systemTime.wYear = 1982;
	systemTime.wMonth = 01;
	systemTime.wDay = 11;
	systemTime.wHour = 11;
	systemTime.wMinute = 30;
	systemTime.wSecond = 18;

	ToSerialize data{
	    23.3f,
	    89.0,
	    -2147483647,
	    4294967295,
	    -127,
	    COleDateTime(2020, 01, 11, 13, 30, 43),
	    CString("This is a string"),
	    CTime(systemTime)};

	SECTION("Store")
	{

		CStdioFile file(GetFileInTempDirectory("store.bin").c_str(), CFile::modeWrite | CFile::typeBinary);
		CArchive   archive(&file, CArchive::store);

		archive << data.aFloat;
		archive << data.aDouble;
		archive << data.aInt32;
		archive << data.aUInt32;
		archive << data.aInt8;
		archive << data.aDateTime;
		archive << data.aString;
		archive << data.aTime;

		file.Close();
	}

	SECTION("Load")
	{
		CStdioFile file(GetFileInTempDirectory("store.bin").c_str(), CFile::modeRead | CFile::typeBinary);
		CArchive   archive(&file, CArchive::load);

		ToSerialize loaded;
		archive >> loaded.aFloat;
		archive >> loaded.aDouble;
		archive >> loaded.aInt32;
		archive >> loaded.aUInt32;
		archive >> loaded.aInt8;
		archive >> loaded.aDateTime;
		archive >> loaded.aString;
		archive >> loaded.aTime;

		CHECK(loaded.aFloat == data.aFloat);
		CHECK(loaded.aDouble == data.aDouble);
		CHECK(loaded.aInt32 == data.aInt32);
		CHECK(loaded.aUInt32 == data.aUInt32);
		CHECK(loaded.aInt8 == data.aInt8);

		CHECK(loaded.aDateTime.GetYear() == 2020);
		CHECK(loaded.aDateTime.GetMonth() == 1);
		CHECK(loaded.aDateTime.GetDay() == 11);
		CHECK(loaded.aDateTime.GetHour() == 13);
		CHECK(loaded.aDateTime.GetMinute() == 30);

		CHECK(loaded.aString == "This is a string");

		CHECK(loaded.aTime.GetTime().GetYear() == 1982);
		CHECK(loaded.aTime.GetTime().GetMonth() == 1);
		CHECK(loaded.aTime.GetTime().GetDay() == 11);
		CHECK(loaded.aTime.GetTime().GetHour() == 11);
		CHECK(loaded.aTime.GetTime().GetMinute() == 30);

		file.Close();
	}

	SECTION("Simulate and check initialization flow")
	{
		// load the default VRP file
		bfs::path simulationsDir = GetSimulationsDir();
		bfs::path filesDir = simulationsDir / "VarroaPy" / "VarroaPy" / "files";
		bfs::path vrpFile = filesDir / "exe" / "simplified.vrp";

		bfs::path testsDir = GetTestsDir();
		bfs::path inputFile = testsDir / "data" / "rcp85.txt";

		GlobalOptions::Get().BinaryWeatherFileFormatIdentifier.Set("Rcp85");
		bfs::path weatherFile = simulationsDir / "Rcp85Binary" / "data_46.03125_-118.34375";

		bfs::path outputFile = GetFileInTempDirectory("results.csv");

		{
			INFO(vrpFile.string());
			REQUIRE(bfs::exists(vrpFile));
		}
		{
			INFO(inputFile.string());
			REQUIRE(bfs::exists(inputFile));
		}
		{
			INFO(weatherFile.string());
			REQUIRE(bfs::exists(weatherFile));
		}

		// create session
		CVarroaPopSession session;

		// initialize bridge
		VarroaPopCmdBridge bridge(session);
		session.SetBridge(&bridge);

		// set output formatter
		std::unique_ptr<TestOutputFormatter> outputFormatter(new TestOutputFormatter(session));
		session.SetOutputFormatter(outputFormatter.get());

		CStdioFile vrp(vrpFile.string().c_str(), CFile::modeRead | CFile::typeBinary);
		CArchive   vrpArchive(&vrp, CArchive::load);
		session.Serialize(vrpArchive);

		// load weather file
		REQUIRE(session.LoadWeatherFile(weatherFile.string().c_str()));

		// load vrp file
		{
			CHECK(session.GetColony()->GetColonySize() == 0);
			session.GetColony()->InitializeColony();
			CHECK(session.GetColony()->GetColonySize() == 20000);

			CHECK(session.GetColony()->GetForagerLifespan() == 10);
			CHECK(session.GetColony()->Foragers()->GetPropActualForagers() == Catch::Detail::Approx(0.3));
			CHECK(session.GetColony()->Foragers()->GetQuantity() == 6455);
			CHECK(session.GetColony()->Foragers()->GetLength() == session.GetColony()->GetForagerLifespan());

			CHECK(session.GetColony()->Wadl()->GetQuantity() == 20000 - 6455);

			CHECK(session.GetColony()->queen.GetQueenStrength() == Catch::Detail::Approx(4.0));
			CHECK(session.m_RQEnableReQueen == true);
			CHECK(session.m_RQScheduled == 1);
			CHECK(session.m_RQOnce == 0);
			CHECK(session.m_RQReQueenDate == COleDateTime(1899, 12, 30, 0, 0, 0));

			vrp.Close();
		}

		// load input file
		{
			session.GetColony()->Clear();
			session.ProcessInputFile(inputFile.string().c_str());

			CHECK(session.GetColony()->GetColonySize() == 0);
			session.GetColony()->InitializeColony();
			CHECK(session.GetColony()->GetColonySize() == 20000);

			CHECK(session.GetColony()->GetForagerLifespan() == 10);
			CHECK(session.GetColony()->Foragers()->GetPropActualForagers() == Catch::Detail::Approx(0.3));
			CHECK(session.GetColony()->Foragers()->GetQuantity() == 6455);
			CHECK(session.GetColony()->Foragers()->GetLength() == session.GetColony()->GetForagerLifespan());

			CHECK(session.GetColony()->Wadl()->GetQuantity() == 20000 - 6455);

			CHECK(session.GetColony()->queen.GetQueenStrength() == Catch::Detail::Approx(3.0));
			CHECK(session.m_RQEnableReQueen == true);
			CHECK(session.m_RQScheduled == 0);
			CHECK(session.m_RQOnce == 1);
			CHECK(session.m_RQReQueenDate == COleDateTime(2010, 8, 1, 0, 0, 0));

			vrp.Close();
		}

		session.GetColony()->Clear();
		session.ProcessInputFile(inputFile.string().c_str());
		session.Simulate();

		outputFormatter->WriteToFile(outputFile.string(), false);

		CStdioFile file(GetFileInTempDirectory("colony.bin").c_str(), CFile::modeWrite | CFile::typeBinary);
		CArchive   archive(&file, CArchive::store);
		CHECK(archive.IsStoring());
		session.GetColony()->Serialize(archive, session.GetFileVersion());
		file.Close();
	}

	SECTION("Colony snapshot")
	{
		// load the default VRP file
		bfs::path simulationsDir = GetSimulationsDir();
		bfs::path testsDir = GetTestsDir();
		bfs::path filesDir = simulationsDir / "VarroaPy" / "VarroaPy" / "files";
		bfs::path vrpFile = filesDir / "exe" / "simplified.vrp";
		bfs::path inputFile = testsDir / "data" / "rcp85-snapshot.txt";

		GlobalOptions::Get().BinaryWeatherFileFormatIdentifier.Set("Rcp85");
		bfs::path weatherFile = simulationsDir / "Rcp85Binary" / "data_46.03125_-118.34375";
        
        // force forage inc aging
        GlobalOptions::Get().ShouldAdultsAgeBasedOnForageInc.Set(true);

		bfs::path snapshotsDirectory = bfs::path(GetTempDirectory()) / "snapshots";
		if (!bfs::exists(snapshotsDirectory)) bfs::create_directories(snapshotsDirectory);
		REQUIRE(bfs::exists(snapshotsDirectory));

		REQUIRE(bfs::exists(vrpFile));
		REQUIRE(bfs::exists(inputFile));
		REQUIRE(bfs::exists(weatherFile));

		// create session
		CVarroaPopSession session;

		// initialize bridge
		VarroaPopCmdBridge bridge(session);
		session.SetBridge(&bridge);

		// set output formatter
		std::unique_ptr<TestOutputFormatter> outputFormatter(new TestOutputFormatter(session));
		session.SetOutputFormatter(outputFormatter.get());

		CStdioFile vrp(vrpFile.string().c_str(), CFile::modeRead | CFile::typeBinary);
		CArchive   vrpArchive(&vrp, CArchive::load);
		session.Serialize(vrpArchive);

		// load weather file
		REQUIRE(session.LoadWeatherFile(weatherFile.string().c_str()));

		session.ProcessInputFile(inputFile.string().c_str());

		REQUIRE(session.m_SnapshotsDates.GetCount() == 2);

		auto snapshotDate = (CSnapshotInfo*)session.m_SnapshotsDates.GetHead();
		REQUIRE(snapshotDate->GetDate().GetYear() == 2020);
		REQUIRE(snapshotDate->GetDate().GetMonth() == 4);
		REQUIRE(snapshotDate->GetDate().GetDay() == 15);

		snapshotDate = (CSnapshotInfo*)session.m_SnapshotsDates.GetTail();
		REQUIRE(snapshotDate->GetDate().GetYear() == 2030);
		REQUIRE(snapshotDate->GetDate().GetMonth() == 12);
		REQUIRE(snapshotDate->GetDate().GetDay() == 31);

		session.SetSnapshotsDirectory(snapshotsDirectory.string().c_str());

		session.Simulate();

		outputFormatter->WriteToFile(GetFileInTempDirectory("results-snapshot.csv").c_str());
	}

	SECTION("Colony snapshot - loading")
	{
		bfs::path         snapshotsDirectory = bfs::path(GetTempDirectory()) / "snapshots";
		CVarroaPopSession session;

		// now we are going to check the snapshots
		{
			bfs::path snapshot = snapshotsDirectory / "snapshot-2020-04-15";
			{
				INFO("make sure to run the section 'Colony snapshot' first:");
				INFO(snapshot.string());
				REQUIRE(bfs::exists(snapshot));
			}

			CStdioFile file(snapshot.string().c_str(), CFile::modeRead | CFile::typeBinary);
			CArchive   archive(&file, CArchive::load);
			CColony    colony;
			colony.Serialize(archive, session.GetFileVersion());

			const int eggs = 399;
			const int larvae = 311;
			const int broods = 654;
			const int adults = 4428;
			const int foragers = 803;
			const int colonySize = 5231;
			CHECK(colony.Weggs.GetQuantity() == eggs);
			CHECK(colony.Wlarv.GetQuantity() == larvae);
			CHECK(colony.CapWkr.GetQuantity() == broods);
			CHECK(colony.Wadl()->GetQuantity() == adults);
			CHECK(colony.Foragers()->GetQuantity() == foragers);
			CHECK(colony.GetColonySize() == colonySize);
		}
		{
			bfs::path snapshot = snapshotsDirectory / "snapshot-initial";
			{
				INFO("make sure to run the section 'Colony snapshot' first:");
				INFO(snapshot.string());
				REQUIRE(bfs::exists(snapshot));
			}

			CStdioFile file(snapshot.string().c_str(), CFile::modeRead | CFile::typeBinary);
			CArchive   archive(&file, CArchive::load);
			CColony    colony;
			colony.Serialize(archive, session.GetFileVersion());

			const int eggs = 0;
			const int larvae = 0;
			const int broods = 0;
			const int adults = 3249;
			const int foragers = 3427;
			const int colonySize = 6676;
			CHECK(colony.Weggs.GetQuantity() == eggs);
			CHECK(colony.Wlarv.GetQuantity() == larvae);
			CHECK(colony.CapWkr.GetQuantity() == broods);
			CHECK(colony.Wadl()->GetQuantity() == adults);
			CHECK(colony.Foragers()->GetQuantity() == foragers);
			CHECK(colony.GetColonySize() == colonySize);
		}
	}

	SECTION("Colony snapshot - reset")
	{
		// load the default VRP file
		bfs::path simulationsDir = GetSimulationsDir();
		bfs::path testsDir = GetTestsDir();
		bfs::path filesDir = simulationsDir / "VarroaPy" / "VarroaPy" / "files";
		bfs::path vrpFile = filesDir / "exe" / "simplified.vrp";
		bfs::path inputFile = testsDir / "data" / "rcp85-reset.txt";

		GlobalOptions::Get().BinaryWeatherFileFormatIdentifier.Set("Rcp85");
		bfs::path weatherFile = simulationsDir / "Rcp85Binary" / "data_46.03125_-118.34375";

		bfs::path snapshotsDirectory = bfs::path(GetTempDirectory()) / "snapshots";
		if (!bfs::exists(snapshotsDirectory)) bfs::create_directories(snapshotsDirectory);
		REQUIRE(bfs::exists(snapshotsDirectory));

		REQUIRE(bfs::exists(vrpFile));
		REQUIRE(bfs::exists(inputFile));
		REQUIRE(bfs::exists(weatherFile));

		// create session
		CVarroaPopSession session;

		// initialize bridge
		VarroaPopCmdBridge bridge(session);
		session.SetBridge(&bridge);

		// set output formatter
		std::unique_ptr<TestOutputFormatter> outputFormatter(new TestOutputFormatter(session));
		session.SetOutputFormatter(outputFormatter.get());

		CStdioFile vrp(vrpFile.string().c_str(), CFile::modeRead | CFile::typeBinary);
		CArchive   vrpArchive(&vrp, CArchive::load);
		session.Serialize(vrpArchive);

		// load weather file
		REQUIRE(session.LoadWeatherFile(weatherFile.string().c_str()));

		session.ProcessInputFile(inputFile.string().c_str());

		CHECK(session.m_SnapshotsResetEnabled);
		REQUIRE(session.m_SnapshotsResets.GetCount() == 2);

		auto snapshotDate = (CSnapshotInfo*)session.m_SnapshotsResets.GetHead();
		CHECK_FALSE(snapshotDate->IsScheduled());
		CHECK(snapshotDate->GetDate().GetYear() == 2020);
		CHECK(snapshotDate->GetDate().GetMonth() == 4);
		CHECK(snapshotDate->GetDate().GetDay() == 15);

		snapshotDate = (CSnapshotInfo*)session.m_SnapshotsResets.GetTail();
		CHECK_FALSE(snapshotDate->IsScheduled());
		CHECK(snapshotDate->GetDate().GetYear() == 2030);
		CHECK(snapshotDate->GetDate().GetMonth() == 12);
		CHECK(snapshotDate->GetDate().GetDay() == 31);

		session.SetSnapshotsDirectory(snapshotsDirectory.string().c_str());

		session.Simulate();

		outputFormatter->WriteToFile(GetFileInTempDirectory("results-reset.csv").c_str());

		auto items = GetItemsFromFile(GetFileInTempDirectory("results-reset.csv"));

		REQUIRE(items.size() == 11323);
		CHECK(items[11151].date == "07/13/2040");
		CHECK(items[11151].queenStrength == Catch::Detail::Approx(3.0));
		CHECK(items[11151].eggs == 660);
		CHECK(items[11151].larvae == 478);
		CHECK(items[11151].broods == 75);
		CHECK(items[11151].adults == 172);
		CHECK(items[11151].foragers == 944);
		CHECK(items[11151].colonySize == 1116);
	}

	SECTION("Colony snapshot - reset scheduled")
	{
		// load the default VRP file
		bfs::path simulationsDir = GetSimulationsDir();
		bfs::path testsDir = GetTestsDir();
		bfs::path filesDir = simulationsDir / "VarroaPy" / "VarroaPy" / "files";
		bfs::path vrpFile = filesDir / "exe" / "simplified.vrp";
		bfs::path inputFile = testsDir / "data" / "rcp85-autoreset.txt";

		GlobalOptions::Get().BinaryWeatherFileFormatIdentifier.Set("Rcp85");
		bfs::path weatherFile = simulationsDir / "Rcp85Binary" / "data_46.03125_-118.34375";

		bfs::path snapshotsDirectory = bfs::path(GetTempDirectory()) / "snapshots";

		REQUIRE(bfs::exists(vrpFile));
		REQUIRE(bfs::exists(inputFile));
		REQUIRE(bfs::exists(weatherFile));

		// create session
		CVarroaPopSession session;

		// initialize bridge
		VarroaPopCmdBridge bridge(session);
		session.SetBridge(&bridge);

		// set output formatter
		std::unique_ptr<TestOutputFormatter> outputFormatter(new TestOutputFormatter(session));
		session.SetOutputFormatter(outputFormatter.get());

		CStdioFile vrp(vrpFile.string().c_str(), CFile::modeRead | CFile::typeBinary);
		CArchive   vrpArchive(&vrp, CArchive::load);
		session.Serialize(vrpArchive);

		// load weather file
		REQUIRE(session.LoadWeatherFile(weatherFile.string().c_str()));

		session.ProcessInputFile(inputFile.string().c_str());

		CHECK(session.m_SnapshotsResetEnabled);
		REQUIRE(session.m_SnapshotsResets.GetCount() == 2);

		auto snapshotDate = (CSnapshotInfo*)session.m_SnapshotsResets.GetHead();
		CHECK_FALSE(snapshotDate->IsScheduled());
		CHECK(snapshotDate->GetDate().GetYear() == 2006);
		CHECK(snapshotDate->GetDate().GetMonth() == 1);
		CHECK(snapshotDate->GetDate().GetDay() == 1);

		snapshotDate = (CSnapshotInfo*)session.m_SnapshotsResets.GetTail();
		CHECK(snapshotDate->IsScheduled());
		CHECK(snapshotDate->GetDate().GetYear() == 2010);
		CHECK(snapshotDate->GetDate().GetMonth() == 04);
		CHECK(snapshotDate->GetDate().GetDay() == 15);

		session.SetSnapshotsDirectory(snapshotsDirectory.string().c_str());

		session.Simulate();

		outputFormatter->WriteToFile(GetFileInTempDirectory("results-autoreset.csv").c_str());
	}

	SECTION("Colony snapshot - BUG - reset on January 1st")
	{
		// load the default VRP file
		bfs::path simulationsDir = GetSimulationsDir();
		bfs::path testsDir = GetTestsDir();
		bfs::path filesDir = simulationsDir / "VarroaPy" / "VarroaPy" / "files";
		bfs::path vrpFile = filesDir / "exe" / "simplified.vrp";

		GlobalOptions::Get().BinaryWeatherFileFormatIdentifier.Set("Rcp85");
		bfs::path weatherFile = simulationsDir / "Rcp85Binary" / "data_46.28125_-119.34375";

		// set global options
		GlobalOptions::Get().ShouldForageDayElectionBasedOnTemperatures.Set(false);
		GlobalOptions::Get().ShouldComputeHourlyTemperatureEstimation.Set(true);
		GlobalOptions::Get().ShouldAdultsAgeBasedOnForageInc.Set(true);

		bfs::path snapshotsDirectory = testsDir / "data" / "snapshots";
		if (!bfs::exists(snapshotsDirectory)) bfs::create_directories(snapshotsDirectory);
		REQUIRE(bfs::exists(snapshotsDirectory));

		// activate cold storage
		auto& csSimulator = CColdStorageSimulator::Get();
		csSimulator.SetEnabled(true);
		csSimulator.SetStartDate(COleDateTime(1970, 10, 15, 0, 0, 0));
		csSimulator.SetEndDate(COleDateTime(1970, 4, 1, 0, 0, 0));

		REQUIRE(bfs::exists(vrpFile));
		REQUIRE(bfs::exists(weatherFile));

		// snapshot
		{
			bfs::path inputFile = testsDir / "data" / "bug-reset-jan-first" / "rcp85-snapshot.txt";
			REQUIRE(bfs::exists(inputFile));

			// create session
			CVarroaPopSession session;

			// set snapshots directory
			session.SetSnapshotsDirectory(snapshotsDirectory.string().c_str());

			// initialize bridge
			VarroaPopCmdBridge bridge(session);
			session.SetBridge(&bridge);

			// set output formatter
			std::unique_ptr<TestOutputFormatter> outputFormatter(new TestOutputFormatter(session));
			session.SetOutputFormatter(outputFormatter.get());

			CStdioFile vrp(vrpFile.string().c_str(), CFile::modeRead | CFile::typeBinary);
			CArchive   vrpArchive(&vrp, CArchive::load);
			session.Serialize(vrpArchive);

			// load weather file - deactivate cold storage for the purpose of loading weather file
			csSimulator.SetEnabled(false);
			REQUIRE(session.LoadWeatherFile(weatherFile.string().c_str()));
			csSimulator.SetEnabled(true);

			session.ProcessInputFile(inputFile.string().c_str());

			outputFormatter->RecordWindow(COleDateTime(2030, 1, 1, 0, 0, 0), COleDateTime(2031, 1, 1, 0, 0, 0));

			session.Simulate();

			const std::string resultsFile = GetFileInTempDirectory("results-richland.csv");

			outputFormatter->WriteToFile(resultsFile.c_str());
			auto items = GetItemsFromFile(resultsFile);

			REQUIRE(items.size() == 366);
			CHECK(items[365].date == "01/01/2031");
			CHECK(items[365].queenStrength == Catch::Detail::Approx(3.0));
			CHECK(items[365].eggs == 0);
			CHECK(items[365].larvae == 0);
			CHECK(items[365].broods == 0);
			CHECK(items[365].adults == 30242);
			CHECK(items[365].foragers == 8296);
			CHECK(items[365].colonySize == 38651);
		}

		// reset
		{
			bfs::path inputFile = testsDir / "data" / "bug-reset-jan-first" / "rcp85-single-year.txt";
			REQUIRE(bfs::exists(inputFile));

			// create session
			CVarroaPopSession session;

			// set snapshots directory
			session.SetSnapshotsDirectory(snapshotsDirectory.string().c_str());

			// initialize bridge
			VarroaPopCmdBridge bridge(session);
			session.SetBridge(&bridge);

			// set output formatter
			std::unique_ptr<TestOutputFormatter> outputFormatter(new TestOutputFormatter(session));
			session.SetOutputFormatter(outputFormatter.get());

			CStdioFile vrp(vrpFile.string().c_str(), CFile::modeRead | CFile::typeBinary);
			CArchive   vrpArchive(&vrp, CArchive::load);
			session.Serialize(vrpArchive);

			// load weather file - deactivate cold storage for the purpose of loading weather file
			csSimulator.SetEnabled(false);
			REQUIRE(session.LoadWeatherFile(weatherFile.string().c_str()));
			csSimulator.SetEnabled(true);

			session.ProcessInputFile(inputFile.string().c_str());

			session.Simulate();

			const std::string resultsFile = GetFileInTempDirectory("results-richland-single-year.csv");

			outputFormatter->WriteToFile(resultsFile.c_str());
			auto items = GetItemsFromFile(resultsFile);

			REQUIRE(items.size() == 366);
			CHECK(items[365].date == "01/01/2031");
			CHECK(items[365].queenStrength == Catch::Detail::Approx(3.0));
			CHECK(items[365].eggs == 0);
			CHECK(items[365].larvae == 0);
			CHECK(items[365].broods == 0);
			CHECK(items[365].adults == 31618);
			CHECK(items[365].foragers == 8706);
			CHECK(items[365].colonySize == 40453);
		}
	}
}

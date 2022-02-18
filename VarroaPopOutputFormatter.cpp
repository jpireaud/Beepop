#include "stdafx.h"

#include "VarroaPopOutputFormatter.h"
#include "GlobalOptions.h"
#include "VarroaPopSession.h"
#include "WeatherEvents.h"

CVarroaPopOutputFormatter::CVarroaPopOutputFormatter(
    CVarroaPopSession& session, CStringList& resultsText, CStringList& resultsHeader, CStringList& resultsFileHeader)
    : COutputFormatter(session), m_ResultsText(resultsText), m_ResultsHeader(resultsHeader),
      m_ResultsFileHeader(resultsFileHeader)
{
}

void CVarroaPopOutputFormatter::Init(CColony& colony)
{
	const char* formatData[] = {
	    "%s",    // "Initial or Date"
	    "%6d",   // Colony size
	    "%8d",   // Adult Drones
	    "%8d",   // Adult Workers
	    "%8d",   // Foragers
	    "%8d",   // Active Foragers
	    "%7d",   // Drones Brood
	    "%6d",   // Wkr Brood
	    "%6d",   // Drone Larv
	    "%6d",   // Wkr Larv
	    "%6d",   // Drone Eggs
	    "%6d",   // Wkr Eggs
	    "%6d",   // Total Eggs
	    "%7.2f", // DD
	    "%6.2f", // L
	    "%6.2f", // N
	    "%8.2f", // P
	    "%7.2f", // dd
	    "%6.2f", // l
	    "%8.2f", // n
	    "%6d",   // Free Mites
	    "%6d",   // DBrood Mites
	    "%6d",   // WBrood Mites
	    "%6.2f", // DMite / Cell
	    "%6.2f", // WMite / Cell
	    "%6d",   // Mites Dying
	    "%6.2f", // Prop Mites Dying
	    "%8.1f", // Colony Pollen
	    "%6.3f", // Conc Pollen Pest
	    "%8.1f", // Colony Nectar
	    "%6.3f", // Conc Nectar Pest
	    "%6d",   // Dead DLarv
	    "%6d",   // Dead WLarv
	    "%6d",   // Dead DAdlt
	    "%6d",   // Dead WAdlt
	    "%6d",   // Dead Foragers
	    "%8.3f", // Queen Strength
	    "%8.3f", // Ave Temp
	    "%6.3f", // Rain
	    "%8.3f", // Min Temp
	    "%8.3f", // Max Temp
	    "%8.2f", // Daylight Hours
	    "%8.2f", // Activity Ratio (Forage Inc)
	    "%8d",   // Forage Day
	    NULL};

	// Set results data format string
	char delimiter = ' ';                // Space delimited
	if (m_Session.m_FieldDelimiter == 1) // Comma Delimited
	{
		delimiter = ',';
	}
	else if (m_Session.m_FieldDelimiter == 2) // Tab Delimited
	{
		delimiter = '\t';
	}

	int formatDataIdx = 0;
	m_ResultsFileFormatStg = formatData[formatDataIdx++];
	while (formatData[formatDataIdx] != NULL)
	{
		m_ResultsFileFormatStg += delimiter;
		m_ResultsFileFormatStg += formatData[formatDataIdx++];
	}

	CString CurSize;

	CurSize.Format("                                                        Capped  Capped						"
	               "																						       "
	               "       Prop           Conc            Conc                                             ");
	m_ResultsFileHeader.AddTail(CurSize);
	CurSize.Format("            Colony  Adult     Adult           Active    Drone   Wkr     Drone  Wkr   Drone  "
	               "Wkr   Total                                                         Free   DBrood WBrood DMite "
	               " WMite  Mites  Mites  Colony  Pollen  Colony  Nectar   Dead   Dead   Dead   Dead   Dead    "
	               "Queen      Ave           Min     Max      Daylight  Forage  Forage");
	m_ResultsFileHeader.AddTail(CurSize);

	CurSize.Format("     Date   Size    Drones    Wkr     Forgrs  Forgrs    Brood   Brood   Larv   Larv  Eggs   "
	               "Eggs  Eggs      DD      L      N      P       dd       l       n    Mites  Mites  Mites  /Cell "
	               " /Cell  Dying  Dying  Pollen  Pest    Nectar  Pest     DLarv  WLarv  DAdlt  WAdlt  Forgrs  "
	               "Strength   Temp  Rain    Temp    Temp     Hours     Inc     Day");
	// Append additional command name if InOut statistics are required
	if (GlobalOptions::Get().ShouldOutputInOutCounts())
	{
		CurSize.Format(
		    "%s NewWorkerEggs NewDroneEggs WorkerEggsToLarvae DroneEggsToLarvae WorkerLarvaeToBrood "
		    "DroneLarvaeToBrood WorkerBroodToAdult DroneBroodToAdult DroneAdultsDying "
		    "ForagersKilledByPesticides WorkerAdultToForagers WinterMortalityForagersLoss ForagersDying",
		    CurSize);
	}
	m_ResultsFileHeader.AddTail(CurSize);

	CurSize.Format(
	    m_ResultsFileFormatStg,
	    // event.GetDateStg("%m/%d/%Y"),
	    "Initial   ",                           // "Initial or Date"
	    colony.GetColonySize(),                 // Colony size
	    colony.Dadl.GetQuantity(),              // Adult Drones
	    colony.Wadl()->GetQuantity(),           // Adult Workers
	    colony.Foragers()->GetQuantity(),       // Forgers
	    colony.Foragers()->GetActiveQuantity(), // Active Forgers
	    colony.CapDrn.GetQuantity(),            // Drones Brood
	    colony.CapWkr.GetQuantity(),            // Wkr Brood
	    colony.Dlarv.GetQuantity(),             // Drone Larv
	    colony.Wlarv.GetQuantity(),             // Wkr Larv
	    colony.Deggs.GetQuantity(),             // Drone Eggs
	    colony.Weggs.GetQuantity(),             // Wkr Eggs
	    colony.GetEggsToday(),                  // Total Eggs
	    colony.GetDDToday(),                    // DD
	    colony.GetLToday(),                     // L
	    colony.GetNToday(),                     // N
	    colony.GetPToday(),                     // P
	    colony.GetddToday(),                    // dd
	    colony.GetlToday(),                     // l
	    colony.GetnToday(),                     // n
	    colony.RunMite.GetTotal(),              // Free Mites
	    colony.CapDrn.GetMiteCount(),           // DBrood Mites
	    colony.CapWkr.GetMiteCount(),           // WBrood Mites
	    colony.CapDrn.GetMitesPerCell(),        // DMite / Cell
	    colony.CapWkr.GetMitesPerCell(),        // WMite / Cell
	    0,                                      // Mites Dying
	    0.0,                                    // Prop Mites Dying
	    0.0,                                    // Colony Pollen
	    0.0,                                    // Conc Pollen Pest
	    0.0,                                    // Colony Nectar
	    0.0,                                    // Conc Nectar Pest
	    0,                                      // Dead DLarv
	    0,                                      // Dead WLarv
	    0,                                      // Dead DAdlt
	    0,                                      // Dead WAdlt
	    0,                                      // Dead Foragers
	    colony.queen.GetQueenStrength(),        // Queen Strength
	    0.0,                                    // Ave Temp
	    0.0,                                    // Rain
	    0.0,                                    // Min Temp
	    0.0,                                    // Max Temp
	    0.0,                                    // Daylight Hours
	    0.0,                                    // Activity Ratio
	    0                                       // Forage Day
	);
	// Append additional command name if InOut statistics are required
	if (GlobalOptions::Get().ShouldOutputInOutCounts())
	{
		CurSize.Format(
		    "%s %5d %5d %5d %5d %5d %5d %5d %5d %5d %5d %5d %5d %5d", CurSize, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	}
	m_ResultsText.AddTail(CurSize);
}

void CVarroaPopOutputFormatter::Record(CColony& colony, CEvent& event)
{
	double PropMiteDeath =
	    colony.GetMitesDyingThisPeriod() + colony.GetTotalMiteCount() > 0
	        ? colony.GetMitesDyingThisPeriod() / double(colony.GetMitesDyingThisPeriod() + colony.GetTotalMiteCount())
	        : 0;

	double ColPollen = colony.m_Resources.GetPollenQuantity(); // In Grams
	double ColNectar = colony.m_Resources.GetNectarQuantity();
	double NectarPesticideConc = colony.m_Resources.GetNectarPesticideConcentration() * 1000000;
	double PollenPesticideConc =
	    colony.m_Resources.GetPollenPesticideConcentration() * 1000000; // convert from g/g to ug/g

	CString CurSize;
	CurSize.Format(
	    m_ResultsFileFormatStg,                 //
	    event.GetDateStg("%m/%d/%Y"),           //
	    colony.GetColonySize(),                 //
	    colony.Dadl.GetQuantity(),              //
	    colony.Wadl()->GetQuantity(),           //
	    colony.Foragers()->GetQuantity(),       //
	    colony.Foragers()->GetActiveQuantity(), //
	    colony.CapDrn.GetQuantity(),            //
	    colony.CapWkr.GetQuantity(),            //
	    colony.Dlarv.GetQuantity(),             //
	    colony.Wlarv.GetQuantity(),             //
	    colony.Deggs.GetQuantity(),             //
	    colony.Weggs.GetQuantity(),             //
	    colony.GetEggsToday(),                  //
	    colony.GetDDToday(),                    //
	    colony.GetLToday(),                     //
	    colony.GetNToday(),                     //
	    colony.GetPToday(),                     //
	    colony.GetddToday(),                    //
	    colony.GetlToday(),                     //
	    colony.GetnToday(),                     //
	    colony.RunMite.GetTotal(),              //
	    colony.CapDrn.GetMiteCount(),           //
	    colony.CapWkr.GetMiteCount(),           //
	    colony.CapDrn.GetMitesPerCell(),        //
	    colony.CapWkr.GetMitesPerCell(),        //
	    colony.GetMitesDyingThisPeriod(),       //
	    PropMiteDeath,                          //
	    ColPollen,                              //
	    PollenPesticideConc,                    //
	    ColNectar,                              //
	    NectarPesticideConc,                    //
	    colony.m_DeadDroneLarvaePesticide,      //
	    colony.m_DeadWorkerLarvaePesticide,     //
	    colony.m_DeadDroneAdultsPesticide,      //
	    colony.m_DeadWorkerAdultsPesticide,     //
	    colony.m_DeadForagersPesticide,         //
	    colony.queen.GetQueenStrength(),        //
	    event.GetTemp(),                        //
	    event.GetRainfall(),                    //
	    event.GetMinTemp(),                     //
	    event.GetMaxTemp(),                     //
	    event.GetDaylightHours(),               //
	    event.GetForageInc(),                   //
	    event.IsForageDay()                     //
	);
	// Append additional command name if InOut statistics are required
	if (GlobalOptions::Get().ShouldOutputInOutCounts())
	{
		CurSize.Format(
		    "%s %5d %5d %5d %5d %5d %5d %5d %5d %5d %5d %5d %5d %5d", CurSize, colony.m_InOutEvent.m_NewWEggs,
		    colony.m_InOutEvent.m_NewDEggs, colony.m_InOutEvent.m_WEggsToLarv, colony.m_InOutEvent.m_DEggsToLarv,
		    colony.m_InOutEvent.m_WLarvToBrood, colony.m_InOutEvent.m_DLarvToBrood, colony.m_InOutEvent.m_WBroodToAdult,
		    colony.m_InOutEvent.m_DBroodToAdult, colony.m_InOutEvent.m_DeadDAdults,
		    colony.m_InOutEvent.m_ForagersKilledByPesticide, colony.m_InOutEvent.m_WAdultToForagers,
		    colony.m_InOutEvent.m_WinterMortalityForagersLoss, colony.m_InOutEvent.m_DeadForagers);
	}
	m_ResultsText.AddTail(CurSize);
}

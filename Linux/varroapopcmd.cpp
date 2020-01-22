#include "varroapopcmd.h"

#include <iostream>

VarroaPopCmd::VarroaPopCmd()
{
	m_DispWeeklyData = false;  // Initially Set to False

	// Defaults for results file
	m_ColTitles = true;
	m_Version = true;
	m_InitConds = false;
	m_WeatherColony = false;
	m_FieldDelimiter = 0; // Fixed width fields


	// Graph Selection Initial Values
	m_AD = TRUE;
	m_AW = TRUE;
	m_CS = TRUE;
	m_DB = FALSE;
	m_DE = FALSE;
	m_DL = FALSE;
	m_F = FALSE;
	m_MDB = FALSE;
	m_MWB = FALSE;
	m_PDB = FALSE;
	m_PWB = FALSE;
	m_PRM = FALSE;
	m_RM = FALSE;
	m_WB = FALSE;
	m_WE = FALSE;
	m_WL = FALSE;
	m_IM = FALSE;
	m_MD = FALSE;
	m_PMD = FALSE;
	m_TE = FALSE;
	m_DD = FALSE;
	m_L = FALSE;
	m_N = FALSE;
	m_P = FALSE;
	m_dd = FALSE;
	m_l = FALSE;
	m_n = FALSE;
	m_AutoScaleChart = 0;
	m_YAxisMin = 0;
	m_YAxisMax = 0;

	availableFilesList.RemoveAll();
	selectedFilesList.RemoveAll();
	selectedFileIndex = -1;


	// Add Header Strings
	m_ResultsHeader.AddTail("Date");
	m_ResultsHeader.AddTail("ColSze");
	m_ResultsHeader.AddTail("AdDrns");
	m_ResultsHeader.AddTail("AdWkrs");
	m_ResultsHeader.AddTail("Forgr");
	m_ResultsHeader.AddTail("DrnBrd");
	m_ResultsHeader.AddTail("WkrBrd");
	m_ResultsHeader.AddTail("DrnLrv");
	m_ResultsHeader.AddTail("WkrLrv");
	m_ResultsHeader.AddTail("DrnEggs");
	m_ResultsHeader.AddTail("WkrEggs");
	m_ResultsHeader.AddTail("TotalEggs");
	m_ResultsHeader.AddTail("DD");
	m_ResultsHeader.AddTail("L");
	m_ResultsHeader.AddTail("N");
	m_ResultsHeader.AddTail("P");
	m_ResultsHeader.AddTail("dd");
	m_ResultsHeader.AddTail("l");
	m_ResultsHeader.AddTail("n");
	m_ResultsHeader.AddTail("FreeMts");
	m_ResultsHeader.AddTail("DBrdMts");
	m_ResultsHeader.AddTail("WBrdMts");
	m_ResultsHeader.AddTail("Mts/DBrd");
	m_ResultsHeader.AddTail("Mts/WBrd");
	m_ResultsHeader.AddTail("Mts Dying");
	m_ResultsHeader.AddTail("PropMts Dying");
	m_ResultsHeader.AddTail("ColPollen(g)");
	m_ResultsHeader.AddTail("PPestConc(ug/g)");
	m_ResultsHeader.AddTail("ColNectar(g)");
	m_ResultsHeader.AddTail("NPestConc(ug/g)");
	m_ResultsHeader.AddTail("Dead DLarv");
	m_ResultsHeader.AddTail("Dead WLarv");
	m_ResultsHeader.AddTail("Dead DAdults");
	m_ResultsHeader.AddTail("Dead WAdults");
	m_ResultsHeader.AddTail("Dead Foragers");
	m_ResultsHeader.AddTail("Queen Strength");
	m_ResultsHeader.AddTail("Temp (DegC)");
	m_ResultsHeader.AddTail("Precip");


	m_ImmigrationType = "None";
	m_TotImmigratingMites = 0;
	m_ImmMitePctResistant = 0;
	m_ImmigrationStartDate = COleDateTime(1999,1,1,0,0,0);
	m_ImmigrationEndDate = COleDateTime(1999,1,1,0,0,0);
	m_ImmigrationEnabled = false;
	m_SimulationComplete = false;
	m_ResultsReady = false;
	m_RQEggLayingDelay = 10;
	m_RQEnableReQueen = false;
	m_RQScheduled = 1;
	m_RQQueenStrength = 5;
	m_RQOnce = 0;
	m_VTTreatmentDuration = 0;
	m_VTEnable = false;
	m_VTMortality = 0;
	m_InitMitePctResistant = 0;

	m_SPEnable = FALSE;
	m_SPInitial = 0;

	m_CombRemoveDate = COleDateTime(1999,1,1,0,0,0);
	m_CombRemoveEnable = FALSE;
	m_CombRemovePct = 0;
    
	m_pWeather = new CWeatherEvents; // Create the WeatherEvents
	m_SessionLoaded = false;
	m_WeatherLoaded = false;
}

VarroaPopCmd::~VarroaPopCmd()
{
	m_MiteTreatments.ClearAll();
	m_pWeather->ClearAllEvents();
	delete m_pWeather;
}

void VarroaPopCmd::SetResultsFileName(CString resultsFilename)
{
	m_ResultsFileName = resultsFilename;
}

//  ProcessInputFile reads the lines in the command line input file and makes the appropriate
//  changes to internal variables based on the name and the value contained in the line.  The function is called
//  after the .vrp file is loaded.
//
//  Purists would not like the use of so many if statements because it requires evaluation of a lot of invalid
//  ifs until a valid if is found.  This seemed the most clear to me since it is only used once per execution of VP
//  and because we are selecting on a string, we can't use a switch statement.  Also, it's pretty clear how to read and add.
//
//  To expose a new variable to the input file, add a new if clause with the lower case version of the name string
//  and update the appropriate internal variables.  
void VarroaPopCmd::ProcessInputFile(CString FileName)
{
	try
	{
		theColony.m_RQQueenStrengthArray.RemoveAll();
		CString Line;
		CString Name;
		CString Value;
		CStdioFile InputFile(FileName,CFile::shareDenyNone|CFile::modeRead);
		while (InputFile.ReadString(Line))
		{
			int leftchars = Line.Find("=");
			int rightchars = Line.GetLength() - leftchars - 1;
			if ((leftchars <1) || (rightchars <1)) continue; // Go to next line
			Name = Line.Left(leftchars);
			Value = Line.Right(rightchars);
			Name.Trim();
			Value.Trim();
			Name.MakeLower();
			Value.MakeLower();
			TRACE("Name = %s,  Value = %s\n",Name,Value);

			// switch structure to allocate Name/Value to specific Initial Condition
			if (Name == "weatherfilename")
			{
				//Updated to set m_WeatherLoaded in 3.2.8.16. 
				m_WeatherLoaded = m_pWeather->LoadWeatherFile(Value);
				if (m_WeatherLoaded)
				{
					m_WeatherFileName = Value;
				}
				else
				{
					CString msg = "  Processing Input File: The Specified Weather file  ";
					msg += Value+" was not found\n";
					msg += "You will have to specify one before you run a simulation";
                    std::cerr << msg << std::endl;
				}
				continue;
			}
			if (Name == "simstart")
			{
				COleDateTime theDate;
				theDate.ParseDateTime(Value);
				COleDateTime tempDate(theDate.GetYear(),theDate.GetMonth(),theDate.GetDay(),0,0,0);
				m_SimStartTime = tempDate;
				SetSimStart(m_SimStartTime);
				continue;
			}
			if (Name == "simend")
			{
				COleDateTime theDate;
				theDate.ParseDateTime(Value);
				COleDateTime tempDate(theDate.GetYear(),theDate.GetMonth(),theDate.GetDay(),0,0,0);
				m_SimEndTime = tempDate;
				SetSimEnd(m_SimEndTime);
				continue;
			}
			if (Name == "icdroneadults")
			{
				theColony.m_InitCond.m_droneAdultsField = atoi(Value);
				continue;
			}
			if (Name == "icworkeradults")
			{
				theColony.m_InitCond.m_workerAdultsField = atoi(Value);
				continue;
			}
			if (Name == "icdronebrood")
			{
				theColony.m_InitCond.m_droneBroodField = atoi(Value);
				continue;
			}
			if (Name == "icworkerbrood")
			{
				theColony.m_InitCond.m_workerBroodField = atoi(Value);
				continue;
			}
			if (Name == "icdronelarvae")
			{
				theColony.m_InitCond.m_droneLarvaeField = atoi(Value);
				continue;
			}
			if (Name == "icworkerlarvae")
			{
				theColony.m_InitCond.m_workerLarvaeField = atoi(Value);
				continue;
			}
			if (Name == "icdroneeggs")
			{
				theColony.m_InitCond.m_droneEggsField = atoi(Value);
				continue;
			}
			if (Name == "icworkereggs")
			{
				theColony.m_InitCond.m_workerEggsField = atoi(Value);
				continue;
			}
			if (Name == "icqueenstrength")
			{
				theColony.m_InitCond.m_QueenStrength = atof(Value);
				continue;
			}
			if (Name == "icforagerlifespan")
			{
				theColony.m_InitCond.m_ForagerLifespan = atoi(Value);
				continue;
			}
			if (Name == "icdroneadultinfest")
			{
				theColony.m_InitCond.m_droneAdultInfestField = float(atof(Value));
				continue;
			}
			if (Name == "icdronebroodinfest")
			{
				theColony.m_InitCond.m_droneBroodInfestField = float(atof(Value));
				continue;
			}
			if (Name == "icdronemiteoffspring")
			{
				theColony.m_InitCond.m_droneMiteOffspringField = float(atof(Value));
				continue;
			}
			if (Name == "icdronemitesurvivorship")
			{
				theColony.m_InitCond.m_droneMiteSurvivorshipField = float(atof(Value));
				continue;
			}
			if (Name == "icworkeradultinfest")
			{
				theColony.m_InitCond.m_workerAdultInfestField = float(atof(Value));
				continue;
			}
			if (Name == "icworkerbroodinfest")
			{
				theColony.m_InitCond.m_workerBroodInfestField = float(atof(Value));
				continue;
			}
			if (Name == "icworkermiteoffspring")
			{
				theColony.m_InitCond.m_workerMiteOffspring = float(atof(Value));
				continue;
			}
			if (Name == "icworkermitesurvivorship")
			{
				theColony.m_InitCond.m_workerMiteSurvivorship = float(atof(Value));
				continue;
			}
			if (Name == "plotnone")
			{
				m_AD = FALSE;
				m_AW = FALSE;
				m_CS = FALSE;
				m_DB = FALSE;
				m_DE = FALSE;
				m_DL = FALSE;
				m_F = FALSE;
				m_TM = FALSE;
				m_MDB = FALSE;
				m_MWB = FALSE;
				m_PDB = FALSE;
				m_PWB = FALSE;
				m_PRM = FALSE;
				m_RM = FALSE;
				m_WB = FALSE;
				m_WE = FALSE;
				m_WL = FALSE;
				m_IM = FALSE;
				m_TE = FALSE;
				m_DD = FALSE;
				m_L = FALSE;
				m_N = FALSE;
				m_P = FALSE;
				m_dd = FALSE;
				m_l = FALSE;
				m_n = FALSE;
				continue;
			}
			if (Name == "plotad")
			{
				m_AD = (Value=="true")?TRUE:FALSE;
				continue;
			}
			if (Name == "plotaw")
			{
				m_AW = (Value=="true")?TRUE:FALSE;
				continue;
			}
			if (Name == "plotcs")
			{
				m_CS = (Value=="true")?TRUE:FALSE;
				continue;
			}
			if (Name == "plotdb")
			{
				m_DB = (Value=="true")?TRUE:FALSE;
				continue;
			}
			if (Name == "plotde")
			{
				m_DE = (Value=="true")?TRUE:FALSE;
				continue;
			}
			if (Name == "plotdl")
			{
				m_DL = (Value=="true")?TRUE:FALSE;
				continue;
			}
			if (Name == "plotf")
			{
				m_F = (Value=="true")?TRUE:FALSE;
				continue;
			}
			if (Name == "plottm")
			{
				m_TM = (Value=="true")?TRUE:FALSE;
				continue;
			}
			else if (Name == "plotmdb")
			{
				m_MDB = (Value=="true")?TRUE:FALSE;
				continue;
			}
			if (Name == "plotmwb")
			{
				m_MWB = (Value=="true")?TRUE:FALSE;
				continue;
			}
			if (Name == "plotpdb")
			{
				m_PDB = (Value=="true")?TRUE:FALSE;
				continue;
			}
			if (Name == "plotpwb")
			{
				m_PWB = (Value=="true")?TRUE:FALSE;
				continue;
			}
			if (Name == "plotprm")
			{
				m_PRM = (Value=="true")?TRUE:FALSE;
				continue;
			}
			if (Name == "plotrm")
			{
				m_RM = (Value=="true")?TRUE:FALSE;
				continue;
			}
			if (Name == "plotwb")
			{
				m_WB = (Value=="true")?TRUE:FALSE;
				continue;
			}
			if (Name == "plotwe")
			{
				m_WE = (Value=="true")?TRUE:FALSE;
				continue;
			}
			if (Name == "plotwl")
			{
				m_WL = (Value=="true")?TRUE:FALSE;
				continue;
			}
			else if (Name == "plotim")
			{
				m_IM = (Value=="true")?TRUE:FALSE;
				continue;
			}
			if (Name == "denone")
			{
				if (Value=="true") theColony.AddDiscreteEvent("07/01/1999",DE_NONE);
				continue;
			}
			if (Name == "deswarm")
			{
				if (Value=="true") theColony.AddDiscreteEvent("07/01/1999",DE_SWARM);
				continue;
			}
			if (Name == "dechalkbrood")
			{
				if (Value=="true") theColony.AddDiscreteEvent("07/01/1999",DE_CHALKBROOD);				
				continue;
			}
			if (Name == "deresource")
			{
				if (Value=="true") theColony.AddDiscreteEvent("07/01/1999",DE_RESOURCEDEP);				
				continue;
			}
			if (Name == "desupercedure")
			{
				if (Value=="true") theColony.AddDiscreteEvent("07/01/1999",DE_SUPERCEDURE);				
				continue;
			}
			if (Name == "depesticide")
			{
				if (Value=="true") theColony.AddDiscreteEvent("07/01/1999",DE_PESTICIDE);				
				continue;
			}
			if (Name == "immtype")
			{
				m_ImmigrationType = Value;
				continue;
			}
			if (Name == "totalimmmites")
			{
				m_TotImmigratingMites = atoi(Value);
				continue;
			}
			if (Name == "pctimmmitesresistant")
			{
				m_ImmMitePctResistant = atof(Value);
				m_TotImmigratingMites.SetPctResistant(m_ImmMitePctResistant);
				continue;
			}
			if (Name == "immstart")
			{
				COleDateTime theDate;
				theDate.ParseDateTime(Value);
				m_ImmigrationStartDate = theDate;
				continue;
			}
			if (Name == "immend")
			{
				COleDateTime theDate;
				theDate.ParseDateTime(Value);
				m_ImmigrationEndDate = theDate;
				continue;
			}
			if (Name == "immenabled")
			{
				m_ImmigrationEnabled = (Value == "true")?true:false;
				continue;
			}
			if (Name == "rqegglaydelay")
			{
				m_RQEggLayingDelay = UINT(atoi(Value));
				continue;
			}
			if (Name == "rqwkrdrnratio")
			{
				m_RQWkrDrnRatio = atof(Value);
				continue;
			}
			if (Name == "rqrequeendate")
			{
				COleDateTime theDate;
				theDate.ParseDateTime(Value);
				COleDateTime tempDate(theDate.GetYear(),theDate.GetMonth(),theDate.GetDay(),0,0,0);
				m_RQReQueenDate = tempDate;
				continue;
			}
			if (Name == "rqenablerequeen")
			{
				m_RQEnableReQueen = (Value == "true")?true:false;	
				continue;
			}
			if (Name == "rqscheduled")
			{
				m_RQScheduled = (Value == "true")?0:1;
				continue;
			}
			if (Name == "rqqueenstrength")
				// This value is placed into an array which is used in Colony::RequeenIfNeeded.  Each occurance of this parameter name in the 
				// input file will result in another requeen strength value being added to the end of the array.
				// Thus rqqueenstrength doesn't overwrite the previous value if supplied more than once
			{
				m_RQQueenStrength = atof(Value);
				theColony.m_RQQueenStrengthArray.Add(m_RQQueenStrength);				
				continue;
			}
			if (Name == "rqonce")
			{
				m_RQOnce = (Value == "true")?0:1;
				continue;
			}
			if (Name == "vttreatmentduration")
			{
				m_VTTreatmentDuration = UINT(atoi(Value));
				continue;
			}
			if (Name == "vtmortality")
			{
				m_VTMortality = UINT(atoi(Value));
				continue;
			}
			if (Name == "vtenable")
			{
				m_VTEnable = (Value == "true")?TRUE:FALSE;				
				continue;
			}
			if (Name == "vttreatmentstart")
			{
				COleDateTime theDate;
				if(theDate.ParseDateTime(Value)) // Verifies this is a valid date
				{
					COleDateTime tempDate(theDate.GetYear(),theDate.GetMonth(),theDate.GetDay(),0,0,0);
					m_VTTreatmentStart = tempDate;
				}
				continue;
			}
			if (Name == "initmitepctresistant")
			{
				m_InitMitePctResistant = atof(Value);
				continue;
			}
			if (Name == "ainame")
			{
				// TEST TEST TEST  Be sure pointers all work and no issue with name not found
				//AIItem pItem;
				//AIItem* pEPAItem;
				//pEPAItem = theColony.m_EPAData.GetAIItemPtr(Value);
				//theColony.m_EPAData.SetCurrentAIItem(pEPAItem);
				continue;
			}
			if (Name == "aiadultslope")
			{
				theColony.m_EPAData.m_AI_AdultSlope = atof(Value);
				continue;
			}
			if (Name == "aiadultld50")
			{
				theColony.m_EPAData.m_AI_AdultLD50 = atof(Value);
				continue;
			}
			if (Name == "aiadultslopecontact")
			{
				theColony.m_EPAData.m_AI_AdultSlope_Contact = atof(Value);
				continue;
			}
			if (Name == "aiadultld50contact")
			{
				theColony.m_EPAData.m_AI_AdultLD50_Contact = atof(Value);
				continue;
			}
			if (Name == "ailarvaslope") // note: this was incorrectly "ailarvatslope" in 3.2.5.7
			{
				theColony.m_EPAData.m_AI_LarvaSlope = atof(Value);
				continue;
			}
			if (Name == "ailarvald50")
			{
				theColony.m_EPAData.m_AI_LarvaLD50 = atof(Value);
				continue;
			}
			if (Name == "aikow")
			{
				theColony.m_EPAData.m_AI_KOW = atof(Value);
				continue;
			}
			if (Name == "aikoc")
			{
				theColony.m_EPAData.m_AI_KOC = atof(Value);
				continue;
			}
			if (Name == "aihalflife")
			{
				theColony.m_EPAData.m_AI_HalfLife = atof(Value);
				continue;
			}
			if (Name == "aicontactfactor")
			{
				theColony.m_EPAData.m_AI_ContactFactor = atof(Value);
				continue;
			}
			if (Name == "cl4pollen")
			{
				theColony.m_EPAData.m_C_L4_Pollen = atof(Value);
				continue;
			}
			if (Name == "cl4nectar")
			{
				theColony.m_EPAData.m_C_L4_Nectar = atof(Value);
				continue;
			}
			if (Name == "cl5pollen")
			{
				theColony.m_EPAData.m_C_L5_Pollen = atof(Value);
				continue;
			}
			if (Name == "cl5nectar")
			{
				theColony.m_EPAData.m_C_L5_Nectar = atof(Value);
				continue;
			}
			if (Name == "cldpollen")
			{
				theColony.m_EPAData.m_C_LD_Pollen = atof(Value);
				continue;
			}
			if (Name == "cldnectar")
			{
				theColony.m_EPAData.m_C_LD_Nectar = atof(Value);
				continue;
			}
			if (Name == "ca13pollen")
			{
				theColony.m_EPAData.m_C_A13_Pollen = atof(Value);
				continue;
			}
			if (Name == "ca13nectar")
			{
				theColony.m_EPAData.m_C_A13_Nectar = atof(Value);
				continue;
			}
			if (Name == "ca410pollen")
			{
				theColony.m_EPAData.m_C_A410_Pollen = atof(Value);
				continue;
			}
			if (Name == "ca410nectar")
			{
				theColony.m_EPAData.m_C_A410_Nectar = atof(Value);
				continue;
			}
			if (Name == "ca1120pollen")
			{
				theColony.m_EPAData.m_C_A1120_Pollen = atof(Value);
				continue;
			}
			if (Name == "ca1120nectar")
			{
				theColony.m_EPAData.m_C_A1120_Nectar = atof(Value);
				continue;
			}
			if (Name == "cadpollen")
			{
				theColony.m_EPAData.m_C_AD_Pollen = atof(Value);
				continue;
			}
			if (Name == "cadnectar")
			{
				theColony.m_EPAData.m_C_AD_Nectar = atof(Value);
				continue;
			}
			if (Name == "cforagerpollen")
			{
				theColony.m_EPAData.m_C_Forager_Pollen = atof(Value);
				continue;
			}
			if (Name == "cforagernectar")
			{
				theColony.m_EPAData.m_C_Forager_Nectar = atof(Value);
				continue;
			}
			if (Name == "ipollentrips")
			{
				theColony.m_EPAData.m_I_PollenTrips = (int)atof(Value); // no fail on float input but convert to int
				continue;
			}
			if (Name == "inectartrips")
			{
				theColony.m_EPAData.m_I_NectarTrips = (int)atof(Value);
				continue;
			}
			if (Name == "ipercentnectarforagers")
			{
				theColony.m_EPAData.m_I_PercentNectarForagers = atof(Value);
				continue;
			}
			if (Name == "ipollenload")
			{
				theColony.m_EPAData.m_I_PollenLoad = atof(Value);
				continue;
			}
			if (Name == "inectarload")
			{
				theColony.m_EPAData.m_I_NectarLoad = atof(Value);
				continue;
			}
			if (Name == "foliarenabled")
			{
				theColony.m_EPAData.m_FoliarEnabled = (Value == "true")?true:false;
				continue;
			}
			if (Name == "soilenabled")
			{
				theColony.m_EPAData.m_SoilEnabled = (Value == "true")?true:false;
				continue;
			}
			if (Name == "seedenabled")
			{
				theColony.m_EPAData.m_SeedEnabled = (Value == "true")?true:false;
				continue;
			}
			if (Name == "eapprate")
			{
				theColony.m_EPAData.m_E_AppRate = atof(Value);
				continue;
			}
			if (Name == "esoiltheta")
			{
				theColony.m_EPAData.m_E_SoilTheta = atof(Value);
				continue;
			}
			if (Name == "esoilp")
			{
				theColony.m_EPAData.m_E_SoilP = atof(Value);
				continue;
			}
			if (Name == "esoilfoc")
			{
				theColony.m_EPAData.m_E_SoilFoc = atof(Value);
				continue;
			}
			if (Name == "esoilconcentration")
			{
				theColony.m_EPAData.m_E_SoilConcentration = atof(Value);
				continue;
			}
			if (Name == "eseedconcentration")
			{
				theColony.m_EPAData.m_E_SeedConcentration = atof(Value);
				continue;
			}
			if (Name == "foliarappdate")
			{
				COleDateTime theDate;
				if( theDate.ParseDateTime(Value) ) // Verify this Value is a valid date expression
				{
					COleDateTime tempDate(theDate.GetYear(),theDate.GetMonth(),theDate.GetDay(),0,0,0);
					theColony.m_EPAData.m_FoliarAppDate = tempDate;
				}
				continue;
			}
			if (Name == "foliarforagebegin")
			{
				COleDateTime theDate;
				theDate.ParseDateTime(Value);
				COleDateTime tempDate(theDate.GetYear(),theDate.GetMonth(),theDate.GetDay(),0,0,0);
				theColony.m_EPAData.m_FoliarForageBegin = tempDate;
				continue;
			}
			if (Name == "foliarforageend")
			{
				COleDateTime theDate;
				if( theDate.ParseDateTime(Value) ) // Verify this Value is a valid date expression
				{
					COleDateTime tempDate(theDate.GetYear(),theDate.GetMonth(),theDate.GetDay(),0,0,0);
					theColony.m_EPAData.m_FoliarForageEnd = tempDate;
				}
				continue;
			}
			if (Name == "soilforagebegin")
			{
				COleDateTime theDate;
				if( theDate.ParseDateTime(Value) ) // Verify this Value is a valid date expression
				{
					COleDateTime tempDate(theDate.GetYear(),theDate.GetMonth(),theDate.GetDay(),0,0,0);
					theColony.m_EPAData.m_SoilForageBegin = tempDate;
				}
				continue;
			}
			if (Name == "soilforageend")
			{
				COleDateTime theDate;
				if( theDate.ParseDateTime(Value) ) // Verify this Value is a valid date expression
				{
					COleDateTime tempDate(theDate.GetYear(),theDate.GetMonth(),theDate.GetDay(),0,0,0);
					theColony.m_EPAData.m_SoilForageEnd = tempDate;
				}
				continue;
			}
			if (Name == "seedforagebegin")
			{
				COleDateTime theDate;
				if( theDate.ParseDateTime(Value) ) // Verify this Value is a valid date expression
				{
					COleDateTime tempDate(theDate.GetYear(),theDate.GetMonth(),theDate.GetDay(),0,0,0);
					theColony.m_EPAData.m_SeedForageBegin = tempDate;
				}
				continue;
			}
			if (Name == "seedforageend")
			{
				COleDateTime theDate;
				if( theDate.ParseDateTime(Value) ) // Verify this Value is a valid date expression
				{
					COleDateTime tempDate(theDate.GetYear(),theDate.GetMonth(),theDate.GetDay(),0,0,0);
					theColony.m_EPAData.m_SeedForageEnd = tempDate;
				}
				continue;
			}
			if (Name == "necpolfileenable")
			{
				theColony.m_NutrientCT.m_NutrientContEnabled = (Value == "true") ? true : false;
				continue;
			}
			if (Name == "necpolfilename")
			{
				theColony.m_NutrientCT.m_ContaminantFileName = Value;
				continue;
			}
			if (Name == "initcolnectar")
			{
				theColony.m_ColonyNecInitAmount = atof(Value);
				continue;
			}
			if (Name == "initcolpollen")
			{
				theColony.m_ColonyPolInitAmount = atof(Value);
				continue;
			}
			if (Name == "maxcolnectar")
			{
				theColony.m_ColonyNecMaxAmount = atof(Value);
				continue;
			}
			if (Name == "maxcolpollen")
			{
				theColony.m_ColonyPolMaxAmount = atof(Value);
				continue;
			}
			if (Name == "suppollenenable")
			{
				theColony.m_SuppPollenEnabled = (Value == "true") ? true : false;
				continue;
			}
			if (Name == "suppollenamount")
			{
				theColony.m_SuppPollen.m_StartingAmount = atof(Value);
				continue;
			}
			if (Name == "suppollenbegin")
			{
				COleDateTime theDate;
				if( theDate.ParseDateTime(Value) ) // Verify this Value is a valid date expression
				{
					COleDateTime tempDate(theDate.GetYear(),theDate.GetMonth(),theDate.GetDay(),0,0,0);
					theColony.m_SuppPollen.m_BeginDate = tempDate;
				}
				continue;
			}
			if (Name == "suppollenend")
			{
				COleDateTime theDate;
				if( theDate.ParseDateTime(Value) ) // Verify this Value is a valid date expression
				{
					COleDateTime tempDate(theDate.GetYear(),theDate.GetMonth(),theDate.GetDay(),0,0,0);
					theColony.m_SuppPollen.m_EndDate = tempDate;
				}
				continue;
			}
			if (Name == "supnectarenable")
			{
				theColony.m_SuppNectarEnabled = (Value == "true")?true:false;
				continue;
			}
			if (Name == "supnectaramount")
			{
				theColony.m_SuppNectar.m_StartingAmount = atof(Value);
				continue;
			}
			if (Name == "supnectarbegin")
			{
				COleDateTime theDate;
				if( theDate.ParseDateTime(Value) ) // Verify this Value is a valid date expression
				{
					COleDateTime tempDate(theDate.GetYear(),theDate.GetMonth(),theDate.GetDay(),0,0,0);
					theColony.m_SuppNectar.m_BeginDate = tempDate;
				}
				continue;
			}
			if (Name == "supnectarend")
			{

				COleDateTime theDate;
				if( theDate.ParseDateTime(Value) ) // Verify this Value is a valid date expression
				{
					COleDateTime tempDate(theDate.GetYear(),theDate.GetMonth(),theDate.GetDay(),0,0,0);
					theColony.m_SuppNectar.m_EndDate = tempDate;
				}
				continue;
			}
			if (Name == "foragermaxprop")
			{
				theColony.foragers.SetPropActualForagers(atof(Value));
				continue;
			}
			if (Name == "needresourcestolive")
			{
				theColony.m_NoResourceKillsColony = (Value == "true") ? true : false;
				continue;

			}
			if (Name == "plotte")
			{
				m_TE = (Value == "true") ? TRUE : FALSE;
				continue;
			}
			if (Name == "plotDD")
			{
				m_DD = (Value == "true") ? TRUE : FALSE;
				continue;
			}
			if (Name == "plotN")
			{
				m_N = (Value == "true") ? TRUE : FALSE;
				continue;
			}
			if (Name == "plotL")
			{
				m_L = (Value == "true") ? TRUE : FALSE;
				continue;
			}
			if (Name == "plotP")
			{
				m_P = (Value == "true") ? TRUE : FALSE;
				continue;
			}
			if (Name == "plotdd")
			{
				m_dd = (Value == "true") ? TRUE : FALSE;
				continue;
			}
			if (Name == "plotl")
			{
				m_l = (Value == "true") ? TRUE : FALSE;
				continue;
			}
			if (Name == "plotn")
			{
				m_n = (Value == "true") ? TRUE : FALSE;
				continue;
			}
/*
EToLXition=
LToBXition=
BToAXition=
AToFXition=
ALifeSpan=
FLifeSpan=
The Value string for the next several items is in the format StartDate, EndDate, number where commmas are separators in the string
*/
			if (Name == "etolxition")
			{
				if (Value == "clear")
				{
					theColony.m_InitCond.m_EggTransitionDRV.ClearAll();
				}
				else
				{
					int curpos = 0;
					double NumVal = 0.0;
					CString StartDateStg = Value.Tokenize(",", curpos);
					if (StartDateStg.GetLength() > 0) // Was Start Date found?
					{
						CString EndDateStg = Value.Tokenize(",", curpos);
						if (EndDateStg.GetLength() > 0) // Was End Date Found?
						{
							CString NumValStg = Value.Tokenize(",", curpos);
							if (NumValStg.GetLength() > 0) // Was the % of survivors found?
							{
								NumVal = atof(NumValStg); //  Note that if NumValStg cannot be converted, NumVal will be set to 0.0
								theColony.m_InitCond.m_EggTransitionDRV.AddItem(StartDateStg, EndDateStg, NumVal);
							}
						}
					}
				}
				continue;
			}
			if (Name == "ltobxition")
			{
				if (Value == "clear")
				{
					theColony.m_InitCond.m_LarvaeTransitionDRV.ClearAll();
				}
				else
				{
					int curpos = 0;
					double NumVal = 0.0;
					CString StartDateStg = Value.Tokenize(",", curpos);
					if (StartDateStg.GetLength() > 0) // Was Start Date found?
					{
						CString EndDateStg = Value.Tokenize(",", curpos);
						if (EndDateStg.GetLength() > 0) // Was End Date Found?
						{
							CString NumValStg = Value.Tokenize(",", curpos);
							if (NumValStg.GetLength() > 0) // Was the % of survivors found?
							{
								NumVal = atof(NumValStg); //  Note that if NumValStg cannot be converted, NumVal will be set to 0.0
								theColony.m_InitCond.m_LarvaeTransitionDRV.AddItem(StartDateStg, EndDateStg, NumVal);
							}
						}
					}
				}
				continue;
			}
			if (Name == "btoaxition")
			{
				if (Value == "clear")
				{
					theColony.m_InitCond.m_BroodTransitionDRV.ClearAll();
				}
				else
				{
					int curpos = 0;
					double NumVal = 0.0;
					CString StartDateStg = Value.Tokenize(",", curpos);
					if (StartDateStg.GetLength() > 0) // Was Start Date found?
					{
						CString EndDateStg = Value.Tokenize(",", curpos);
						if (EndDateStg.GetLength() > 0) // Was End Date Found?
						{
							CString NumValStg = Value.Tokenize(",", curpos);
							if (NumValStg.GetLength() > 0) // Was the % of survivors found?
							{
								NumVal = atof(NumValStg); //  Note that if NumValStg cannot be converted, NumVal will be set to 0.0
								theColony.m_InitCond.m_BroodTransitionDRV.AddItem(StartDateStg, EndDateStg, NumVal);
							}
						}
					}
				}
				continue;
			}
			if (Name == "atofxition")
			{
				if (Value == "clear")
				{
					theColony.m_InitCond.m_AdultTransitionDRV.ClearAll();
				}
				else
				{
					int curpos = 0;
					double NumVal = 0.0;
					CString StartDateStg = Value.Tokenize(",", curpos);
					if (StartDateStg.GetLength() > 0) // Was Start Date found?
					{
						CString EndDateStg = Value.Tokenize(",", curpos);
						if (EndDateStg.GetLength() > 0) // Was End Date Found?
						{
							CString NumValStg = Value.Tokenize(",", curpos);
							if (NumValStg.GetLength() > 0) // Was the % of survivors found?
							{
								NumVal = atof(NumValStg); //  Note that if NumValStg cannot be converted, NumVal will be set to 0.0
								theColony.m_InitCond.m_AdultTransitionDRV.AddItem(StartDateStg, EndDateStg, NumVal);
							}
						}
					}
				}
				continue;
			}
			if (Name == "alifespan")
			{
				if (Value == "clear")
				{
					theColony.m_InitCond.m_AdultLifespanDRV.ClearAll();
				}
				else
				{
					int curpos = 0;
					double NumVal = 0.0;
					CString StartDateStg = Value.Tokenize(",", curpos);
					if (StartDateStg.GetLength() > 0) // Was Start Date found?
					{
						CString EndDateStg = Value.Tokenize(",", curpos);
						if (EndDateStg.GetLength() > 0) // Was End Date Found?
						{
							CString NumValStg = Value.Tokenize(",", curpos);
							if (NumValStg.GetLength() > 0) // Was the % of survivors found?
							{
								NumVal = atof(NumValStg); //  Note that if NumValStg cannot be converted, NumVal will be set to 0.0
								if ((NumVal >= 7) && (NumVal <= 21))  // Adult bee age constraint
								{
									theColony.m_InitCond.m_AdultLifespanDRV.AddItem(StartDateStg, EndDateStg, NumVal);
								}
							}
						}
					}
				}
				continue;
			}
			if (Name == "flifespan")
			{
				if (Value == "clear")
				{
					theColony.m_InitCond.m_ForagerLifespanDRV.ClearAll();
				}
				else
				{
					int curpos = 0;
					double NumVal = 0.0;
					CString StartDateStg = Value.Tokenize(",", curpos);
					if (StartDateStg.GetLength() > 0) // Was Start Date found?
					{
						CString EndDateStg = Value.Tokenize(",", curpos);
						if (EndDateStg.GetLength() > 0) // Was End Date Found?
						{
							CString NumValStg = Value.Tokenize(",", curpos);
							if (NumValStg.GetLength() > 0) // Was the % of survivors found?
							{
								NumVal = atof(NumValStg); //  Note that if NumValStg cannot be converted, NumVal will be set to 0.0
								if ((NumVal >= 0) && (NumVal <= 20))  // Constraint on forager lifespan
								{
									theColony.m_InitCond.m_ForagerLifespanDRV.AddItem(StartDateStg, EndDateStg, NumVal);
								}
							}
						}
					}
				}
				continue;
			}

			if (Name == "etolxitionen")
			{
				theColony.m_InitCond.m_EggTransitionDRV.SetEnabled(Value == "true");
				continue;
			}

			if (Name == "ltobxitionen")
			{
				theColony.m_InitCond.m_LarvaeTransitionDRV.SetEnabled(Value == "true");
				continue;
			}

			if (Name == "btoaxitionen")
			{
				theColony.m_InitCond.m_BroodTransitionDRV.SetEnabled(Value == "true");
				continue;
			}

			if (Name == "atofxitionen") 
			{
				theColony.m_InitCond.m_AdultTransitionDRV.SetEnabled(Value == "true");
				continue;
			}

			if (Name == "alifespanen")
			{
				theColony.m_InitCond.m_AdultLifespanDRV.SetEnabled(Value == "true");
				continue;
			}

			if (Name == "flifespanen")
			{
				theColony.m_InitCond.m_ForagerLifespanDRV.SetEnabled(Value == "true");
				continue;
			}

			//Fall through - no match
			{
                std::cerr << "Input File Variable Name " << Name << " not Recognized" << std::endl;
				continue;
			}
		}
	}

	catch (CFileException *e)
	{
		TCHAR stg[255];
		e->GetErrorMessage(stg,255);
        std::cerr << "Error Pocessing Input File: " << stg << std::endl;
	}

}

void VarroaPopCmd::InitializeSimulation()
{
	// Initialize Results Matrix
	/*  The columns of this CMatrix are defined as follows:

				Col 0 = Day Number
				Col 1 = Data point for first series to be plotted
				Col 2 = Data point for second series to be plotted
				Col n = Data point for Nth series to be plotted

		The rows correspond to the values for each day.  The dimensions of the 
		CMatrix array are set to (Number of series + 1, Number of days being plotted)
	*/

	m_SimResults.SetDimensions(GetNumSeries()+1,GetSimDays());

	m_ResultsText.RemoveAll();
	m_ResultsHeader.RemoveAll();
	m_ResultsFileHeader.RemoveAll();
	m_IncImmigratingMites = 0;
	UpdateResults(1);  // Get Results of initial conditions

	theColony.InitializeColony();
	theColony.SetMiticideTreatment(m_MiteTreatments,m_VTEnable);
	theColony.SetMitePctResistance(m_InitMitePctResistant);

	// Initializing the Spore functions
//	theColony.SetSporeTreatment(GetSimDayNumber(m_SPTreatmentStart),m_SPEnable);
//	theColony.m_Spores.SetMortalityFunction(0.10,,0);
	m_CumImmigratingMites = int(0);
	m_FirstResultEntry = true;
}

void VarroaPopCmd::Simulate()
{
    // if (ReadyToSimulate())
    {
		InitializeSimulation();
        
		//  Set results frequency 
		int ResFreq = m_DispWeeklyData?7:1;

		// Set results data format string
		if (m_FieldDelimiter == 1)		// Comma Delimited
		{
			m_ResultsFileFormatStg = "%s,%6d,%6d,%6d,%6d,%6d,%6d,%6d,%6d,%6d,%6d,%6d,%.2f,%.2f,%.2f,%04.2f,%.2f,%.2f,%05.2f,%6d,%6d,%6d,%6.2f,%6.2f,%6d,%6.2f,%6.1f,%6.3f,%6.1f,%6.3f,%6d,%6d,%6d,%6d,%6d,%6.3f,%6.3f,%6.3f";
		}
		else if (m_FieldDelimiter == 2) // Tab Delimited
		{
			m_ResultsFileFormatStg = "%s\t%6d\t%6d\t%6d\t%6d\t%6d\t%6d\t%6d\t%6d\t%6d\t%6d\t%6d\t%.2f\t%.2f\t%.2f\t%04.2f\t%.2f\t%.2f\t%05.2f\t%6d\t%6d\t%6d\t%6.2f\t%6.2f\t%6d\t%6.2f\t%6.1f\t%6.3f\t%6.1f\t%6.3f\t%6d\t%6d\t%6d\t%6d\t%6d\t%6.3f\t%6.3f\t%6.3f";
		}
		else	// Otherwise space delimited
		{
			// original m_ResultsFileFormatStg = "%s %6d %6d %6d %6d %6d %6d %6d %6d %6d %6d %6d %.2f %.2f %.2f %04.2f %.2f %.2f %05.2f %6d %6d %6d %6.2f %6.2f %6d %6.2f %6.1f %6.3f %6.1f %6.3f %6d %6d %6d %6d %6d     %6.3f   %6.3f %6.3f";
			m_ResultsFileFormatStg = "%s %6d %6d %6d %6d %6d %6d %6d %6d %6d %6d %6d %.2f %.2f %.2f %04.2f %.2f %.2f %05.2f %6d %6d %6d %6.2f %6.2f %6d %6.2f %6.1f %6.3f %6.1f %6.3f %6d %6d %6d %6d %6d     %6.3f   %6.3f %6.3f";
		}
        
		CEvent* pEvent = m_pWeather->GetDayEvent(GetSimStart());
		int DayCount = 1;
		int TotSimDays = GetSimDays();
		int TotImMites = 0;
		int TotForagingDays = 0;

		CString CurSize;
		CurSize.Format("                                        Capped  Capped                                                                                                                     Prop           Conc          Conc                                             ");
		m_ResultsFileHeader.AddTail(CurSize);
		CurSize.Format("            Colony  Adult  Adult         Drone   Wkr    Drone  Wkr    Drone  Wkr  Total                                          Free   DBrood WBrood DMite  WMite  Mites  Mites  Colony Pollen Colony Nectar   Dead   Dead   Dead   Dead   Dead    Queen      Ave");
		m_ResultsFileHeader.AddTail(CurSize);
		CurSize.Format("     Date   Size   Drones   Wkr   Forgrs Brood  Brood   Larv   Larv    Eggs  Eggs  Eggs  DD    L    N     P      dd    l    n    Mites  Mites  Mites  /Cell  /Cell  Dying  Dying  Pollen  Pest  Nectar  Pest    DLarv  WLarv  DAdlt  WAdlt  Forgrs  Strength   Temp   Rain");
		m_ResultsFileHeader.AddTail(CurSize);
		CurSize.Format(m_ResultsFileFormatStg,
				//pEvent->GetDateStg("%m/%d/%Y"), 
				"Initial   ",
				theColony.GetColonySize(),
				theColony.Dadl.GetQuantity(),
				theColony.Wadl.GetQuantity(),
				theColony.foragers.GetActiveQuantity(),
				theColony.CapDrn.GetQuantity(),
				theColony.CapWkr.GetQuantity(),
				theColony.Dlarv.GetQuantity(),
				theColony.Wlarv.GetQuantity(),
				theColony.Deggs.GetQuantity(),
				theColony.Weggs.GetQuantity(),
				theColony.GetEggsToday(),
				theColony.GetDDToday(),
				theColony.GetLToday(),
				theColony.GetNToday(),
				theColony.GetPToday(),
				theColony.GetddToday(),
				theColony.GetlToday(),
				theColony.GetnToday(),
				theColony.RunMite.GetTotal(),
				theColony.CapDrn.GetMiteCount(),
				theColony.CapWkr.GetMiteCount(),
				theColony.CapDrn.GetMitesPerCell(),
				theColony.CapWkr.GetMitesPerCell(),
				0, // Changed from double to int
				0.0,
				0.0,
				0.0,
				0.0,
				0.0,
				0,0,0,0,0, // Added 1 0 at the end
				theColony.queen.GetQueenStrength(),
				0.0,0.0); // removed 1 0.0 from the end
		m_ResultsText.AddTail(CurSize);
    
		// *************************************************
		// Main Loop for Simulation
		//
		//
		while ((pEvent != NULL) && (DayCount <= TotSimDays)) 
		{

			theColony.ReQueenIfNeeded(
					DayCount,	
					pEvent,
					m_RQEggLayingDelay,
					m_RQWkrDrnRatio,
					m_RQEnableReQueen,
					m_RQScheduled,
					m_RQQueenStrength,
					m_RQOnce,
					m_RQReQueenDate);
			
			// Determine if there is feed available and call theColony.SetFeedingDay(t/f);
			// Alternate approach is to pass the feed dates and quantities to the colony and
			// let the colony keep track - probably a better idea since the pollen is consumed

			theColony.UpdateBees(pEvent, DayCount);
			
			if (IsImmigrationEnabled() && IsImmigrationWindow(pEvent)) 
			{
				m_IncImmigratingMites = (GetImmigrationMites(pEvent));
				m_IncImmigratingMites.SetPctResistant(m_ImmMitePctResistant);
				theColony.AddMites(m_IncImmigratingMites);
			}
			else m_IncImmigratingMites = 0; // Reset to 0 after Immigration Window Closed
			

			theColony.UpdateMites(pEvent, DayCount);

			if (m_CombRemoveEnable && 
				(pEvent->GetTime().GetYear() == m_CombRemoveDate.GetYear()) &&
				(pEvent->GetTime().GetMonth() == m_CombRemoveDate.GetMonth()) &&
				(pEvent->GetTime().GetDay() == m_CombRemoveDate.GetDay())) 
			{
				theColony.RemoveDroneComb(m_CombRemovePct);
				TRACE("Drone Comb Removed on %s\n",pEvent->GetDateStg());
			}

			theColony.DoPendingEvents(pEvent,DayCount); // Sets colony based on discrete events


			if ((DayCount % ResFreq) == 0 ) // Print once every ResFreq times thru the loop
			{
				double PropMiteDeath = 
					theColony.GetMitesDyingThisPeriod()+theColony.GetTotalMiteCount() > 0?
					theColony.GetMitesDyingThisPeriod()/
					double(theColony.GetMitesDyingThisPeriod()+theColony.GetTotalMiteCount()) : 0;

				double ColPollen = theColony.m_Resources.GetPollenQuantity(); // In Grams
				double ColNectar = theColony.m_Resources.GetNectarQuantity();
				double NectarPesticideConc = theColony.m_Resources.GetNectarPesticideConcentration() * 1000000;
				double PollenPesticideConc = theColony.m_Resources.GetPollenPesticideConcentration() * 1000000;  // convert from g/g to ug/g

				CurSize.Format(m_ResultsFileFormatStg,
					pEvent->GetDateStg("%m/%d/%Y"), 
					theColony.GetColonySize(),
					theColony.Dadl.GetQuantity(),
					theColony.Wadl.GetQuantity(),
					//theColony.foragers.GetQuantity(),
					theColony.foragers.GetActiveQuantity(),
					theColony.CapDrn.GetQuantity(),
					theColony.CapWkr.GetQuantity(),
					theColony.Dlarv.GetQuantity(),
					theColony.Wlarv.GetQuantity(),
					theColony.Deggs.GetQuantity(),
					theColony.Weggs.GetQuantity(),
					theColony.GetEggsToday(),
					theColony.GetDDToday(),
					theColony.GetLToday(),
					theColony.GetNToday(),
					theColony.GetPToday(),
					theColony.GetddToday(),
					theColony.GetlToday(),
					theColony.GetnToday(),
					theColony.RunMite.GetTotal(),
					theColony.CapDrn.GetMiteCount(),
					theColony.CapWkr.GetMiteCount(),
					theColony.CapDrn.GetMitesPerCell(),
					theColony.CapWkr.GetMitesPerCell(),
					theColony.GetMitesDyingThisPeriod(),
					PropMiteDeath,
					ColPollen,
					PollenPesticideConc,
					ColNectar,
					NectarPesticideConc,
					theColony.m_DeadDroneLarvaePesticide,
					theColony.m_DeadWorkerLarvaePesticide,
					theColony.m_DeadDroneAdultsPesticide,
					theColony.m_DeadWorkerAdultsPesticide,
					theColony.m_DeadForagersPesticide,
					theColony.queen.GetQueenStrength(),
					pEvent->GetTemp(),
					pEvent->GetRainfall());
				m_ResultsText.AddTail(CurSize);
			}
			

			UpdateResults(DayCount,pEvent); 

			if ((DayCount % ResFreq) == 0 ) 
				theColony.SetStartSamplePeriod(); // Get ready for new accumulation period

			DayCount++;

			pEvent->IsForageDay()?TotForagingDays++:TotForagingDays;

			pEvent = m_pWeather->GetNextEvent();
		}
		//delete pEvent;
		m_ResultsReady = true;
		m_SimulationComplete = true;

		// If command line switch has /or then save results file
		StoreResultsFile(m_ResultsFileName);

		theColony.Clear();
		m_SimulationComplete = false;
	}
}

void VarroaPopCmd::SetSimStart(COleDateTime start)
{
	m_SimStartTime = start;
	theColony.m_InitCond.m_SimStart = m_SimStartTime.Format("%m/%d/%Y");  
}

void VarroaPopCmd::SetSimEnd(COleDateTime end)
{
	m_SimEndTime = end;
	theColony.m_InitCond.m_SimEnd = m_SimEndTime.Format("%m/%d/%Y");
}

bool VarroaPopCmd::ReadyToSimulate()
{
    return (theColony.IsInitialized() && m_pWeather->IsInitialized());
}

int VarroaPopCmd::GetSimDays()
{
	COleDateTimeSpan ts = GetSimEnd() - GetSimStart();
	return (int)ts.GetDays()+1;
}

int VarroaPopCmd::GetSimDayNumber(COleDateTime theDate)
{
	COleDateTime ss = GetSimStart();
	COleDateTimeSpan ts = theDate - GetSimStart();
	int num = (int)ts.GetDays()+1;
	return num;
}

COleDateTime VarroaPopCmd::GetSimDate(int DayNumber)
{
	COleDateTimeSpan ts((long)DayNumber,0,0,0);
	return (GetSimStart()+ts);
}

int VarroaPopCmd::GetNumSeries()
// Calculates the number of items we are planning to graph
{
	int count = 0;
	if (m_TM) count++;
	if (m_AD) count++;
	if (m_AW) count++;
	if (m_CS) count++;
	if (m_DB) count++;
	if (m_DE) count++;
	if (m_DL) count++;
	if (m_F) count++;
	if (m_MDB) count++;
	if (m_MWB) count++;
	if (m_PDB) count++;
	if (m_PWB) count++;
	if (m_PRM) count++;
	if (m_RM) count++;
	if (m_WB) count++;
	if (m_WE) count++;
	if (m_WL) count++;
	if (m_IM) count++;
	if (m_MD) count++;
	if (m_PMD) count++;
	if (m_NS) count++;
	if (m_PS) count++;
	if (m_NPC) count++;
	if (m_PPC) count++;
	if (m_DDL) count++;
	if (m_DWL) count++;
	if (m_DDA) count++;
	if (m_DWA) count++;
	if (m_DFG) count++;
	if (m_TE) count++;
	if (m_DD) count++;
	if (m_L) count++;
	if (m_N) count++;
	if (m_P) count++;
	if (m_dd) count++;
	if (m_l) count++;
	if (m_n) count++;
	return count;
}

bool VarroaPopCmd::IsImmigrationWindow(CEvent* pEvent)
{
	COleDateTime today = (pEvent->GetTime());

	return((today>=m_ImmigrationStartDate) && (today<=m_ImmigrationEndDate));

}

CMite VarroaPopCmd::GetImmigrationMites(CEvent* pEvent)
{
	//  This routine calculates the number of mites to immigrate on the 
	//  specified date.  It also keeps track of the cumulative number of 
	//  mites that have migrated so far.  First calculate the total quantity
	//  of immigrating mites then return a CMite based on percent resistance to miticide
	/*
		The equations of immigration were derived by identifying the desired function, 
		e.g. f(x) = A*Cos(x), then calculating the constants by setting the integral of
		the function (over the range 0..1) to 1.  This means that the area under the
		curve is = 1.  This ensures that 100% of m_TotImmigratingMites were added to the
		colony.  With the constants were established, a very simple numerical integration 
		is performed using sum(f(x)*DeltaX) for each day of immigration.

		The immigration functions are:

			Cosine -> f(x) = 1.188395*cos(x)

			Sine -> f(x) = 1.57078*sin(PI*x)

			Tangent -> f(x) = 2.648784*tan(1.5*x)

			Exponential -> f(x) = (1.0/(e-2))*(exp(1 - (x)) - 1.0)

			Logarithmic -> f(x) = -1.0*log(x)  day #2 and on

			Polynomial -> f(x) = 3.0*(x) - 1.5*(x*x)

		In the case of Logarithmic, since there is an infinity at x=0, the 
		actual value of the integral over the range (0..DeltaX) is used on the first
		day.

		Mites only immigrate on foraging days.



	*/

	double answer;
	COleDateTime theDate = pEvent->GetTime();
	if ((theDate >= GetImmigrationStart()) && (theDate <= GetImmigrationEnd() && pEvent->IsForageDay()))
	{
		int SimDaytoday = GetSimDayNumber(theDate);
		int SimDayImStart = GetSimDayNumber(GetImmigrationStart());
		int SimDayImStop = GetSimDayNumber(GetImmigrationEnd());

		// Set cumulative immigration to 0 on first day
		if (SimDaytoday == SimDayImStart) m_CumImmigratingMites = 0;

		// If today is the last immigration day, immigrate all remaining mites
		// NOTE: Changed this logic in version 3.2.8.10 when we decided to not immigrade on non-foraging days.
		// In that case, it doesn't make sense to immigrate all remaining mites on the last day
		if (false) {} //(SimDaytoday == SimDayImStop) answer = m_TotImmigratingMites - m_CumImmigratingMites;
		else
		{

			// Calculate the proportion of days into immigration
			double ImProp = (double)(SimDaytoday - SimDayImStart )/
				(double)(1 + SimDayImStop - SimDayImStart);

			double DeltaX = 1.0/(SimDayImStop - SimDayImStart+1);
			double X = ImProp+DeltaX/2;


			// Return function based on immigration type
			if (m_ImmigrationType.MakeUpper() == "NONE") answer = 0;

			else if (m_ImmigrationType.MakeUpper() == "COSINE")  // f(x) = A*Cos(x)
			{
				answer = GetNumImmigrationMites()*1.188395*cos(X)*DeltaX;
			}

			else if (m_ImmigrationType.MakeUpper() == "EXPONENTIAL") // f(x) = A*(exp(1-x) + B) dx
			{
				answer = GetNumImmigrationMites()*(1.0/(exp(1.0) -2))*(exp(1.0 - (X)) -1.0)*DeltaX;
			}

			else if (m_ImmigrationType.MakeUpper() == "LOGARITHMIC") // f(x) = A*log(x) dx
			{
				if (ImProp == 0) // Deal with discontinuity at 0
				{
					answer = GetNumImmigrationMites()*(-1.0*DeltaX*log(DeltaX) - DeltaX);
				}
				else answer = GetNumImmigrationMites()*(-1.0*log(X)*DeltaX);
			}

			else if (m_ImmigrationType.MakeUpper() == "POLYNOMIAL") // f(x) = (A*x + B*x*x) dx
			{
				answer = GetNumImmigrationMites()*(3.0*(X) - 1.5*(X*X))*DeltaX;
			}

			else if (m_ImmigrationType.MakeUpper() == "SINE") // f(x) = A*Sin(PiX) dx
			{
				answer = GetNumImmigrationMites()*1.57078*sin(3.1416*X)*DeltaX;
			}
			else if (m_ImmigrationType.MakeUpper() == "TANGENT") // f(x) = A*Tan(B*X) dx
			{
				answer = GetNumImmigrationMites()*2.648784*tan(1.5*X)*DeltaX;
			}

			else answer = 0;  // m_ImmigrationType not valid


			// Now calculate the correction factor based on number of days of immigration.
			// The equations assume 25 days so correction factor is 25/(#days in sim)
			/*
			if (!(m_ImmigrationType == "Cosine"))
			{
			double CorrFact = (double)25/
				(double)(GetSimDayNumber(GetImmigrationEnd()) - 
				GetSimDayNumber(GetImmigrationStart()) + 1);
			answer = answer*CorrFact;
			}
			*/

			// Constrain to positive number
			if (answer <0.0) answer = 0.0;
		}

		// Increment the running total of mites that have immigrated
		int ResistantMites = int((answer*m_ImmMitePctResistant)/100 + 0.5);
		m_CumImmigratingMites += CMite(ResistantMites, int(answer-ResistantMites + 0.5));
	}
	else answer = 0;
	CMite theImms;
	theImms.SetResistant(int((answer*m_ImmMitePctResistant)/100 + 0.5));
	theImms.SetNonResistant(int(answer-theImms.GetResistant() + 0.5));
	return theImms;
}

void VarroaPopCmd::UpdateResults(int DayCount, CEvent* pEvent)
{
	if (m_FirstResultEntry) 
	{
		m_SimLabels.RemoveAll();
	}
	int seriesID = 0;
	m_SimResults[seriesID++][DayCount-1] = DayCount;
	if (m_AD)	//	Adult Drones
	{
		m_SimResults[seriesID++][DayCount-1] = theColony.Dadl.GetQuantity();
		if (m_FirstResultEntry) m_SimLabels.AddTail("Adult Drones");
	}
	if (m_AW)	// Adult Workers
	{
		m_SimResults[seriesID++][DayCount-1] = theColony.Wadl.GetQuantity();
		if (m_FirstResultEntry) m_SimLabels.AddTail("Adult Workers");
	}
	if (m_CS)	// Colony Size
	{
		m_SimResults[seriesID++][DayCount-1] = theColony.GetColonySize();
		if (m_FirstResultEntry) m_SimLabels.AddTail("Colony Size");
	}
	if (m_DB)	// Drone Brood
	{
		m_SimResults[seriesID++][DayCount-1] = theColony.CapDrn.GetQuantity();
		if (m_FirstResultEntry) m_SimLabels.AddTail("Drone Brood");
	}
	if (m_DE)	// Drone Eggs
	{
		m_SimResults[seriesID++][DayCount-1] = theColony.Deggs.GetQuantity();
		if (m_FirstResultEntry) m_SimLabels.AddTail("Drone Eggs");
	}
	if (m_DL)	// Drone Larvae
	{
		m_SimResults[seriesID++][DayCount-1] = theColony.Dlarv.GetQuantity();
		if (m_FirstResultEntry) m_SimLabels.AddTail("Drone Larvae");
	}
	if (m_F)	// Foragers
	{
		//m_SimResults[seriesID++][DayCount-1] = theColony.foragers.GetQuantity();
		m_SimResults[seriesID++][DayCount-1] = theColony.foragers.GetActiveQuantity();
		if (m_FirstResultEntry) m_SimLabels.AddTail("Active Foragers");
	}
	if (m_TM)   // Total Mites In Colony
	{
		m_SimResults[seriesID++][DayCount-1] = theColony.CapDrn.GetMiteCount()+
			theColony.CapWkr.GetMiteCount() + theColony.RunMite;
		if (m_FirstResultEntry) m_SimLabels.AddTail("Total Mite Count");
	}
	if (m_MDB)	// Mites in Drone Brood
	{
		m_SimResults[seriesID++][DayCount-1] = theColony.CapDrn.GetMiteCount();
		if (m_FirstResultEntry) m_SimLabels.AddTail("Mites in Drn Brood");
	}
	if (m_MWB)	// Mites in Worker Brood
	{
		m_SimResults[seriesID++][DayCount-1] = theColony.CapWkr.GetMiteCount();
		if (m_FirstResultEntry) m_SimLabels.AddTail("Mites in Wkr Brood");
	}
	if (m_RM)	// Free Running Mites
	{
		m_SimResults[seriesID++][DayCount-1] = theColony.RunMite.GetTotal();
		if (m_FirstResultEntry) m_SimLabels.AddTail("Free Running Mites");
	}
	if (m_WB)	// Worker Brood
	{
		m_SimResults[seriesID++][DayCount-1] = theColony.CapWkr.GetQuantity();
		if (m_FirstResultEntry) m_SimLabels.AddTail("Worker Brood");
	}
	if (m_WE)	// Worker Eggs
	{
		m_SimResults[seriesID++][DayCount-1] = theColony.Weggs.GetQuantity();
		if (m_FirstResultEntry) m_SimLabels.AddTail("Worker Eggs");
	}
	if (m_WL)	// Worker Larvae
	{
		m_SimResults[seriesID++][DayCount-1] = theColony.Wlarv.GetQuantity();
		if (m_FirstResultEntry) m_SimLabels.AddTail("Worker Larvae");
	}
	if (m_PWB)	// Mites per Worker Brood Cell
	{
		m_SimResults[seriesID++][DayCount-1] = theColony.CapWkr.GetMitesPerCell();
		if (m_FirstResultEntry) m_SimLabels.AddTail("Mites/Wkr Cell");
	}
	if (m_PDB)	// Mites per Drone Brood Cell
	{
		m_SimResults[seriesID++][DayCount-1] = theColony.CapDrn.GetMitesPerCell();
		if (m_FirstResultEntry) m_SimLabels.AddTail("Mites/Drn Cell");
	}
	if (m_PRM)	// Proportion of Resistant Free Mites
	{
		m_SimResults[seriesID++][DayCount-1] = theColony.RunMite.GetPctResistant()/100.0;
		if (m_FirstResultEntry) m_SimLabels.AddTail("Prop Res Free Mites");
	}
	if (m_IM)	// Immigrating Mites
	{
		m_SimResults[seriesID++][DayCount-1] = m_IncImmigratingMites.GetTotal();
		if (m_FirstResultEntry) m_SimLabels.AddTail("Immigrating Mites");
	}
	if (m_MD)
	{
		m_SimResults[seriesID++][DayCount-1] = theColony.GetMitesDyingToday();
		if (m_FirstResultEntry) m_SimLabels.AddTail("Num Mites Dying/Day");
	}
	if (m_PMD)
	{
		m_SimResults[seriesID++][DayCount-1] = 
			(theColony.GetTotalMiteCount() > 0) ? 
			theColony.GetMitesDyingToday()/double(theColony.GetMitesDyingToday()+theColony.GetTotalMiteCount()) : 0;
		if (m_FirstResultEntry) m_SimLabels.AddTail("Prop Mites Dying");
	}
	if (m_NS)
	{
		m_SimResults[seriesID++][DayCount-1] = theColony.m_Resources.GetNectarQuantity();
		if (m_FirstResultEntry) m_SimLabels.AddTail("Nectar Stores(g) ");

	}
	if (m_PS)
	{
		m_SimResults[seriesID++][DayCount-1] = theColony.m_Resources.GetPollenQuantity();
		if (m_FirstResultEntry) m_SimLabels.AddTail("Pollen Stores(g) ");

	}
	if (m_NPC)
	{
		m_SimResults[seriesID++][DayCount-1] = theColony.m_Resources.GetNectarPesticideConcentration() * 1000000;
		if (m_FirstResultEntry) m_SimLabels.AddTail("N-PestConc ug/g ");
	}
	if (m_PPC)
	{
		m_SimResults[seriesID++][DayCount-1] = theColony.m_Resources.GetPollenPesticideConcentration() * 1000000;
		if (m_FirstResultEntry) m_SimLabels.AddTail("P-PestConc ug/g ");
	}
	if (m_DDL)
	{
		m_SimResults[seriesID++][DayCount-1] = theColony.m_DeadDroneLarvaePesticide;
		if (m_FirstResultEntry) m_SimLabels.AddTail("Dead DLarv ");
	}
	if (m_DWL)
	{
		m_SimResults[seriesID++][DayCount-1] = theColony.m_DeadWorkerLarvaePesticide;
		if (m_FirstResultEntry) m_SimLabels.AddTail("Dead WLarv ");

	}
	if (m_DDA)
	{
		m_SimResults[seriesID++][DayCount-1] = theColony.m_DeadDroneAdultsPesticide;
		if (m_FirstResultEntry) m_SimLabels.AddTail("Dead DAdults ");

	}
	if (m_DWA)
	{
		m_SimResults[seriesID++][DayCount-1] = theColony.m_DeadWorkerAdultsPesticide;
		if (m_FirstResultEntry) m_SimLabels.AddTail("Dead WAdults ");

	}
	if (m_DFG)
	{
		m_SimResults[seriesID++][DayCount-1] = theColony.m_DeadForagersPesticide;
		if (m_FirstResultEntry) m_SimLabels.AddTail("Dead Foragers ");

	}
	if (m_TE)	// Worker Eggs
	{
		m_SimResults[seriesID++][DayCount - 1] = theColony.GetEggsToday();
		if (m_FirstResultEntry) m_SimLabels.AddTail("Total Eggs");
	}
	if (m_DD)	// Worker Eggs
	{
		m_SimResults[seriesID++][DayCount - 1] = theColony.GetDDToday();
		if (m_FirstResultEntry) m_SimLabels.AddTail("DD");
	}
	if (m_L)	// Worker Eggs
	{
		m_SimResults[seriesID++][DayCount - 1] = theColony.GetLToday();
		if (m_FirstResultEntry) m_SimLabels.AddTail("L");
	}
	if (m_N)	// Worker Eggs
	{
		m_SimResults[seriesID++][DayCount - 1] = theColony.GetNToday();
		if (m_FirstResultEntry) m_SimLabels.AddTail("N");
	}
	if (m_P)	// Worker Eggs
	{
		m_SimResults[seriesID++][DayCount - 1] = theColony.GetPToday();
		if (m_FirstResultEntry) m_SimLabels.AddTail("P");
	}
	if (m_dd)	// Worker Eggs
	{
		m_SimResults[seriesID++][DayCount - 1] = theColony.GetddToday();
		if (m_FirstResultEntry) m_SimLabels.AddTail("dd");
	}
	if (m_l)	// Worker Eggs
	{
		m_SimResults[seriesID++][DayCount - 1] = theColony.GetlToday();
		if (m_FirstResultEntry) m_SimLabels.AddTail("l");
	}
	if (m_n)	// Worker Eggs
	{
		m_SimResults[seriesID++][DayCount - 1] = theColony.GetnToday();
		if (m_FirstResultEntry) m_SimLabels.AddTail("n");
	}

	m_FirstResultEntry = false;
//	if (pEvent != NULL) m_AxisLabels.AddTail(pEvent->GetDateStg("%b/%d/%y"));
}

void VarroaPopCmd::StoreResultsFile(CString PathName)
{
	try
	{
		CStdioFile theFile(PathName,CFile::modeCreate|CFile::modeWrite|CFile::typeText);

		// Write VarroaPop Version
		if (m_Version)
		{
			CString titlestg;
			titlestg.Format("Varroa Population Simulation - %s\n",COleDateTime::GetCurrentTime().Format("%b %d,%Y  %I:%M:%S %p"));
			theFile.WriteString(titlestg);
			CString verstg ("Linux CMD");
			theFile.WriteString(verstg + "\n\n");
		}
		// Write Header Info to file
		if (m_WeatherColony)
		{
			theFile.WriteString("Weather File: "+GetWeatherFileName() + "\n");
			theFile.WriteString("Colony File:  "+GetColonyFileName() + "\n\n");
		}

		// Write Initial Conditions to file
		if (m_InitConds)
		{
			CString OutStg;
			OutStg.Format("Drone Adult Infestation=%4.2f\n",theColony.m_InitCond.m_droneAdultInfestField);
			theFile.WriteString(OutStg);
			OutStg.Format("Drone Brood Infestation=%4.2f\n",theColony.m_InitCond.m_droneBroodInfestField);
			theFile.WriteString(OutStg);
			OutStg.Format("Drone Mite Survivorship=%4.2f\n",theColony.m_InitCond.m_droneMiteSurvivorshipField);
			theFile.WriteString(OutStg);
			OutStg.Format("Drone Mite Offspring=%4.2f\n",theColony.m_InitCond.m_droneMiteOffspringField);
			theFile.WriteString(OutStg);
			OutStg.Format("Worker Adult Infestation=%4.2f\n",theColony.m_InitCond.m_workerAdultInfestField);
			theFile.WriteString(OutStg);
			OutStg.Format("Worker Brood Infestation=%4.2f\n",theColony.m_InitCond.m_workerBroodInfestField);
			theFile.WriteString(OutStg);
			OutStg.Format("Worker Mite Survivorship=%4.2f\n",theColony.m_InitCond.m_workerMiteSurvivorship);
			theFile.WriteString(OutStg);
			OutStg.Format("Worker Mite Offspring=%4.2f\n",theColony.m_InitCond.m_workerMiteOffspring);
			theFile.WriteString(OutStg);
			OutStg.Format("Drone Adults=%d\n",theColony.m_InitCond.m_droneAdultsField);
			theFile.WriteString(OutStg);
			OutStg.Format("Drone Brood=%d\n",theColony.m_InitCond.m_droneBroodField);
			theFile.WriteString(OutStg);
			OutStg.Format("Drone Larvae=%d\n",theColony.m_InitCond.m_droneLarvaeField);
			theFile.WriteString(OutStg);
			OutStg.Format("Drone Eggs=%d\n",theColony.m_InitCond.m_droneEggsField);
			theFile.WriteString(OutStg);
			OutStg.Format("Worker Adults=%d\n",theColony.m_InitCond.m_workerAdultsField);
			theFile.WriteString(OutStg);
			OutStg.Format("Worker Brood=%d\n",theColony.m_InitCond.m_workerBroodField);
			theFile.WriteString(OutStg);
			OutStg.Format("Worker Larvae=%d\n",theColony.m_InitCond.m_workerLarvaeField);
			theFile.WriteString(OutStg);
			OutStg.Format("Worker Eggs=%d\n",theColony.m_InitCond.m_workerEggsField);
			theFile.WriteString(OutStg);
			OutStg.Format("Queen Sperm=%d\n",(int)(theColony.m_InitCond.m_QueenSperm));
			theFile.WriteString(OutStg);
			OutStg.Format("Maximum Eggs per Day=%d\n",(int)(theColony.m_InitCond.m_MaxEggs));
			theFile.WriteString(OutStg);
			OutStg.Format("Forager Lifespan=%d\n",theColony.m_InitCond.m_ForagerLifespan);
			theFile.WriteString(OutStg);
			OutStg.Format("Total Eggs=%d\n", theColony.m_InitCond.m_totalEggsField);
			theFile.WriteString(OutStg);
			OutStg.Format("Daily DD=%.2f\n", theColony.m_InitCond.m_DDField);
			theFile.WriteString(OutStg);
			OutStg.Format("Daily L=%.2f\n", theColony.m_InitCond.m_LField);
			theFile.WriteString(OutStg);
			OutStg.Format("Daily N=%.2f\n", theColony.m_InitCond.m_NField);
			theFile.WriteString(OutStg);
			OutStg.Format("Daily P=%.2f\n", theColony.m_InitCond.m_PField);
			theFile.WriteString(OutStg);
			OutStg.Format("Daily dd=%.2f\n", theColony.m_InitCond.m_ddField);
			theFile.WriteString(OutStg);
			OutStg.Format("Daily l=%.2f\n", theColony.m_InitCond.m_lField);
			theFile.WriteString(OutStg);
			OutStg.Format("Daily n=%.2f\n", theColony.m_InitCond.m_nField);
			theFile.WriteString(OutStg);

			if (m_ImmigrationEnabled) theFile.WriteString("Immigration Enabled=TRUE\n");
			else  theFile.WriteString("Immigration Enabled=FALSE\n");

			if (m_RQEnableReQueen) theFile.WriteString("Requeening Enabled=TRUE\n");
			else  theFile.WriteString("Requeening Enabled=FALSE\n");

			if (m_VTEnable) theFile.WriteString("Varroa Treatment Enabled=TRUE\n");
			else  theFile.WriteString("Varroa Treatment Enabled=FALSE\n");

			if (m_CombRemoveEnable) theFile.WriteString("Comb Removal Enabled=TRUE\n");
			else  theFile.WriteString("Comb Removal Enabled=FALSE\n");

			theFile.WriteString("\n");

		}



		// Write Column Headers to file
		POSITION pos = m_ResultsFileHeader.GetHeadPosition();
		if (m_ColTitles)
		{
			while (pos!= NULL)
			{
				theFile.WriteString(m_ResultsFileHeader.GetNext(pos) + "\n");
			}
		}

		// Now write results to the file
		pos = m_ResultsText.GetHeadPosition();
		while (pos != NULL)
		{
			theFile.WriteString(m_ResultsText.GetNext(pos) + "\n");
		}
		theFile.Close();
	}
	catch (CFileException* e)
	{
		TCHAR stg[255];
		e->GetErrorMessage(stg,255);
        std::cerr << stg << std::endl;
	}

}
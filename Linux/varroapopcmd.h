#pragma once
#ifndef VARROAPOPCMD_H
#define VARROAPOPCMD_H

#include "colony.h"
#include "ieditem.h"
#include "matrix.h"
#include "mite.h"
#include "weatherevents.h"

#include "stdafx.h"

class VarroaPopCmd
{
public:

    VarroaPopCmd();
    ~VarroaPopCmd();

	void SetResultsFileName(CString resultsFilename);
	void ProcessInputFile(CString FileName);

	void InitializeSimulation();

    void Simulate();

	bool IsImmigrationEnabled() { return m_ImmigrationEnabled;}
	bool IsImmigrationWindow(CEvent* pEvent);

    CMite GetImmigrationMites(CEvent* pEvent);
	COleDateTime GetImmigrationStart() {return m_ImmigrationStartDate;}
	COleDateTime GetImmigrationEnd() {return m_ImmigrationEndDate;}
	int GetNumImmigrationMites() {return m_TotImmigratingMites.GetTotal();}
	
	void UpdateResults(int Day, CEvent* pEvent = NULL);
	void StoreResultsFile(CString PathName);
	
	CString GetWeatherFileName() {return m_pWeather->GetFileName();}
	CString GetColonyFileName() {return theColony.GetName();}

	void Serialize(CArchive& ar);

	// Added for the CMD app
	void LoadVRPFile(const CString& filename);
	void LoadWeatherFile(const CString& filename);

protected:

	// Simulation Operations
	COleDateTime GetSimStart() {return m_SimStartTime;}
	COleDateTime GetSimEnd() {return m_SimEndTime;}
	void SetSimStart(COleDateTime start); 
	void SetSimEnd(COleDateTime end);
	int GetSimDays();
	int GetSimDayNumber(COleDateTime theDate);
	COleDateTime GetSimDate(int DayNum);
	int GetNumSeries();
    bool ReadyToSimulate();

protected:

	CStringList availableFilesList;
	CStringList selectedFilesList;
	int selectedFileIndex;

	//  Output/Plotting Attributes;
	CMatrix m_SimResults;		// The simulation results to be plotted
	CStringList m_SimLabels;	// Contains the labels of the plotted data series
	CStringList m_ResultsHeader;// Header Strings for ListView Control
	CStringList m_ResultsFileHeader; // Header Strings for File
	CStringList m_ResultsText;  // Results of Simulation 
	CStringList m_ResultsFileText; // Results of Simulation for file storage
	bool m_DispWeeklyData;		// Defines whether numeric results are generated
								//    Weekly or Daily

	// Graph Selection variables
	BOOL	m_AD;	// Adult Drones
	BOOL	m_AW;	// Adult Workers
	BOOL	m_CS;	// Colony Size
	BOOL	m_DB;	// Drone Brood
	BOOL	m_DE;	// Drone Eggs
	BOOL	m_DL;	// Drone Larvae
	BOOL	m_F;	// Foragers
	BOOL    m_TM;	// Total Mites in colony
	BOOL	m_MDB;	// Mites in Drone Brood
	BOOL	m_MWB;	// Mites in Worker Brood
	BOOL	m_PDB;	// Proportion of Drone Brood Infested
	BOOL	m_PWB;	// Proportion of Worker Brood Infested
	BOOL	m_PRM;	// Proportion of Running Mites resistant to miticide
	BOOL	m_RM;	// Free Running Mites
	BOOL	m_WB;	// Worker Brood
	BOOL	m_WE;	// Worker Eggs
	BOOL	m_WL;	// Worker Larvae
	BOOL    m_IM;	// Immigrating Mites
	BOOL	m_MD;	// Mites Dying this day or week
	BOOL	m_PMD;	// Proportion of total mite population dying this day or week
	BOOL	m_NS;	// Colony Nectar Stores
	BOOL	m_PS;	// COlony Pollen Stores
	BOOL	m_NPC;	// Nectar Persticide Concentration
	BOOL	m_PPC;	// Pollen Pesticide Concentration
	BOOL	m_DDL;	// Dead Drone Larvae from Pesticide
	BOOL	m_DWL;	// Dead Worker Larvae from Pesticide
	BOOL	m_DDA;	// Dead Drone Adults from Pesticide
	BOOL	m_DWA;	// Dead Worker Adults from Pesticide
	BOOL	m_DFG;	// Dead Foragers from Pesticide
	BOOL	m_TE;	// Total Eggs
	BOOL	m_DD;	// Daily DD
	BOOL	m_L;	// Daily L
	BOOL	m_N;	// Daily N
	BOOL	m_P;	// Daily P
	BOOL	m_dd;	// Daily dd
	BOOL	m_l;	// Daily l
	BOOL	m_n;	// Daily n
	int		m_AutoScaleChart; //0 if autoscale, 1 if manual scale
	double	m_YAxisMax; // If not autoscaled, the Y-axis maximum
	double  m_YAxisMin; // If not autoscaled, the Y-axis minimum


	

	// Options Selection from COptions Dialog
	BOOL m_ColTitles;
	BOOL m_InitConds;
	BOOL m_Version;
	BOOL m_WeatherColony;
	int m_FieldDelimiter;
	int m_DispFrequency;



protected:
	CColony theColony;
	CWeatherEvents* m_pWeather;
	bool m_FirstResultEntry;
	CString m_DefaultPathName;
	CString m_WeatherFileName;
	bool m_SessionLoaded;
	bool m_WeatherLoaded;
	bool m_ShowWarnings;


	// Simulation Data
	COleDateTime m_SimStartTime;
	COleDateTime m_SimEndTime;
	bool m_SimulationComplete;
	bool m_ResultsReady;

public:
	// Immigration Data
	CString m_ImmigrationType;
	CMite m_TotImmigratingMites;
	CMite m_IncImmigratingMites;
	CMite m_CumImmigratingMites;
	double m_ImmMitePctResistant;
	COleDateTime m_ImmigrationStartDate;
	COleDateTime m_ImmigrationEndDate;
	bool m_ImmigrationEnabled;

	// Re-Queening Data
	UINT	m_RQEggLayingDelay;
	double	m_RQWkrDrnRatio;
	BOOL	m_RQEnableReQueen;
	int		m_RQScheduled;
	double	m_RQQueenStrength;
	int		m_RQOnce;
	COleDateTime	m_RQReQueenDate;

	// Varroa Miticide Treatment Data;
	// NOTE:  Need to change this to a list to support multiple treatments
	CMiteTreatments m_MiteTreatments;
	
	COleDateTime	m_VTTreatmentStart;
	UINT	m_VTTreatmentDuration;
	UINT	m_VTMortality;
	double	m_InitMitePctResistant;
	BOOL	m_VTEnable;

	// Varroa Spore Treatment Data
	BOOL	m_SPEnable;
	COleDateTime	m_SPTreatmentStart;
	int		m_SPInitial;
	double	m_Mort10;
	double	m_Mort25;
	double	m_Mort50;
	double	m_Mort75;
	double	m_Mort90;

	// Comb Removal
	COleDateTime	m_CombRemoveDate;
	BOOL	m_CombRemoveEnable;
	double  m_CombRemovePct;

	// EPA Mortality
	CIEDItem m_IEDItem;  //Note:  This variable should be removed but it will change the session file format
	BOOL m_IEDEnable;
    
	CString m_ResultsFileFormatStg;
    CString m_ResultsFileName;
};

#endif // VARROAPOPCMD_H
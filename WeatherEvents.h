// WeatherEvents.h: interface for the CWeatherEvents class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WEATHEREVENTS_H__40D18204_C275_11D2_8918_9F75F84DB713__INCLUDED_)
#define AFX_WEATHEREVENTS_H__40D18204_C275_11D2_8918_9F75F84DB713__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include <vector>

class CColdStorageSimulator;

class CEvent : public CObject
{
	friend class CWeatherEvents;

private:
	COleDateTime m_Time;
	double       m_Temp;     //  Average Temperature in degC
	double       m_MaxTemp;  //  Maximum Temperature in degC
	double       m_MinTemp;  //  Minumum Temperature in degC
	double       m_Rainfall; //  Rainfall in inches
	bool         m_ForageDay;
	double       m_ForageInc; //  Increment of a Forage Day
	double       m_Solstice;
	double       m_DaylightHours;
	int          m_FlightHours;
	int          m_LineNum;

public:
	CEvent();
	~CEvent();
	CString ToText();      // Returns a human-readable text version of the event
	CEvent(CEvent& event); // Copy Constructor
	const COleDateTime& GetTime() const { return m_Time; }
	CString             GetDateStg(CString format = "%d/%m/%Y");
	double              GetTemp();
	double              GetMaxTemp();
	double              GetMinTemp();
	double              GetRainfall() { return m_Rainfall; }
	bool                IsForageDay();
	//! Returns true if the current day is a forage day and that forage increment is valid
	bool                IsForagingDay() { return IsForageDay() && GetForageInc() > 0.0; }
	bool                IsWinterDay();
	int                 GetLineNum() { return m_LineNum; }
	double              GetSolstice();
	double              GetDaylightHours();
	int                 GetFlightHours();
	void                SetTime(COleDateTime time) { m_Time = time; }
	void                SetTemp(double temp) { m_Temp = temp; }
	void                SetMaxTemp(double maxTemp) { m_MaxTemp = maxTemp; }
	void                SetMinTemp(double minTemp) { m_MinTemp = minTemp; }
	void                SetRainfall(double rainfall) { m_Rainfall = rainfall; }
	void                SetForage(bool Forage) { m_ForageDay = Forage; }
	void                SetForageInc(double forageInc) { m_ForageInc = forageInc; };
	void                SetForageInc(double TThresh, double TMax, double TAve);
	double              GetForageInc();
	void                SetLineNum(int line) { m_LineNum = line; }
	void                SetSolstice(double hrs) { m_Solstice = hrs; }
	void                SetDaylightHours(double hrs) { m_DaylightHours = hrs; }
	void                SetFlightHours(int hrs) { m_FlightHours = hrs; }
	void                Serialize(CArchive& ar);

	//  use this methods with a specific ColdStorageSimulator instance
	double GetTemp(const CColdStorageSimulator& coldStorage);
	double GetMaxTemp(const CColdStorageSimulator& coldStorage);
	double GetMinTemp(const CColdStorageSimulator& coldStorage);
	bool   IsForageDay(const CColdStorageSimulator& coldStorage);
	double GetForageInc(const CColdStorageSimulator& coldStorage);

	//  Overloaded Operators
	CEvent operator=(CEvent& event);
	CEvent operator+(CEvent event);
	void   operator+=(CEvent event);
};

class CWeatherFile : public CStdioFile
{
	friend class CWeatherEvents;

private:
	CString m_HeaderScale;
	CString m_HeaderFileName;
	CString m_HeaderFormat;
	CString m_HeaderBeginTime;
	CString m_HeaderBeginDate;
	CString m_HeaderEndTime;
	CString m_HeaderEndDate;
	CString m_HeaderStartSim;
	CString m_HeaderEndSim;
	int     m_HeaderTempCol;
	int     m_HeaderMaxTempCol;
	int     m_HeaderMinTempCol;
	int     m_HeaderRainCol;
	int     m_HeaderWindspeedCol;
	int     m_HeaderSolarRadCol;
	int     m_HeaderInterval;
	int     m_CurrentLine; // The file line number that was just read in
	enum DateType
	{
		UNDEFINED,
		DOY,
		MMDD,
		MMDDYY,
		MMDDYYYY,
		MONTHNAME
	};
	DateType m_DateType;
	CString  m_ErrorStg;
	DWORD    m_PrevValidLinePos;
	int      m_Size;
	int      m_BytesRead;
	bool     IsMonth(CString monthname);
	int      MonthToNum(CString monthname);

public:
	CWeatherFile();
	~CWeatherFile();
	BOOL    Open(LPCTSTR lpszFileName, UINT nOpenFlags, CFileException* pError = NULL);
	bool    IsHeaderPresent();
	bool    CreateHeader();
	bool    CreateMinMaxHeader();
	bool    CreateHourlyHeader();
	bool    DigestHeader();
	void    SeekToBegin();
	BOOL    GetLine(CString& stg);
	bool    GetValidLine(COleDateTime& theTime, CString& theLine);
	bool    IsHourlyFormat() { return (m_HeaderFormat == "HOURLY"); }
	CString GetError() { return m_ErrorStg; }
	CEvent* LineToEvent();
	CEvent* LinesToEvent();
	CEvent* GetNextEvent();
	bool    IsLineValid(CString theLine);
	void    GoToPrevLine() { Seek(m_PrevValidLinePos, CFile::begin); }
};

class CWeatherEvents : public CObject
{
private:
	CString                          m_Filename;
	POSITION                         pos;
	CTypedPtrList<CPtrList, CEvent*> m_EventList;
	bool                             HasBeenInitialized;

public:
	CWeatherEvents();
	virtual ~CWeatherEvents();
	void         ClearAllEvents();
	bool         AddEvent(CEvent* theEvent);
	bool         RemoveCurrentEvent();
	COleDateTime GetBeginningTime(); // Returns the first date in the actual weather file
	COleDateTime GetEndingTime();    // Returns the last date in the actual weather file
	COleDateTime GetCurrentTime();
	double       CalcDaylightFromLatitude(double Lat, int DayNum);
	int          GetCurrentLineNumber();
	int          GetTotalEvents();
	void         SetFileName(CString fname) { m_Filename = fname; }
	CString      GetFileName();
	int          CheckInterval();
	int          CheckSanity();
	bool         LoadWeatherFile(CString FileName);
	bool         LoadEPAWeatherFileDVF(CString FileName);
	bool         LoadEPAWeatherFileWEA(CString FileName);

	//! Enable to load grid binary files directly check WeatherGridData.h to see supported formats
	template <typename GridDataType> bool LoadWeatherGridDataBinaryFile(CString FileName);

	void ComputeHourlyTemperatureEstimationAndUpdateForageInc(std::vector<CEvent*>& events);

	void Serialize(CArchive& ar);
	bool IsInitialized() { return HasBeenInitialized; }
	//  Access
	void    GoToFirstEvent();
	CEvent* GetNextEvent();
	CEvent* GetDayEvent(COleDateTime theTime);
	CEvent* GetFirstEvent();

	// Operators
protected:
	double GetLatitudeFromFile(CString WeatherFileName);
	double GetLatitudeFromFileName(CString WeatherFileName);
};

//  Free Functions
int CountChars(CString instg, TCHAR testchar);

#endif // !defined(AFX_WEATHEREVENTS_H__40D18204_C275_11D2_8918_9F75F84DB713__INCLUDED_)

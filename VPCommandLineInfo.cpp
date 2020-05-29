// VPCommandLineInfo.cpp: implementation of the CVPCommandLineInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "varroapop.h"
#include "VPCommandLineInfo.h"

#include "GlobalOptions.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVPCommandLineInfo::CVPCommandLineInfo()
{
	m_CurFlag = FLNone;
	CLBackground = false;
	CLSessionFileName = "";
	CLInputFileName = "";
	CLOutputGraphFileName = "";
	CLOutputResultsFileName = "";
	CLOutputLogFileName = "";

}

CVPCommandLineInfo::~CVPCommandLineInfo()
{

}


void CVPCommandLineInfo::ParseParam( LPCTSTR lpszParam, BOOL bFlag, BOOL bLast )
{
//	CCommandLineInfo::ParseParam(  lpszParam, bFlag, bLast );

	CString Param(lpszParam);
	Param.MakeLower();

	if (bFlag) // This is a flag value so set the flag type.  Next parameter is the value
	{
		if (Param == "i") m_CurFlag = FLInputFile;
		else if (Param == "og") m_CurFlag = FLOutputGraph;
		else if (Param == "or") m_CurFlag = FLOutputResults;
		else if (Param == "ol") m_CurFlag = FLOutputLog;
		else if (Param == "b") 
		{
			m_CurFlag = FLNone; // no parameter after /b
			CLBackground = true;
		}
		else if (Param == "foragedaynotemp")
		{
			m_CurFlag = FLNone;
			GlobalOptions::Get().ForageDayElectionBasedOnTemperatures.Set(false);
		}
		else if (Param == "hourlytempestimation")
		{
			m_CurFlag = FLNone;
			GlobalOptions::Get().ShouldComputeHourlyTemperatureEstimation.Set(true);
		}
		else if (Param == "pendingforagersfirst")
		{
			m_CurFlag = FLNone;
			GlobalOptions::Get().ShouldAddForagersToPendingForagersFirst.Set(true);
		}
		else if (Param == "binaryweatherfileformat")
		{
			m_CurFlag = FLBinaryWeatherFileFormat;
		}
		else m_CurFlag = FLInvalid;
	}
	else
	{
		switch ( m_CurFlag )
		{
			case FLNone:
				CLSessionFileName = Param;
				m_CurFlag = FLNone;
				break;
			case FLInputFile:
				CLInputFileName = Param;
				m_CurFlag = FLNone;
				break;
			case FLOutputGraph:
				CLOutputGraphFileName = Param;
				m_CurFlag = FLNone;
				break;
			case FLOutputResults:
				CLOutputResultsFileName = Param;
				m_CurFlag = FLNone;
				break;
			case FLOutputLog:
				CLOutputLogFileName = Param;
				m_CurFlag = FLNone;
				break;
			case FLBackground:
				CLBackground = true;
				m_CurFlag = FLNone;
				break;
			case FLBinaryWeatherFileFormat:
				GlobalOptions::Get().BinaryWeatherFileFormatIdentifier.Set(static_cast<const char*>(lpszParam));
				m_CurFlag = FLNone;
				break;
			default:;

		}
	}

	//TRACE(" Parameter is %s\n",lpszParam);

}

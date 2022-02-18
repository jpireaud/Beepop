#pragma once

#include "stdafx.h"

#include "OutputFormatter.h"

/**
 * This class encapsulates manipulations done on Session structure for default output handling.
 *
 * This
 */
class CVarroaPopOutputFormatter : public COutputFormatter
{
public:
	CVarroaPopOutputFormatter(CVarroaPopSession& session, CStringList& resultsText, CStringList& resultsHeader,
	                          CStringList& resultsFileHeader);

	void Init(CColony& colony);

	void Record(CColony& colony, CEvent& event);

protected:
	CStringList& m_ResultsText;
	CStringList& m_ResultsHeader;
	CStringList& m_ResultsFileHeader;
	CString      m_ResultsFileFormatStg;
};

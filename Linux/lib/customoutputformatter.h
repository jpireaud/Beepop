#pragma once

#include "csv.h"
#include "outputformatter.h"

#include <sstream>

/**
 * Output formatter that will only output the colony size
 */
class CustomOutputFormatter : public COutputFormatter
{
public:
	CustomOutputFormatter(CVarroaPopSession& session);

	virtual ~CustomOutputFormatter();

	virtual void Init(CColony& colony) = 0;

	virtual void Record(CColony& colony, CEvent& event) = 0;

	std::stringstream& Stream();

	void WriteToFile(const std::string& filename, bool compressOutput = false) const;

protected:
	std::stringstream m_stream;
	csv_writer        m_writer;
};

#include "csv.h"

#include <iomanip>
#include <vector>

csv_reader::csv_reader(std::istream& stream, const char& delimiter) : m_stream(stream), m_delimiter(delimiter)
{
}

csv_reader::~csv_reader()
{
}

void csv_reader::skipLines(const size_t& count)
{
	std::string string;
	size_t      leftToSkip = count;
	while (leftToSkip > 0)
	{
		std::getline(m_stream, string);
		leftToSkip--;
	}
}

bool csv_reader::hasMore() const
{
	return m_stream.good() && !m_stream.eof();
}

template <> void csv_reader::read_with_delimiter(std::string& arg, char delimiter)
{
	std::getline(m_stream, arg, delimiter);
	// trim the end of the string to avoid eol issues between OSes
	arg.erase(arg.find_last_not_of(" \n\r\t") + 1);
}

csv_writer::csv_writer(std::ostream& stream, const char& delimiter) : m_stream(stream), m_delimiter(delimiter)
{
	m_stream << std::setprecision(15);
}

csv_writer::~csv_writer()
{
}

template <> void csv_writer::write_with_delimiter(const std::string& arg, char delimiter)
{
	m_stream << "\"" << arg << "\"" << delimiter;
}

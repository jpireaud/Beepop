#pragma once

#include <fstream>
#include <functional>
#include <sstream>
#include <string>
#include <variant>
#include <vector>

class csv_reader
{
public:
	csv_reader(std::istream& istream, const char& delimiter);
	~csv_reader();

	template <typename T> void read_with_delimiter(T& arg, char delimiter = '\n')
	{
		std::string string;
		std::getline(m_stream, string, delimiter);
		std::stringstream stream(string);
		stream >> arg;
	}

	template <typename T> void read(T& arg) { read_with_delimiter(arg); }

	template <typename T, typename... Args> void read(T& arg, Args&... args)
	{
		read_with_delimiter(arg, m_delimiter);
		read(args...);
	}

	void skipLines(const size_t& count);

	//! tells if we reach the end of the file or if more lines are to parse
	bool hasMore() const;

private:
	std::istream& m_stream;
	char          m_delimiter;
};

template <> void csv_reader::read_with_delimiter(std::string& arg, char delimiter);

class csv_writer
{
public:
	csv_writer(std::ostream& ostream, const char& delimiter);
	~csv_writer();

	template <typename T> void write_with_delimiter(const T& arg, char delimiter = '\n')
	{
		m_stream << arg << delimiter;
	}

	template <typename T> void write(const T& arg) { write_with_delimiter(arg); }

	template <typename T, typename... Args> void write(const T& arg, const Args&... args)
	{
		write_with_delimiter(arg, m_delimiter);
		write(args...);
	}

private:
	std::ostream& m_stream;
	char          m_delimiter;
};

template <> void csv_writer::write_with_delimiter(const std::string& arg, char delimiter);

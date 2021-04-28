#include "customoutputformatter.h"

#include "gzip/compress.hpp"

CustomOutputFormatter::CustomOutputFormatter(CVarroaPopSession& session)
    : COutputFormatter(session), m_writer(m_stream, ',')
{
}

CustomOutputFormatter::~CustomOutputFormatter()
{
}

std::stringstream& CustomOutputFormatter::Stream()
{
	return m_stream;
}

void CustomOutputFormatter::WriteToFile(const std::string& filename, bool compressOutput) const
{
	const std::string uncompressedData = m_stream.str();
	if (compressOutput == false)
	{
		std::ofstream outputStream(filename, std::ios_base::out);
		if (outputStream.is_open())
		{
			outputStream << uncompressedData;
			outputStream.close();
		}
		else
		{
			std::cerr << "cannot open output file " << filename << std::endl;
		}
	}
	else
	{
		// let's compress the stream
		const std::size_t compressedSize = uncompressedData.size();
		const std::string compressedData = gzip::compress(uncompressedData.c_str(), compressedSize);

		std::ofstream outputStream(filename + ".gz", std::ios_base::binary);
		if (outputStream.is_open())
		{
			outputStream << compressedData;
			outputStream.close();
		}
		else
		{
			std::cerr << "cannot open output file " << filename << std::endl;
		}
	}
}

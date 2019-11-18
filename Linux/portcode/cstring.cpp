#include "cstring.h"

#include <boost/algorithm/string/case_conv.hpp>

CString::CString() : m_data()
{
}

CString::CString(const std::string& str) : m_data(str)
{
}

CString::CString(const char* cStr) : m_data(cStr)
{
}

bool CString::operator==(const CString& str) const
{
	return m_data == str.m_data;
}

bool CString::operator==(const char* str) const
{
	return m_data == str;
}

CString CString::MakeLower() const
{
	std::string lower(m_data);
	boost::algorithm::to_lower(lower);
	return CString(lower);
}

CString CString::MakeUpper() const
{
	std::string upper(m_data);
	boost::algorithm::to_upper(upper);
	return CString(upper);
}

CString::operator const char* () const
{
	return m_data.c_str();
}

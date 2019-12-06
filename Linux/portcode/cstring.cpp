#include "cstring.h"

#include <boost/algorithm/string/case_conv.hpp>
#include <boost/algorithm/string/trim.hpp>

namespace ba = boost::algorithm;

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

CString& CString::operator+=(const CString& str)
{
	if (&str != this)
	{
		m_data += str.m_data;
	}
	return *this;
}

CString& CString::operator=(const CString& str)
{
	if (&str != this)
	{
		m_data = str.m_data;
	}
	return *this;
}

const std::string& CString::ToString() const
{
	return m_data;
}

CString::operator const char*() const
{
	return m_data.c_str();
}

int CString::GetLength() const
{
	return static_cast<int>(m_data.length());
}

CString CString::MakeLower() const
{
	std::string lower(m_data);
	ba::to_lower(lower);
	return CString(lower);
}

CString CString::MakeUpper() const
{
	std::string upper(m_data);
	ba::to_upper(upper);
	return CString(upper);
}

void CString::Trim()
{
	ba::trim(m_data);
}

void CString::TrimLeft()
{
	ba::trim_left(m_data);
}

void CString::TrimRight()
{
	ba::trim_right(m_data);
}

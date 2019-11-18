#pragma once
#ifndef CMAPSTRINGTOOB_CUSTOM_H
#define CMAPSTRINGTOOB_CUSTOM_H

#include "cobject.h"
#include "cstring.h"

#include <cstddef>

class CMapStringToOb : public CObject
{
public:

	bool IsEmpty() const;
	size_t GetStartPosition() const;
	void SetAt(CString& string, CObject* value);
	void GetNextAssoc(size_t position, CString& string, CObject*& value) const;
	bool Lookup(CString& string, CObject*& value) const;
	void RemoveKey(CString& string);
};

#endif // CMAPSTRINGTOOB_CUSTOM_H

#pragma once
#ifndef CMAPSTRINGTOOB_CUSTOM_H
#define CMAPSTRINGTOOB_CUSTOM_H

#include "cobject.h"
#include "cstring.h"

#include "stdafx.h"

#include <cstddef>
#include <map>

namespace CMapStringToObNs { struct InnerPosition {
    std::map<CString, CObject*>::const_iterator m_it;
}; }

class CMapStringToOb : public CObject
{
public:

	bool IsEmpty() const;
	POSITION GetStartPosition() const;
	void SetAt(CString& string, CObject* value);
	void GetNextAssoc(POSITION& position, CString& string, CObject*& value) const;
	bool Lookup(CString& string, CObject*& value) const;
	void RemoveKey(CString& string);

protected:

    std::map<CString, CObject*> m_map;
    mutable std::unique_ptr<CMapStringToObNs::InnerPosition> m_iterator;
};

#endif // CMAPSTRINGTOOB_CUSTOM_H

#pragma once
#ifndef COBLIST_CUSTOM_H
#define COBLIST_CUSTOM_H

#include "cobject.h"
#include "cstring.h"

#include "stdafx.h"

#include <cstddef>
#include <list>

namespace CObListNs { struct InnerPosition {
    std::list<CObject*>::const_iterator m_it;
}; }

class CObList : public CObject
{
public:
	CObList();

	INT_PTR GetCount() const;
	BOOL IsEmpty() const;

	// In the MFC framework we use the index to go through the linked list and return
	// the actual node wrapped in the POSITION structure
	POSITION FindIndex(INT_PTR index) const;

	CObject* GetAt(POSITION position) const;
	CObject* GetHead() const;
	CObject* GetPrev(POSITION& position) const;
	CObject* GetNext(POSITION& position) const;

	POSITION GetHeadPosition() const;
	POSITION GetTailPosition() const;

	POSITION AddHead (CObject* object);
	POSITION AddTail (CObject* object);
	void RemoveAt(POSITION position);
	CObject* RemoveHead();
	CObject* RemoveTail();
	void RemoveAll();

protected:

    std::list<CObject*> m_data;
    mutable std::unique_ptr<CObListNs::InnerPosition> m_iterator;
};

class CStringList : public CObList
{
public:
	CStringList();

	void AddTail(const CString& string);
};

#endif // COBLIST_CUSTOM_H

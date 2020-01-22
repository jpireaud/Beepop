#pragma once
#ifndef COBLIST_CUSTOM_H
#define COBLIST_CUSTOM_H

#include "cobject.h"
#include "cstring.h"

#include "stdafx.h"

#include <cstddef>
#include <list>

namespace CObListNs { struct InnerPosition : public __POSITION {
	InnerPosition(const std::list<CObject*>::const_iterator& it) : m_it(it) {}
	InnerPosition* copy() { return new InnerPosition(m_it); }
    std::list<CObject*>::const_iterator m_it;
}; }

class CObList : public CObject
{
public:
	CObList();
	virtual ~CObList();

	INT_PTR GetCount() const;
	BOOL IsEmpty() const;

	// In the MFC framework we use the index to go through the linked list and return
	// the actual node wrapped in the POSITION structure
	POSITION FindIndex(INT_PTR index) const;

	CObject* GetAt(POSITION position) const;
	CObject* GetHead() const;
	CObject* GetTail() const;
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
};

namespace CStringListNs { struct InnerPosition : public __POSITION {
	InnerPosition(const std::list<CString>::const_iterator& it) : m_it(it) {}
	InnerPosition* copy() { return new InnerPosition(m_it); }
    std::list<CString>::const_iterator m_it;
}; }

class CStringList : public CObject
{
public:
	CStringList();
	~CStringList();

	INT_PTR GetCount() const;
	BOOL IsEmpty() const;

	const CString& GetNext(POSITION& position) const;

	POSITION GetHeadPosition() const;
	
	void AddTail(const CString& string);
	
	void RemoveAll();

protected:

    std::list<CString> m_data;
};

#endif // COBLIST_CUSTOM_H

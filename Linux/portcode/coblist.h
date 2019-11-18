#pragma once
#ifndef COBLIST_CUSTOM_H
#define COBLIST_CUSTOM_H

#include "cobject.h"
#include "cstring.h"

#include <cstddef>

class CObList : public CObject
{
public:
	CObList();

	size_t GetCount() const;
	bool IsEmpty() const;

	// In the MFC framework we use the index to go through the linked list and return
	// the actual node wrapped in the POSITION structure
	size_t FindIndex(size_t index) const;

	CObject* GetAt(size_t position) const;
	CObject* GetHead() const;
	CObject* GetPrev(size_t position) const;
	CObject* GetNext(size_t position) const;

	size_t GetHeadPosition() const;
	size_t GetTailPosition() const;

	size_t AddHead (CObject* object);
	size_t AddTail (CObject* object);
	void RemoveAt(size_t position);
	CObject* RemoveHead();
	CObject* RemoveTail ();
	void RemoveAll();
};

class CStringList : public CObList
{
public:
	CStringList();

	void AddTail(const CString& string);
};

#endif // COBLIST_CUSTOM_H

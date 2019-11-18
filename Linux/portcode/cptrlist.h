#pragma once
#ifndef CPTRLIST_CUSTOM_H
#define CPTRLIST_CUSTOM_H

#include "cobject.h"

#include <cstddef>

class CPtrList : public CObject
{
    public:
    
};

template<class BASE_CLASS, class TYPE>
class CTypedPtrList : public BASE_CLASS
{
public:

	bool IsEmpty() const;
	size_t GetCount() const;
	TYPE GetAt(size_t position) const;
	size_t AddTail(TYPE object);
	void RemoveAt(size_t position);
	size_t GetHeadPosition() const;
	TYPE GetHead() const;
	TYPE GetTail() const;
	TYPE GetNext(size_t position) const;
	TYPE RemoveHead() const;
	void RemoveAll() const;
};

#endif // CPTRLIST_CUSTOM_H

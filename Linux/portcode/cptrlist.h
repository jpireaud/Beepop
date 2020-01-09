#pragma once
#ifndef CPTRLIST_CUSTOM_H
#define CPTRLIST_CUSTOM_H

#include "cobject.h"

#include <cstddef>
#include <list>

namespace CPtrListNs { template<class TYPE> struct InnerPosition {
    typename std::list<TYPE>::const_iterator m_it;
}; }

class CPtrList : public CObject
{
    public:
    
};

template<class BASE_CLASS, class TYPE>
class CTypedPtrList
{
public:

	CTypedPtrList();
	~CTypedPtrList();

	BOOL IsEmpty() const;
	INT_PTR GetCount() const;
	TYPE GetAt(POSITION position) const;
	POSITION AddTail(TYPE object);
	void RemoveAt(POSITION position);
	POSITION GetHeadPosition() const;
	POSITION GetTailPosition() const;
	TYPE GetHead() const;
	TYPE GetTail() const;
	TYPE GetNext(POSITION& position) const;
	TYPE RemoveHead();
	void RemoveAll();

protected:

    std::list<TYPE> m_data;
    mutable std::unique_ptr<CPtrListNs::InnerPosition<TYPE>> m_iterator;
};

#include "cptrlist.inline.h"

#endif // CPTRLIST_CUSTOM_H

#pragma once
#ifndef CARRAY_CUSTOM_H
#define CARRAY_CUSTOM_H

#include "cobject.h"

#include <vector>

template<class TYPE, class ARG_TYPE = const TYPE&>
class CArray : public CObject
{
public:
	BOOL IsEmpty() const;

	INT_PTR GetCount() const;

	void RemoveAll();

	void Copy(const CArray& array);

	void Add(const TYPE& element);

	const TYPE& operator[](INT_PTR index) const;
	
	TYPE& operator[](INT_PTR index);

	void RemoveAt(INT_PTR index);

	void SetSize(INT_PTR size, INT_PTR growBy = -1);

protected:

    std::vector<TYPE> m_data;
};

#include "carray.inline.h"

#endif // CARRAY_CUSTOM_H

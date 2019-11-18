#pragma once
#ifndef CARRAY_CUSTOM_H
#define CARRAY_CUSTOM_H

#include "cobject.h"

#include <cstddef>

template<class TYPE, class ARG_TYPE = const TYPE&>
class CArray : public CObject
{
public:
	bool IsEmpty() const;

	int GetCount() const;

	void RemoveAll();

	void Copy(const CArray& array);

	void Add(const TYPE& element);

	const TYPE& operator[](const size_t& index) const;
	TYPE& operator[](const size_t& index);

	void RemoveAt(const size_t& index);

	void SetSize(size_t size);
	void SetSize(size_t columnSize, size_t rowSize);
};

#endif // CARRAY_CUSTOM_H

#pragma once
#ifndef CSTRINGARRAY_CUSTOM_H
#define CSTRINGARRAY_CUSTOM_H

#include "cobject.h"
#include "cstring.h"

#include <cstdint>

class CStringArray : public CObject
{
public:

	int32_t GetSize() const;
	int32_t GetCount() const;
	bool IsEmpty() const;
	int32_t GetUpperBound() const;
	void SetSize(int32_t nNewSize, int32_t nGrowBy = -1);

	CString GetAt(int32_t position);
	void Add(const CString& str);

	const CString& operator[](const size_t& index) const;
	CString& operator[](const size_t& index);

	void RemoveAll();
}; 


#endif // CSTRINGARRAY_CUSTOM_H

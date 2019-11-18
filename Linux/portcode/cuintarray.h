#pragma once
#ifndef CUINTARRAY_CUSTOM_H
#define CUINTARRAY_CUSTOM_H

#include "cobject.h"

#include <cstdint>

class CUIntArray : public CObject
{
public:
    int GetSize() const;
    uint32_t GetAt(uint32_t index) const;

    void Add(uint32_t eventId);
    void RemoveAt(uint32_t index);

	void RemoveAll();
};

#endif // CUINTARRAY_CUSTOM_H

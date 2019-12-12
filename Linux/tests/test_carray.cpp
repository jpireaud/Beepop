#include "catch2/catch.hpp"

//! include explicitely since we are not using the pre-compiled header for tests
//! may change this in the future
#include "stdafx.h" 

#include "carray.h"

TEST_CASE("CArray operations", "[port]") {
    
    CArray<int32_t, int32_t> intArray;
}

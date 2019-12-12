#include "catch2/catch.hpp"

//! include explicitely since we are not using the pre-compiled header for tests
//! may change this in the future
#include "stdafx.h" 

#include "cptrlist.h"

TEST_CASE("CPtrList operations", "[port]") {
    
    CTypedPtrList<CPtrList, CString*> list;
}

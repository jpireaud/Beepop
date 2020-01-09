#include "catch2/catch.hpp"

//! include explicitely since we are not using the pre-compiled header for tests
//! may change this in the future
#include "stdafx.h" 

#include "coledatetime.h"

TEST_CASE("COleDateTime operations", "[port]") {
    
    COleDateTime dateTime;
    
    SECTION("default date") {

        CHECK(dateTime.GetYear() == 1899);
        CHECK(dateTime.GetMonth() == 12);
        CHECK(dateTime.GetDay() == 30);
    }
}
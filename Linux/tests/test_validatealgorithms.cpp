#include "catch2/catch.hpp"

//! include explicitely since we are not using the pre-compiled header for tests
//! may change this in the future
#include "stdafx.h"

TEST_CASE("Validate algorithms", "[port]")
{
    SECTION("Progressive aging")
    {
        CHECK(true);
    }
}

#include "catch2/catch.hpp"

#include "cstring.h"

TEST_CASE("CString operations", "[port]") {
	CString myString("ThisIsAString");
	CHECK(myString.MakeLower() == "thisisastring");
	CHECK(myString.MakeUpper() == "THISISASTRING");
}
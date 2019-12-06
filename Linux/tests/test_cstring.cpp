#include "catch2/catch.hpp"

//! include explicitely since we are not using the pre-compiled header for tests
//! may change this in the future
#include "stdafx.h" 

#include "cstring.h"

TEST_CASE("CString operations", "[port]") {

	// check creation and comparison
	CString myString("ThisIsAString");
	CHECK(myString == "ThisIsAString");
	CHECK(myString == CString("ThisIsAString"));

	SECTION("append data") {

		myString += " - SomeAdditional Data";
		CHECK(myString == "ThisIsAString - SomeAdditional Data");
	}

	SECTION("overwrite data") {

		myString = "Some New Data";
		CHECK(myString == "Some New Data");
	}

	SECTION("conversions") {

		CHECK(myString.ToString() == std::string("ThisIsAString"));

		char* buffer = new char[myString.GetLength()+1];
		sprintf(buffer, "%s", (const char*)myString);
		CHECK(myString == buffer);
		delete[] buffer;
	}
	
	SECTION("casing") {
		
		CHECK(myString.MakeLower() == "thisisastring");
		CHECK(myString.MakeUpper() == "THISISASTRING");	
	}

	SECTION("triming") {
		
		myString = "     With Some Leading Spaces and Trailing Spaces   ";

		SECTION("both") {

			myString.Trim();
			CHECK(myString == "With Some Leading Spaces and Trailing Spaces");
		}
		
		SECTION("left") {

			myString.TrimLeft();
			CHECK(myString == "With Some Leading Spaces and Trailing Spaces   ");
		}
		
		SECTION("right") {

			myString.TrimRight();
			CHECK(myString == "     With Some Leading Spaces and Trailing Spaces");
		}
	}

	SECTION("format") {

		myString.Format("This is an integer %d", 10);
		CHECK(myString == "This is an integer 10");
		std::string fmtString = fmt::sprintf("This is an integer %d", 10);
		CHECK(fmtString == "This is an integer 10");
	}
}

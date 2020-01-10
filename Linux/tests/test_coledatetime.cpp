#include "catch2/catch.hpp"

//! include explicitely since we are not using the pre-compiled header for tests
//! may change this in the future 
#include "stdafx.h" 

#include "coledatetime.h"

TEST_CASE("COleDateTime operations", "[port]") {
    
    SECTION("default date") {
        
        COleDateTime dateTime;

        CHECK(dateTime.GetStatus() == COleDateTime::valid);

        CHECK(dateTime.GetYear() == 1899);
        CHECK(dateTime.GetMonth() == 12);
        CHECK(dateTime.GetDay() == 30);
    }

    SECTION("custom date") {

        COleDateTime dateTime (1982, 1, 11, 13, 3, 0);
        
        CHECK(dateTime.GetStatus() == COleDateTime::valid);

        CHECK(dateTime.GetYear() == 1982);
        CHECK(dateTime.GetMonth() == 1);
        CHECK(dateTime.GetDay() == 11);
        CHECK(dateTime.GetHour() == 13);
        CHECK(dateTime.GetMinute() == 3);
        CHECK(dateTime.GetDayOfYear() == 11);
    }

    SECTION("date comparison") {

        COleDateTime first (1982, 1, 11, 13, 3, 0);
        COleDateTime second (1982, 8, 28, 21, 0, 0);
        COleDateTime third (2020, 8, 28, 21, 0, 0);
        COleDateTime fourth (2020, 8, 28, 21, 0, 1);
        COleDateTime fifth (2020, 8, 28, 21, 0, 1);
        
        CHECK(first.GetStatus() == COleDateTime::valid);
        CHECK(second.GetStatus() == COleDateTime::valid);
        CHECK(third.GetStatus() == COleDateTime::valid);
        CHECK(fourth.GetStatus() == COleDateTime::valid);
        CHECK(fifth.GetStatus() == COleDateTime::valid);

        CHECK(first < second);
        CHECK(second > first);
        CHECK(first >= first);
        CHECK(second >= second);

        CHECK(third < fourth);
        CHECK(fourth > third);
        CHECK(fourth >= fifth);
        CHECK(fourth >= third);
    }

    SECTION("date operations") {

        COleDateTime first (1982, 1, 11, 13, 3, 0);
        COleDateTime second (1982, 8, 28, 21, 0, 0);
        COleDateTime third (2020, 8, 28, 21, 0, 0);
        COleDateTime fourth (2020, 8, 28, 21, 0, 1);
        COleDateTime fifth (2020, 8, 28, 21, 0, 1);
        
        CHECK(first.GetStatus() == COleDateTime::valid);
        CHECK(second.GetStatus() == COleDateTime::valid);
        CHECK(third.GetStatus() == COleDateTime::valid);
        CHECK(fourth.GetStatus() == COleDateTime::valid);
        CHECK(fifth.GetStatus() == COleDateTime::valid);

        CHECK((second - first).GetDays() == 229);
        CHECK((fourth - third).GetDays() == 0);

        auto sixth = fifth + COleDateTimeSpan(3.0);
        CHECK((sixth - fifth).GetDays() == 3);
        
        auto seventh = sixth - COleDateTimeSpan(1.0);
        CHECK((seventh - fifth).GetDays() == 2);
    }

    SECTION("COleDateTimeSpan") {

        SECTION("COleDateTimeSpan()") {
            {
                COleDateTimeSpan span(2.0);
                CHECK(span.GetDays() == 2);
            }
            {
                COleDateTimeSpan span(2.3);
                CHECK(span.GetDays() == 2);
            }
            {
                COleDateTimeSpan span(4.9);
                CHECK(span.GetDays() == 4);
            }
        }

        SECTION("COleDateTimeSpan(...)") {
            {
                COleDateTimeSpan span(2, 48, 50, 1);
                CHECK(span.GetDays() == 4);
            }
            {
                COleDateTimeSpan span(0, 24, 0, 0);
                CHECK(span.GetDays() == 1);
            }
            {
                COleDateTimeSpan span(0, 48, 60 * 24, 0);
                CHECK(span.GetDays() == 3);
            }
        }
    }
}
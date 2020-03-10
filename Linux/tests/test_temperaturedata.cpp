#include "catch2/catch.hpp"

//! include explicitely since we are not using the pre-compiled header for tests
//! may change this in the future
#include "stdafx.h" 

#include "helpers/common.h" 

#define _USE_MATH_DEFINES
#include <cmath>

#include <cstdint>
#include <optional>
#include <variant>
#include <vector>

#include <boost/filesystem.hpp>
namespace bfs = boost::filesystem;

#include <boost/date_time.hpp>
namespace bd = boost::gregorian;

#include "weathergriddata.h"

using namespace WeatherGridDataNs;

// The matcher class
class DayLengthResultMatcher : public Catch::MatcherBase<DayLengthResult> {
    DayLengthResult m_result;
    std::float_t m_epsilon = 1.e-5f;
public:
    DayLengthResultMatcher(const DayLengthResult& result) : m_result(result){}

    // Performs the test for this matcher
    bool match(const DayLengthResult& testing) const override {
        return Catch::Floating::WithinRelMatcher(m_result.sunrise, m_epsilon).match(testing.sunrise)
            && Catch::Floating::WithinRelMatcher(m_result.sunset, m_epsilon).match(testing.sunset)
            && Catch::Floating::WithinRelMatcher(m_result.daylength, m_epsilon).match(testing.daylength);
    }

    // Produces a string describing what this matcher does. It should
    // include any provided data (the begin/ end in this case) and
    // be written as if it were stating a fact (in the output it will be
    // preceded by the value under test).
    virtual std::string describe() const override {
        std::ostringstream ss;
        ss << "is matching sunrise:" << m_result.sunrise << " sunset:" << m_result.sunset << " daylength:" << m_result.daylength;
        return ss.str();
    }
};

// The builder function
inline DayLengthResultMatcher DayLengthResultEq(const DayLengthResult& result) {
    return DayLengthResultMatcher(result);
}

template<typename Container, typename Compare>
struct CompareMatcher : Catch::MatcherBase<Container> {

    CompareMatcher(const Container& comparator, const Compare& compare)
        : m_comparator(comparator),
        m_compare(compare) {}

    bool match(const Container& v) const override {
        if (m_comparator.size() != v.size()) {
            return false;
        }
        for (size_t i = 0; i < v.size(); ++i) {
            if (!m_compare(m_comparator[i], v[i])) {
                return false;
            }
        }
        return true;
    }

    virtual std::string describe() const override {
        return "Equals: " + Catch::Detail::stringify(m_comparator);
    }

    const Container& m_comparator;
    const Compare& m_compare;
};

template<typename Container, typename C>
CompareMatcher<Container, C> Compare(const Container& comparator, const C& compare) {
    return CompareMatcher<Container, C>(comparator, compare);
}

auto EqualsApprox(const std::array<std::float_t, 24>& comparator) {
    return Compare(comparator, [=](std::float_t actual, std::float_t expected) {
        return actual == Approx(expected);
    });
}

TEST_CASE("Temperature Data", "[input]") {
    
    SECTION("Load") {

        bfs::path weatherFile (bfs::path(GetSimulationsDir()) / "ObservedHistoricalBinary" / "data_46.03125_-118.34375");

        std::cout << GetSimulationsDir() << std::endl;

        CHECK(bfs::exists(weatherFile));

        auto data = LoadGridData<ObservedHistoricalItem>(weatherFile.string());
        bd::date startDate(1979, bd::Jan, 1);
        bd::date endDate = startDate + bd::days(data.data().size() - 1 /* first day*/);
        CHECK(endDate.year() == 2016);
        CHECK(endDate.month() == 12);
        CHECK(endDate.day() == 31);
    }

    SECTION("Load Rcp85Binary") {

        bfs::path weatherFile(bfs::path(GetSimulationsDir()) / "Rcp85Binary" / "data_46.03125_-118.34375");

        std::cout << GetSimulationsDir() << std::endl;

        CHECK(bfs::exists(weatherFile));

        auto data = LoadGridData<Rcp85>(weatherFile.string());
        bd::date startDate(2006, bd::Jan, 1);
        bd::date endDate = startDate + bd::days(data.data().size() - 1 /* first day*/);
        CHECK(endDate.year() == 2099);
        CHECK(endDate.month() == 12);
        CHECK(endDate.day() == 31);
    }

    SECTION("JDay") {

        CHECK(ComputeJDay(COleDateTime(2019, 1, 1, 0, 0, 0)) == 1);
        CHECK(ComputeJDay(COleDateTime(2019, 2, 28, 0, 0, 0)) == 59);
        CHECK(ComputeJDay(COleDateTime(2019, 2, 29, 0, 0, 0)) == 60);
        CHECK(ComputeJDay(COleDateTime(2019, 3, 1, 0, 0, 0)) == 60);
        CHECK(ComputeJDay(COleDateTime(2019, 12, 31, 0, 0, 0)) == 365);
        CHECK(ComputeJDay(COleDateTime(2020, 1, 1, 0, 0, 0)) == 1);
        CHECK(ComputeJDay(COleDateTime(2020, 2, 28, 0, 0, 0)) == 59);
        CHECK(ComputeJDay(COleDateTime(2020, 2, 29, 0, 0, 0)) == 60);
        CHECK(ComputeJDay(COleDateTime(2020, 12, 31, 0, 0, 0)) == 366);
    }

    SECTION("daylength") {

        DayLengthResult northPole1 = { -99.0f, -99.0f, 0.0f };
        DayLengthResult northPole180 = { 99.0f, 99.0f, 24.0f };

        CHECK_THAT(DayLength(90.0f, 1), DayLengthResultEq(northPole1));
        CHECK_THAT(DayLength(90.0f, 180), DayLengthResultEq(northPole180));

        DayLengthResult pullman1 = { 7.694178f, 16.30582f, 8.611644f };
        DayLengthResult pullman180 = { 4.010171f, 19.98983f, 15.97966f };

        CHECK_THAT(DayLength(46.7298f, 1), DayLengthResultEq(pullman1));
        CHECK_THAT(DayLength(46.7298f, 180), DayLengthResultEq(pullman180));

        DayLengthResult rio1 = { 6.624304f, 17.3757f, 10.75139f };
        DayLengthResult rio180 = { 5.207381f, 18.79262f, 13.58524f };

        CHECK_THAT(DayLength(22.9068f, 1), DayLengthResultEq(rio1));
        CHECK_THAT(DayLength(22.9068f, 180), DayLengthResultEq(rio180));
    }

    SECTION("hourly temperature") {
        // JDay 1
        {
            auto current_daylength = DayLength(46.7298f, 1);
            auto next_daylength = DayLength(46.7298f, 2);

            HourlyTempraturesEstimator input;
            input.tmin = -2.55f;
            input.tmax = -0.28f;
            input.sunrise = current_daylength.sunrise;
            input.sunset = current_daylength.sunset;
            input.daylength = current_daylength.daylength;

            input.next_tmin = -6.71f;
            input.next_sunrise = next_daylength.sunrise;

            input.compute();

            std::array<std::float_t, 24> expectedResult = { -2.550000f,-2.550000f,-2.550000f,-2.550000f,-2.550000f,-2.550000f,-2.550000f,-2.550000f,-2.377236f,-1.824559f,-1.316665f,-0.8849064f,-0.5559374f,-0.3500657f,-0.28f,-0.3500657f,-0.5559374f,-1.787940f,-2.794280f,-3.479060f,-3.998755f,-4.417698f,-4.768682f, -5.070708f };
            CHECK_THAT(input.hourly_temperatures, EqualsApprox(expectedResult));
        }
        // JDay 2
        {
            auto previous_daylength = DayLength(46.7298f, 1);
            auto current_daylength = DayLength(46.7298f, 2);
            auto next_daylength = DayLength(46.7298f, 3);

            HourlyTempraturesEstimator input;
            input.tmin = -6.71f;
            input.tmax = 1.46f;
            input.sunrise = current_daylength.sunrise;
            input.sunset = current_daylength.sunset;
            input.daylength = current_daylength.daylength;

            input.prev_tmin = -2.55f;
            input.prev_tmax = -0.28f;
            input.prev_sunset = previous_daylength.sunset;

            input.next_tmin = -6.71f;
            input.next_sunrise = next_daylength.sunrise;

            input.compute();

            std::array<std::float_t, 24> expectedResult = { -5.444190f,-5.685756f,-5.903585f,-6.101928f,-6.283987f,-6.452233f,-6.608616f,-6.754699f,-6.074356f,-4.088088f,-2.263309f,-0.7124124f,0.4690795f,1.2083956f,1.46f,1.2083956f,0.4690795f,-1.082260f,-2.173649f,-2.915478f,-3.478154f,-3.931593f,-4.311390f,-4.638157f };
            CHECK_THAT(input.hourly_temperatures, EqualsApprox(expectedResult));
        }
        // JDay 148
        {
            auto previous_daylength = DayLength(46.7298f, 147);
            auto current_daylength = DayLength(46.7298f, 148);
            auto next_daylength = DayLength(46.7298f, 149);

            HourlyTempraturesEstimator input;
            input.tmin = 8.83f;
            input.tmax = 18.02f;
            input.sunrise = current_daylength.sunrise;
            input.sunset = current_daylength.sunset;
            input.daylength = current_daylength.daylength;

            input.prev_tmin = 8.33f;
            input.prev_tmax = 17.42f;
            input.prev_sunset = previous_daylength.sunset;

            input.next_tmin = 5.62f;
            input.next_sunrise = next_daylength.sunrise;

            input.compute();

            std::array<std::float_t, 24> expectedResult = { 10.779638f,10.463412f,10.194304f,9.960077f,9.752718f,9.976793f,11.420404f,12.79732f,14.07209f,15.21189f,16.18737f,16.97343f,17.54982f,17.90169f,18.02f,17.90169f,17.54982f,16.97343f,16.18737f,15.21189f,13.56064f,11.23618f,9.791873f,8.741350f };
            CHECK_THAT(input.hourly_temperatures, EqualsApprox(expectedResult));
        }
        // JDay last
        {
            auto previous_daylength = DayLength(46.7298f, 150);
            auto current_daylength = DayLength(46.7298f, 151);

            HourlyTempraturesEstimator input;
            input.tmin = 7.64f;
            input.tmax = 13.75f;
            input.sunrise = current_daylength.sunrise;
            input.sunset = current_daylength.sunset;
            input.daylength = current_daylength.daylength;

            input.prev_tmin = 7.57f;
            input.prev_tmax = 17.29f;
            input.prev_sunset = previous_daylength.sunset;

            input.compute();

            std::array<std::float_t, 24> expectedResult = { 9.918212f,9.548716f,9.234689f,8.961630f,8.720073f,8.445311f,9.399063f,10.30797f,11.14885f,11.90026f,12.54306f,13.06085f,13.44042f,13.67211f,13.75f,13.67211f,13.44042f,13.06085f,12.54306f,11.90026f,7.64000f,7.64000f,7.640000f,7.640000f };
            CHECK_THAT(input.hourly_temperatures, EqualsApprox(expectedResult));
        }
    }
}

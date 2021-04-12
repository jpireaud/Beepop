#include "catch2/catch.hpp"

//! include explicitely since we are not using the pre-compiled header for tests
//! may change this in the future
#include "stdafx.h"

#include "adult.h"
#include "brood.h"
#include "colony.h"
#include "weatherevents.h"

#include <deque>
#include <stack>

TEST_CASE("Aging")
{
	SECTION("Adult Aging")
	{
		auto colony = std::unique_ptr<CColony>(new CColony);

		auto event = std::unique_ptr<CEvent>(new CEvent);
		event->SetForageInc(0.1);

		CForageBasedAgingAdultList adults;
		adults.SetLength(2);
		adults.SetPropTransition(1.0);

		auto brood = new CBrood(10);
		adults.Update(brood, colony.get(), event.get(), true);

		CHECK(adults.GetQuantity() == 10);
		CHECK(adults.GetCaboose().size() == 0);

		brood = new CBrood(15);
		adults.Update(brood, colony.get(), event.get(), true);

		CHECK(adults.GetQuantity() == 25);
		CHECK(adults.GetCaboose().size() == 0);

		event->SetForageInc(2.0);

		brood = new CBrood(2);
		adults.Update(brood, colony.get(), event.get(), true);

		CHECK(adults.GetQuantity() == 2);
		CHECK(adults.GetCaboose().size() == 2);
		CHECK(adults.GetCaboose()[0]->age == Approx(0.0));
		CHECK(adults.GetCaboose()[1]->age == Approx(0.1));
	}

	SECTION("Update List Length")
	{
		auto colony = std::unique_ptr<CColony>(new CColony);
		auto event = std::unique_ptr<CEvent>(new CEvent);
		event->SetForageInc(1.0);

		std::vector<int> quantity = {20, 39, 57, 74, 70, 66, 62, 58, 54, 50, 46, 42, 38, 34, 30, 26, 22, 18, 14, 10};
		std::vector<int> cabooses = {0, 0, 0, 0, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5};

		CForageBasedAgingAdultList adults;
		adults.SetPropTransition(1.0);
		adults.SetLength(4);

		const int numberOfAdultsBox = 20;
		for (size_t i = 0; i < numberOfAdultsBox; i++)
		{
			auto brood = new CBrood(numberOfAdultsBox - i);
			adults.Update(brood, colony.get(), event.get(), true);
			CHECK(adults.GetQuantity() == quantity[i]);
			CHECK(adults.GetCabooseQuantity() == cabooses[i]);
			adults.ClearCaboose();
		}
	}

	SECTION("Update List Length - Variable forage inc")
	{
		auto colony = std::unique_ptr<CColony>(new CColony);
		auto event = std::unique_ptr<CEvent>(new CEvent);

		std::vector<double> forageInc = {0.1, 0.2, 0.5, 0.8, 1.0, 1.0, 0.7, 0.3, 0.0, 0.0,
		                                 0.0, 0.1, 0.5, 0.7, 1.0, 1.0, 1.0, 1.0, 0.8, 0.2};
		std::vector<int>    quantity = {20, 39, 57, 74, 51, 31, 45, 42, 54, 65, 75, 84, 92, 84, 21, 11, 9, 7, 9, 6};
		std::vector<int>    cabooses = {0, 0, 0, 0, 39, 35, 0, 16, 0, 0, 0, 0, 0, 15, 69, 15, 6, 5, 0, 4};

		CForageBasedAgingAdultList adults;
		adults.SetPropTransition(1.0);
		adults.SetLength(2);

		const int numberOfAdultsBox = 20;
		for (size_t i = 0; i < numberOfAdultsBox; i++)
		{
			event->SetForageInc(forageInc[i]);
			auto brood = new CBrood(numberOfAdultsBox - i);
			adults.Update(brood, colony.get(), event.get(), true);
			CHECK(adults.GetQuantity() == quantity[i]);
			CHECK(adults.GetCabooseQuantity() == cabooses[i]);
			adults.ClearCaboose();
		}
	}
}
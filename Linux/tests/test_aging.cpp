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

		CForageBasedAgingAdultList adults;
		adults.SetLength(2);
		adults.SetPropTransition(1.0);

		auto brood = new CBrood(10);

        event->SetForageInc(0.5);
        adults.Update(brood, colony.get(), event.get(), true);

		CHECK(adults.GetQuantity() == 10);
		CHECK(adults.GetQuantityAt(0) == 10);
		CHECK(adults.GetQuantityAt(1) == 0);
		CHECK(adults.GetQuantityAt(2) == 0);
		CHECK(adults.GetCabooseQueue().size() == 0);

		brood = new CBrood(15);

        event->SetForageInc(0.7);
        adults.Update(brood, colony.get(), event.get(), true);

		CHECK(adults.GetQuantity() == 25);
		CHECK(adults.GetQuantityAt(0) == 15);
		CHECK(adults.GetQuantityAt(1) == 10);
		CHECK(adults.GetQuantityAt(2) == 0);
		CHECK(adults.GetCabooseQueue().size() == 0);

		brood = new CBrood(2);
        event->SetForageInc(0.5);
		adults.Update(brood, colony.get(), event.get(), true);

		CHECK(adults.GetQuantity() == 27);
		CHECK(adults.GetQuantityAt(0) == 2);
		CHECK(adults.GetQuantityAt(1) == 25);
		CHECK(adults.GetQuantityAt(2) == 0);
		CHECK(adults.GetCabooseQueue().size() == 0);

        event->SetForageInc(2.0);
        adults.Update(NULL, colony.get(), event.get(), true);
        CHECK(adults.GetCabooseQueue().size() == 3);
		CHECK(adults.GetCabooseQueue()[0]->GetCurrentAge() == Approx(0.5));
        CHECK(adults.GetCabooseQueue()[1]->GetCurrentAge() == Approx(1.2));
        CHECK(adults.GetCabooseQueue()[2]->GetCurrentAge() == Approx(1.7));
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

		std::vector<int> countAtAge0 = {20, 39, 57, 35, 16, 15, 29, 27, 39, 50, 60, 69, 77, 15, 6, 5, 4, 3, 5, 3};
		std::vector<int> countAtAge1 = {0, 0, 0, 39, 35, 16, 16, 15, 15, 15, 15, 15, 15, 69, 15, 6, 5, 4, 4, 3};

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
			CHECK(adults.GetQuantityAt(0) == countAtAge0[i]);
			CHECK(adults.GetQuantityAt(1) == countAtAge1[i]);
			CHECK(adults.GetQuantityAt(0, 1) == quantity[i]);
			CHECK(adults.GetCabooseQuantity() == cabooses[i]);
			adults.ClearCaboose();
		}
	}

	SECTION("Update List Length - Variable forage inc")
	{
		auto colony = std::unique_ptr<CColony>(new CColony);
		auto event = std::unique_ptr<CEvent>(new CEvent);

		COleDateTime summer(2000, 06, 15, 0, 0, 0);
		event->SetTime(summer);

		std::vector<double> forageInc = {0.1, 0.2, 0.5, 0.8, 1.0, 1.0, 0.7, 0.3, 0.0, 0.0,
		                                 0.0, 0.1, 0.5, 0.7, 1.0, 1.0, 1.0, 1.0, 0.8, 0.2};
		std::vector<int>    quantity = {20, 39, 57, 74, 51, 31, 45, 42, 54, 65, 75, 84, 92, 84, 21, 11, 9, 7, 9, 6};
		std::vector<int>    cabooses = {0, 0, 0, 0, 39, 35, 0, 16, 0, 0, 0, 0, 0, 15, 69, 15, 6, 5, 0, 4};

		std::vector<int> countAtAge0 = {20, 39, 57, 35, 16, 15, 29, 27, 39, 50, 60, 69, 77, 15, 6, 5, 4, 3, 5, 3};
		std::vector<int> countAtAge1 = {0, 0, 0, 39, 35, 16, 16, 15, 15, 15, 15, 15, 15, 69, 15, 6, 5, 4, 4, 3};

		std::vector<int> foragersQuantity = {0,  0,  0,  0,  39, 54, 54, 51, 51, 51,
		                                     51, 51, 51, 48, 30, 24, 21, 18, 18, 15};

		CForageBasedAgingAdultList adults;
		adults.SetPropTransition(1.0);
		adults.SetLength(2);
		adults.SetColony(colony.get());

		CForageBasedAgingForagersList foragers;
        foragers.SetColony(colony.get());
        foragers.SetPropTransition(1.0);
        foragers.SetLength(3);
		colony->m_CurrentForagerLifespan = 3.0;

		const int numberOfAdultsBox = 20;
		for (size_t i = 0; i < numberOfAdultsBox; i++)
		{
			event->SetForageInc(forageInc[i]);
			auto brood = new CBrood(numberOfAdultsBox - i);
			adults.Update(brood, colony.get(), event.get(), true);
			CHECK(adults.GetQuantity() == quantity[i]);
			CHECK(adults.GetQuantityAt(0) == countAtAge0[i]);
			CHECK(adults.GetQuantityAt(1) == countAtAge1[i]);
			CHECK(adults.GetQuantityAt(0, 1) == quantity[i]);
			CHECK(adults.GetCabooseQuantity() == cabooses[i]);

            foragers.Update(adults.GetCabooseQueue(), colony.get(), event.get());
			CHECK(foragers.GetQuantity() == foragersQuantity[i]);
		}
	}
}

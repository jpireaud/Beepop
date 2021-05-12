//
//  testoutputformatter.cpp
//  VarroaPopTests
//
//  Created by Julien Pireaud on 4/28/21.
//

#include "testoutputformatter.h"

#include "colony.h"
#include "csv.h"

std::vector<DataItem> GetItemsFromFile(const std::string& filepath)
{
	std::vector<DataItem> items;
	std::ifstream         fileStream(filepath, std::ifstream::in);
	if (fileStream.is_open())
	{
		csv_reader reader(fileStream, ',');
		reader.skipLines(1);
		while (reader.hasMore())
		{
			DataItem item;
			reader.read(
			    item.date, item.queenStrength, item.eggs, item.larvae, item.broods, item.adults, item.foragers,
			    item.colonySize);
			if (!item.date.empty()) items.push_back(item);
		}
	}
	return items;
}

TestOutputFormatter::TestOutputFormatter(CVarroaPopSession& session) : CustomOutputFormatter(session)
{
}

TestOutputFormatter::~TestOutputFormatter()
{
}

void TestOutputFormatter::Init(CColony& colony)
{
	m_stream
	    << "Date, QueenStrength, Eggs, Larvae, Broods, Adults, Foragers, Colony Size, Day One, DD, L, N, P, dd, l, n";
	m_stream << std::endl;
}

void TestOutputFormatter::Record(CColony& colony, CEvent& event)
{
	if (m_windowed == false || (event.GetTime() >= m_from && event.GetTime() <= m_to))
	{
		m_stream << event.GetDateStg("%m/%d/%Y");
		m_stream << "," << colony.queen.GetQueenStrength();
		m_stream << "," << colony.Weggs.GetQuantity();
		m_stream << "," << colony.Wlarv.GetQuantity();
		m_stream << "," << colony.CapWkr.GetQuantity();
		m_stream << "," << colony.Wadl()->GetQuantity();
		m_stream << "," << colony.Foragers()->GetQuantity();
		m_stream << "," << colony.GetColonySize();
		m_stream << "," << colony.queen.GetDayOne();
		m_stream << "," << colony.queen.GetDD();
		m_stream << "," << colony.queen.GetL();
		m_stream << "," << colony.queen.GetN();
		m_stream << "," << colony.queen.GetP();
		m_stream << "," << colony.queen.Getdd();
		m_stream << "," << colony.queen.Getl();
		m_stream << "," << colony.queen.Getn();
		m_stream << std::endl;
	}
}

void TestOutputFormatter::RecordWindow(const COleDateTime& from, const COleDateTime& to)
{
	m_windowed = true;
	m_from = from;
	m_to = to;
}

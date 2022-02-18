//
//  testoutputformatter.h
//  VarroaPopTests
//
//  Created by Julien Pireaud on 4/28/21.
//

#pragma once
#ifndef testoutputformatter_h
#define testoutputformatter_h

#include "customoutputformatter.h"

#include <sstream>
#include <string>
#include <vector>

struct DataItem
{
	std::string date;
	float       queenStrength;
	int         eggs;
	int         larvae;
	int         broods;
	int         adults;
	int         foragers;
	int         colonySize;
};
std::vector<DataItem> GetItemsFromFile(const std::string& filepath);

/**
 * Output formatter that will only output the colony size
 */
class TestOutputFormatter : public CustomOutputFormatter
{
	bool         m_windowed = false;
	COleDateTime m_from;
	COleDateTime m_to;

public:
	TestOutputFormatter(CVarroaPopSession& session);

	virtual ~TestOutputFormatter();

	virtual void Init(CColony& colony);

	virtual void Record(CColony& colony, CEvent& event);

	// only results data between the provided dates will be saved in the data stream
	void RecordWindow(const COleDateTime& from, const COleDateTime& to);
};

#endif /* testoutputformatter_h */

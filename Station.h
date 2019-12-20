#pragma once

#include <vector>
#include <string>
#include "Line.h"

using namespace std;

 class Station {
public:
	string StationName;//站点名称
	vector<string> BelongTo ;//地铁线的名称
	vector<int> IndexOfLine;//对应的地铁线上的站序号
	bool Visited;//是否已被访问
	Station();
	Station(string name);
	Station& operator=(Station& p);
	
};

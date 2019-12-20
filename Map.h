#pragma once

#include <vector>
#include <string>
#include <map>
#include "Line.h"
#include "Path.h"



class Map
{
public:
	//所有的站点
	map<string, Station> Stations;
	//所有的地铁线
	map<string, Line<Station>> Lines;

	Map(vector<string> lineString);
	Map();

};

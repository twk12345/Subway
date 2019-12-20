#pragma once

#include "Station.h"
#include <tuple>
#include <map>


using namespace std;

template<class T> class Line 
{
public:
	string LineName;
	vector<T> Stations;
};

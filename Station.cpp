#include "Station.h"

Station::Station(string name)
{
	StationName = name;
	Visited = false;
}

Station::Station()
{
	Visited = false;
}

Station& Station::operator=(Station& p) {
	if (this != &p)
	{
		this->BelongTo.clear();
		for (int i = 0;i < (int)p.BelongTo.size();i++)
		{
			this->BelongTo.push_back(p.BelongTo[i]);
			this->IndexOfLine.push_back(p.IndexOfLine[i]);
		}
		this->Visited = p.Visited;
		this->StationName = p.StationName;
	}
	return *this;
}

#include "Map.h"

#define  _CRT_SECURE_NO_WARNINGS

vector<string> split(const string& str, const string& delim) {
	vector<string> res;
	char* buf;
	if ("" == str) return res;
	//先将要切割的字符串从string类型转换为char*类型  
	char* strs = new char[str.length() + 1];
	//strcpy(strs, str.c_str());
	strcpy_s(strs, str.length() + 1, str.c_str());

	char* d = new char[delim.length() + 1];
	//strcpy(d, delim.c_str());
	strcpy_s(d, delim.length() + 1, delim.c_str());
	/*char* p = strtok(strs, d);*/
	char* p = strtok_s(strs, d,&buf);
	while (p) {
		string s = p; //分割得到的字符串转换为string类型  
		res.push_back(s); //存入结果数组  
		//p = strtok(NULL, d);
		p = strtok_s(NULL, d, &buf);
	}

	return res;
}

Map::Map()
{
}

Map::Map(vector<string> lineString)
{
	for (int i = 0;i < (int)lineString.size();i++)
	{
		vector<string> params = split(lineString[i], ",");
		Line<Station> l;
		l.LineName = params[0];
		
		for (int j = 1;j < (int)params.size();j++)
		{
			string name = params[j];
			if (this->Stations.count(name) > 0)
			{
				Station& station = this->Stations[name];
				

				for (int k = 0;k < (int)station.BelongTo.size();k++)
				{
					Station& s = Lines[station.BelongTo[k]].Stations[station.IndexOfLine[k]];
					if(!Lines[station.BelongTo[k]].LineName._Equal(params[0]))
					{
						s.BelongTo.push_back(l.LineName);
						s.IndexOfLine.push_back(j - 1);
					}
					
				}
				this->Stations[name].BelongTo.push_back(l.LineName);
				this->Stations[name].IndexOfLine.push_back(j - 1);

				l.Stations.push_back(station);
			}
			else
			{
				Station station(name);
				station.BelongTo.push_back(l.LineName);
				station.IndexOfLine.push_back(j-1);
				this->Stations[name] = station;
				l.Stations.push_back(station);
			}
		}
		Lines[l.LineName] = l;
	}
}

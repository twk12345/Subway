// subway.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <tuple>
#include <map>
#include "Station.h"
#include "Line.h"
#include "Path.h"
#include "Map.h"
#include "FileOperator.h"

Line<Station> line;
list<Path> routine;
Map metroMap;

//输出地铁线路的所有站点
Line<Station> outputLine(char* lineName)
{
	if ( metroMap.Lines.size() == 0) return line;
	return metroMap.Lines[lineName];
}

vector<vector<Path>> addTransformPath(const vector<Path> currentPath, Station transfromStation, const Line<Station> currentLine)
{
	vector<vector<Path>> pathss;
	for (int i = 0;i < (int)transfromStation.BelongTo.size();i++)
	{
		if (!transfromStation.BelongTo[i]._Equal(currentLine.LineName))
		{
			Line<Station>& newLine = metroMap.Lines[transfromStation.BelongTo[i]];
			int startPos = transfromStation.IndexOfLine[i];
			int prePos = startPos - 1;
			int nextPos = startPos + 1;

			if (prePos >= 0)
			{
				if(!metroMap.Stations[newLine.Stations[prePos].StationName].Visited)
				{
					vector<Path> localPaths;
					localPaths.assign(currentPath.begin(), currentPath.end());
					Path path(startPos, prePos, prePos - 1, newLine);
					localPaths.push_back(path);
					pathss.push_back(localPaths);
				}
				
			}
			if (nextPos < (int)newLine.Stations.size())
			{
				if (!metroMap.Stations[newLine.Stations[nextPos].StationName].Visited)
				{
					vector<Path> localPaths;
					localPaths.assign(currentPath.begin(), currentPath.end());
					Path path(startPos, nextPos, nextPos + 1, newLine);
					localPaths.push_back(path);
					pathss.push_back(localPaths);
				}
			}
		}
	}
	return pathss;
}




bool searchPathInLine(char* endStation, vector<vector<Path>>& pathss, vector<vector<Path>>& resultPaths)
{
	bool flag = false;
	int len = pathss.size();
	vector<vector<Path>> newPathss;
	for (int x=0;x< len;x++)
	{
		vector<Path>& paths = pathss[x];
		Path& path = paths[paths.size()-1];
		//当前路径的终点是否为换乘站，是的话，加上其他的线路
		vector<vector<Path>> tempPathss = addTransformPath( paths, path.PathLine.Stations[path.End], path.PathLine);
		if (tempPathss.size() > 0)
			newPathss.insert(newPathss.begin(), tempPathss.begin(), tempPathss.end());
	}
	
	vector<bool>  toDelete(len);
	for (int i = 0;i < (int)pathss.size();i++)
	{
		vector<Path>& paths = pathss[i];
		//当前线路的，最后路径上移动一步，可能情况：

		Path& path = paths[paths.size() - 1];

		//如果当前路径已经到达终点，这标记为已经搜索到最短路径
		if (path.PathLine.Stations[path.End].StationName._Equal(endStation))
		{
			flag = true;
			vector<Path> result;
			result.assign(paths.begin(), paths.end());
			resultPaths.push_back(result);
			continue;
		}

		//1.没有下一点了或者下一点已经被访问了,删掉这条线路
		
		if (path.Next<0 || path.Next > (int)path.PathLine.Stations.size() || metroMap.Stations[path.PathLine.Stations[path.Next].StationName].Visited)
		{
			toDelete[i] = true;
		}
		else
		{//2.还有下一点,移动路径到下一个站
			metroMap.Stations[path.PathLine.Stations[path.End].StationName].Visited = true;
			path.End = path.Next;
			path.Next = (path.End < path.Start) ? path.End - 1 : path.End + 1;
		}
	}
	//删除标记为需要删除的路线
	for (int j = len - 1;j >= 0;j--)
	{
		if (toDelete[j])
		{
			vector<vector<Path>> ::iterator  b = pathss.begin();
			pathss.erase(b + j, b + j + 1);
		}

	}
	while (!flag)
	{
		pathss.insert(pathss.end(), newPathss.begin(), newPathss.end());
		flag = searchPathInLine(endStation, pathss, resultPaths);
	}
	return true;
}

//搜索起点到终点的最短路径,默认开始站和终点站不能相同
vector<vector<Path>> searchPath(char* startStation, char* endStation)
{
	vector<vector<Path>> resultPaths;
	vector<vector<Path>> tempPaths;
	if (metroMap.Stations.size() == 0) return resultPaths;
	if (metroMap.Stations.count(startStation) == 0) return resultPaths;
	Station station = metroMap.Stations[startStation];
	
	Line<Station>& line = metroMap.Lines[station.BelongTo.at(0)];

	metroMap.Stations[line.Stations[station.IndexOfLine.at(0)].StationName].Visited = true;
	int startPos = station.IndexOfLine[0];
	int prePos = startPos - 1;
	int nextPos = startPos + 1;

	if (prePos >= 0)
	{
		vector<Path> paths;
		Path path(startPos, prePos, prePos - 1, line);
		paths.push_back(path);
		tempPaths.push_back(paths);
	}
	if (nextPos < (int)line.Stations.size())
	{
		vector<Path> paths;
		Path path(startPos, nextPos, nextPos + 1, line);
		paths.push_back(path);
		tempPaths.push_back(paths);
	}

	bool result = searchPathInLine(endStation,tempPaths,resultPaths);
	if (!result)
	{
		cout << "没有可达的线路" << endl;
	}

	return resultPaths;
}




int main(int argc, char* argv[])
{
	char* mapPath = nullptr;
	char* lineName = nullptr;
	char* dstPath = nullptr;
	char* startStation = nullptr;
	char* endStation = nullptr;
	FileOperator fo;
	if (argc < 3)
	{
		return 0;
	}
	else
	{
		int i = 1;
		//命令解析模块
		while (i < argc)
		{
			if (strcmp(argv[i], "-map")==0)
			{
				mapPath = argv[i + 1];
				i = i + 2;
			}
			else if (strcmp(argv[i], "-a") == 0)
			{
				lineName = argv[i + 1];
				i = i + 2;
			}
			else if (strcmp(argv[i], "-o") == 0)
			{
				dstPath = argv[i + 1];
				i = i + 2;
			}
			else if (strcmp(argv[i], "-b") == 0)
			{
				startStation = argv[i + 1];
				endStation = argv[i + 2];
				i = i + 3;
			}
			else
			{
				i++;
			}
		}

		if (mapPath !=nullptr)
		{
			vector<string> lineString = fo.ReadMapFile(mapPath);
			metroMap = Map(lineString);
			//查询线路
			if (lineName != nullptr)
			{
				if(dstPath != nullptr)
				{
					Line<Station> line = outputLine(lineName);
					if (line.LineName.length() > 0)
					{
						bool result = fo.WriteLineToFile(line, dstPath);
						if (!result)
						{
							cout << "写入查询线路的站点到文件失败" << endl;
						}
					}
					else
					{
						cout << "该地铁线不存在" << endl;
					}
				}
				else
				{
					cout << "缺少必要的参数-o" << endl;
				}

			}
			//搜索线路
			else if (startStation != nullptr && endStation != nullptr )
			{
				if (dstPath != nullptr)
				{
					if (metroMap.Stations.count(startStation) == 0)
					{
						cout << "查询的起点站不存在" << endl;
						return -1;
					}
					if (metroMap.Stations.count(endStation) == 0)
					{
						cout << "查询的终点站不存在" << endl;
						return -1;
					}
					vector<vector<Path>> pathss = searchPath(startStation, endStation);
					bool result = fo.WritePathsToFile(pathss, dstPath);
					if (!result)
					{
						cout << "写入搜索到的最短换乘线路到文件失败" << endl;
					}
				}
				else
				{
					cout << "缺少必要的参数-o" << endl;
				}
				
			}
			else
			{
				cout << "缺少必要的参数" << endl;
			}

		}

	}


	return 0;
}

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include "Line.h"
#include "Station.h"
#include "Path.h"

class FileOperator
{
public:
	vector<string> ReadMapFile(string filePath);
	 bool WriteLineToFile(Line<Station> line, string dstPath);
	 bool WritePathsToFile(vector<vector<Path>> pathss, string dstPath);
};

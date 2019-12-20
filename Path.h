#pragma once

#include "Line.h"

class Path
{
public:
	int Start;
	int End;
	int Next;
	Line<Station> PathLine;

	Path(int _start, int _end, int _next, Line<Station> _line);
	
};

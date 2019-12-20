#include "Path.h"

Path::Path(int _start, int _end, int _next, Line<Station> _line){
	Start = _start;
	End = _end;
	Next = _next;
	PathLine = _line;
}

#include "FileOperator.h"

vector<string> FileOperator::ReadMapFile(string filePath) {
	vector<string> lineString;
	if (filePath.length() == 0) return lineString;
	//1.¶ÁÈ¡µØÍ¼ÎÄ¼þ
	ifstream in(filePath);
	string line;
	if (in.is_open())
	{
		while (getline(in, line))
		{
			lineString.push_back(line);
		}
	}
	return lineString;
}

 bool FileOperator::WriteLineToFile(Line<Station> line, string dstPath) {
	 if (dstPath.length() == 0 || line.Stations.size()==0) return false;
	 ofstream f1(dstPath);
	 if (!f1)return false; 
	 f1 << line.LineName<< endl;
	 for (Station station : line.Stations)
	 {
		 f1 << station.StationName << endl;
		 cout << station.StationName << endl;
	 }
		 
	 f1.close();
	 return true;

}
 bool FileOperator::WritePathsToFile(vector<vector<Path>> pathss, string dstPath) {
	 if (dstPath.empty() || pathss.size() == 0) return false;
	 ofstream f1(dstPath);
	 if (!f1)return false;
	 
	 for (vector<Path> paths : pathss)
	 {
		 int pathIndex = 0;
		 for (const auto& path : paths)
		 {
			 f1 << path.PathLine.LineName << endl;
			 cout << path.PathLine.LineName << endl;
			 if (path.End < path.Start)
			 {
				 int startPos = (pathIndex > 0) ? path.Start - 1 : path.Start;
				 for (int i = startPos;i >= path.End; i-- )
				 {

					 f1 << path.PathLine.Stations[i].StationName << endl;
					 cout << path.PathLine.Stations[i].StationName << endl;
				 }
			 }
			 else
			 {
				 int startPos = (pathIndex > 0) ? path.Start + 1 : path.Start;
				 for (int i = startPos;i <= path.End; i++)
				 {

					 f1 << path.PathLine.Stations[i].StationName << endl;
					 cout << path.PathLine.Stations[i].StationName << endl;
				 }
			 }
			 pathIndex++;
		 }
		 f1 << endl;
		 cout << endl;
	 }
		 
	 f1.close();
	 return true;
}

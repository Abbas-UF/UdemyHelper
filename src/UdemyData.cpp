#include "UdemyData.h"
#include <fstream>
#include <sstream>
using namespace std;

void UdemyData::readCSV(string filePath)
{
	ifstream csvFile(filePath);

	if (csvFile.is_open())
	{
		string line;
		getline(csvFile, line);	// Skip first line containing header info.

		while (!csvFile.eof())
		{
			// Get line
			getline(csvFile, line);

			// Parse data
			istringstream parser(line);

			// TODO: Actually parse the data XD
		}
	}
	else
	{
		cout << "> Error: " << filePath << " could not be opened!" << endl;
	}
}

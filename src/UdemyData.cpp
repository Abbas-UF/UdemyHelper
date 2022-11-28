#include "UdemyData.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
using namespace std;

UdemyData::UdemyData(string filePath)
{
	readCSV(filePath);
}

void UdemyData::readCSV(string filePath)
{
	ifstream csvFile(filePath);

	if (csvFile.is_open())
	{
		// Clear previously read data
		if (!udemyMap.empty())
		{
			udemyMap.clear();
		}

		string line;
		getline(csvFile, line);	// Skip first line containing header info.

		while (!csvFile.eof())
		{
			Course temp;

			// Get line
			getline(csvFile, line);

			// Setup parser
			istringstream parser(line);

			getline(parser, line, ',');	// Skip ID
			temp.title = getString(parser);
			temp.rating = getDouble(parser);
			temp.hiRating = getDouble(parser);
			temp.loRating = getDouble(parser);
			temp.numRatings = getInt(parser);
			temp.category = getString(parser);
			temp.subcategory = getString(parser);
			temp.topic = getString(parser);
			temp.instructor = getString(parser);
			temp.language = getString(parser);
			getline(parser, line, ',');
			temp.numPracticeTests = getInt(parser);
			temp.numArticles = getInt(parser);
			temp.numCodingExercises = getInt(parser);
			temp.videoHours = getDouble(parser);
			temp.additionalResources = getInt(parser);
			temp.bestSeller = getBool(parser);
			temp.price = getDouble(parser);

			udemyMap[temp.category].push_back(temp);
		}
	}
	else
	{
		cout << "> Error: " << filePath << " could not be opened!" << endl;
	}
}

bool UdemyData::getCategoriesUtilComparison(wxString a, wxString b) {
	if (a.Cmp(b) >= 0) { return true; } // set to 0 if equal, set to positive if a > b; if equal, return arbitrary true
	return false; // else, b > a, return false
}
wxArrayString UdemyData::getCategories() {
	wxArrayString catArr;
	// iterate through map
	for (auto i : udemyMap) { // go through some pseudo-parsed vector of pairs
		catArr.insert(new wxString(i.first)); // insert new wxStrings
	}
	catArr.Sort(getCategoriesUtilComparison); // sort alphabetically using comparison operator
	return catArr;
}

int UdemyData::getMapSize()
{
	return udemyMap.size();
}

unordered_map<string, vector<Course>>& UdemyData::getMap()
{
	return udemyMap;
}

void UdemyData::printMap()
{
	for (auto i = udemyMap.begin(); i != udemyMap.end(); i++)
	{
		cout << "***===Category: " << i->first << " ===***" << endl;
		int vectorSize = i->second.size();
		// Accessing the second value in the map(set of Course objects)
		for (auto j = 0; j < vectorSize; j++)
		{
			string temp = i->second[j].title;
			cout << "> " << temp << endl;
		}
	}
}

// Private Helpers (Reading CSV)
string UdemyData::getString(istringstream& parser)
{
	string result = "";
	string temp;

	while (parser.peek() == '"')
	{
		getline(parser, temp, '"');	// Discared first quotation mark
		getline(parser, temp, '"');
		result += temp;
	}

	getline(parser, temp, ',');
	result += temp;

	return result;
}

int UdemyData::getInt(istringstream& parser)
{
	string number = getString(parser);

	try
	{
		return stoi(number);
	}
	catch (...)
	{
		cout << "> Error: Could not convert " << number << " to an int!" << endl;
	}

	return -1;
}

double UdemyData::getDouble(istringstream& parser)
{
	string number = getString(parser);

	try
	{
		return stod(number);
	}
	catch (...)
	{
		cout << "> Error: Could not convert " << number << " to a double!" << endl;
	}

	return -1.0;
}

bool UdemyData::getBool(istringstream& parser)
{
	string label = getString(parser);
	
	/* Solution to transform function found at
	https://stackoverflow.com/questions/313970/how-to-convert-an-instance-of-stdstring-to-lower-case
	*/	
	transform(label.begin(), label.end(), label.begin(), 
	[](unsigned char c) {return std::tolower(c);} 
	);

	if (label == "yes" || label == "y")
	{
		return true;
	}
	else
	{
		return false;
	}
}
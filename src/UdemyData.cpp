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

int UdemyData::getMapSize()
{
	return udemyMap.size();
}

unordered_map<string, vector<Course>>& UdemyData::getMap()
{
	return udemyMap;
}

vector<wxString> UdemyData::getWXCategories()
{
	vector<wxString> result;

	for (auto i = udemyMap.begin(); i != udemyMap.end(); i++)
	{
		result.push_back(i->first);
	}

	// STL sort has worst-case time complexity of O(logN)
	sort(result.begin(), result.end());

	return result;
}

vector<Course> UdemyData::getCoursesByRating(vector<string> categories, float rating)
{
	vector<Course> result;

	for (auto i = 0; i < categories.size(); i++)
	{
		auto iterator = udemyMap.find(categories[i]);

		// This check is unnecessary, but here for safety purposes
		if (iterator != udemyMap.end())
		{
			for (auto j = iterator->second.begin(); j != iterator->second.end(); j++)
			{
				if (j->rating >= rating)
				{
					result.push_back(*j);
				}
			}
		}
	}

	return result;
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
	
	// TODO: Delete later
	// INFO: Transform and for loop are similar in performance, but the latter is easier-to-read.
	/*
	// Solution to transform function found at:
	// https://stackoverflow.com/questions/313970/how-to-convert-an-instance-of-stdstring-to-lower-case
	transform(label.begin(), label.end(), label.begin(), 
	[](unsigned char c) {return std::tolower(c);} 
	);
	*/

	for (int i = 0; i < label.size(); i++)
	{
		label[i] = tolower((unsigned char) label[i]);
	}

	if (label == "yes" || label == "y")
	{
		return true;
	}
	else
	{
		return false;
	}
}

// -----------------------------------------------------------------------------------------------------------
//												 SORTING METHODS
// -----------------------------------------------------------------------------------------------------------

// Quick note:
// The way 'sort by' is handled is a bit messy, but it works for now.
// I will try to find a better way later, just wanted to get something working
//	- If there are no bool arguments sent in (see shell/merge function), default is sort by rating

// ---------------------------------------------------
//      Comparison Operators for each 'sort by'
// ---------------------------------------------------
bool UdemyData::greaterCourse(const Course& a, const Course& b, SORT_FILTER type)
{
	if (type == SORT_FILTER::PRICE && a.price != b.price)
	{
		return (a.price > b.price);
	}
	else if (type == SORT_FILTER::RATING && a.rating != b.rating)
	{
		return (a.rating > b.rating);
	}
	else if(type == SORT_FILTER::NUM_RATING && a.numRatings != b.numRatings)
	{
		return (a.numRatings > b.numRatings);
	}
	else
	{
		return a.title > b.title;
	}
}

// ---------------------------------------------------
//      Shell Sort
// ---------------------------------------------------

// The bools track whether an alphabetical, price, or rating 'sort by' is selected
void UdemyData::shellSort(vector<Course>& OV, SORT_FILTER type)
{
	for (int gap = OV.size() / 2; gap > 0; gap /= 2)
	{
		// gap gets progressively smaller
		for (int g_sort = gap; g_sort < OV.size(); g_sort++)
		{
			// for each index not gap-sorted already
			Course T = OV[g_sort]; // temporary course object
			int itr = g_sort;

			// iterate indexes by gap (itr >= gap, itr -= gap) and shift them up until correct OV location is found (OV[itr - gap].second > T.second)
			for (itr = g_sort; itr >= gap && greaterCourse(OV[itr - gap], T, type); itr -= gap)
			{
				OV[itr] = OV[itr - gap]; // keep shifting till found
			}

			OV[itr] = T; // restore temp pair to its position
		}
	}
}


// ---------------------------------------------------
//      Merge Sort
// ---------------------------------------------------
void UdemyData::mergeUtil(vector<Course>& OV, int beg, int mid, int end, SORT_FILTER type)
{
	int first = mid - beg + 1; // set a 'first' index
	int last = end - mid; // set a 'last' index
	vector<Course> VF; // our two temporary vectors. Vector First and Vector Last
	vector<Course> VL; // These will contain indexes [begin -> mid] and [mid+1 -> end]

	for (int i = 0; i < first; i++)
	{ // Populate our temporary vectors with their respective half
		VF.push_back(OV[beg + i]);
	}
	for (int a = 0; a < last; a++)
	{
		VL.push_back(OV[mid + a + 1]);
	}
	int subVF = 0; // Keep track of the indexes we are processing in our first and last subvector, as well as our original object vector
	int subVL = 0;
	int subOV = beg;
	while (subVF < first && subVL < last)
	{
		// until end is reached for each sub vector
		if (greaterCourse(VF[subVF], VL[subVL], type))
		{
			// pick lesser rating (the second of the pair of each vector index)
			OV[subOV] = VL[subVL]; // and swap original vector's index with that subvector index
			subVL++;
		}
		else
		{
			OV[subOV] = VF[subVF];
			subVF++;
		}
		subOV++; // each relevent index is increased at this point
	}
	// These while loops are for any remaining elements after going through first and last subvector (when first != last)
	while (subVF < first)
	{
		OV[subOV] = VF[subVF];
		subOV++;
		subVF++;
	}
	while (subVL < last)
	{
		OV[subOV] = VL[subVL];
		subOV++;
		subVL++;
	}
}

void UdemyData::mergeSort(vector<Course>& OV, int beg, int end, SORT_FILTER type)
{
	if (beg < end) // Base-case for recursive calls
	{
		int mid = beg + (end - beg) / 2; // set middle index
		mergeSort(OV, beg, mid, type); // recursively call our merge function to separate our Object Vector into merge-able parts
		mergeSort(OV, mid + 1, end, type);
		mergeUtil(OV, beg, mid, end, type); // Send our sub-indexes to do magic sorting stuff
	}
}
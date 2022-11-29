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

	sort(result.begin(), result.end());
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
bool UdemyData::greaterAlpha(const Course& a, const Course& b) {
	return (a.title > b.title);
}
bool UdemyData::greaterPrice(const Course& a, const Course& b) {
	if (a.price == b.price) { return greaterAlpha(a, b); }
	return (a.price > b.price);
}
bool UdemyData::greaterRating(const Course& a, const Course& b) {
	if (a.rating == b.rating) { return greaterAlpha(a, b); }
	else return (a.rating > b.rating);
}


// ---------------------------------------------------
//      Shell Sort
// ---------------------------------------------------

// The bools track whether an alphabetical, price, or rating 'sort by' is selected
void UdemyData::shellSort(vector<Course>& OV, int size, bool alpha = false, bool price = false, bool rating = true) {
	for (int gap = size / 2; gap > 0; gap /= 2) { // gap gets progressively smaller
		for (int g_sort = gap; g_sort < size; g_sort++) { // for each index not gap-sorted already
			Course T = OV[g_sort]; // temporary course object
			int itr = g_sort;
			// iterate indexes by gap (itr >= gap, itr -= gap) and shift them up until correct OV location is found (OV[itr - gap].second > T.second)
			if (alpha) {
				for (itr = g_sort; itr >= gap && greaterAlpha(OV[itr - gap], T); itr -= gap) {
					OV[itr] = OV[itr - gap]; // keep shifting till found
				}
			}
			else if (price) {
				for (itr = g_sort; itr >= gap && greaterPrice(OV[itr - gap], T); itr -= gap) {
					OV[itr] = OV[itr - gap]; // keep shifting till found
				}
			}
			else if (rating) {
				for (itr = g_sort; itr >= gap && greaterRating(OV[itr - gap], T); itr -= gap) {
					OV[itr] = OV[itr - gap]; // keep shifting till found
				}
			}
			OV[itr] = T; // restore temp pair to its position
		}
	}
}


// ---------------------------------------------------
//      Merge Sort
// ---------------------------------------------------
void UdemyData::mergeUtil(vector<Course>& OV, int beg, int mid, int end, bool alpha = false, bool price = false, bool rating = true) {
	int first = mid - beg + 1; // set a 'first' index
	int last = end - mid; // set a 'last' index
	vector<Course> VF; // our two temporary vectors. Vector First and Vector Last
	vector<Course> VL; // These will contain indexes [begin -> mid] and [mid+1 -> end]

	for (int i = 0; i < first; i++) { // Populate our temporary vectors with their respective half
		VF.push_back(OV[beg + i]);
	}
	for (int a = 0; a < last; a++) {
		VL.push_back(OV[mid + a + 1]);
	}
	int subVF = 0; // Keep track of the indexes we are processing in our first and last subvector, as well as our original object vector
	int subVL = 0;
	int subOV = beg;
	while (subVF < first && subVL < last) { // until end is reached for each sub vector
		if (alpha) {
			if (greaterAlpha(VF[subVF], VL[subVL])) { // pick lesser rating (the second of the pair of each vector index)
				OV[subOV] = VL[subVL]; // and swap original vector's index with that subvector index
				subVL++;
			}
			else {
				OV[subOV] = VF[subVF];
				subVF++;
			}
		}
		else if (price) {
			if (greaterPrice(VF[subVF], VL[subVL])) {
				OV[subOV] = VL[subVL];
				subVL++;
			}
			else {
				OV[subOV] = VF[subVF];
				subVF++;
			}
		}
		else if (rating) {
			if (greaterRating(VF[subVF], VL[subVL])) {
				OV[subOV] = VL[subVL];
				subVL++;
			}
			else {
				OV[subOV] = VF[subVF];
				subVF++;
			}
		}
		subOV++; // each relevent index is increased at this point
	}
	// These while loops are for any remaining elements after going through first and last subvector (when first != last)
	while (subVF < first) {
		OV[subOV] = VF[subVF];
		subOV++;
		subVF++;
	}
	while (subVL < last) {
		OV[subOV] = VL[subVL];
		subOV++;
		subVL++;
	}
}
void UdemyData::mergeSort(vector<Course>& OV, int beg, int end, bool alpha = false, bool price = false, bool rating = true) {
	if (beg >= end) // Base-case for recursive calls
		return;

	int mid = beg + (end - beg) / 2; // set middle index
	mergeSort(OV, beg, mid, alpha, price, rating); // recursively call our merge function to separate our Object Vector into merge-able parts
	mergeSort(OV, mid + 1, end, alpha, price, rating);
	mergeUtil(OV, beg, mid, end, alpha, price, rating); // Send our sub-indexes to do magic sorting stuff
}

/* --------------------------------------------------------------------------
	Sorting Notes:

	In order to track execution time, I've included a library called 'chrono'.
	To use this, just do:

	auto start = chrono::high_resolution_clock::now();
	SORT();
	auto end = chrono::high_resolution_clock::now();

	between calling the sorts. Then, set:

	auto exec_time = chrono::duration_cast<chrono::microseconds>(shell_end - shell_start);

	and then you can cast it to an int if desired (or wxInt, etc). This'll display milliseconds it takes
	for the sort's execution (usually ~150ms for shell, ~350ms for merge on my machine)

	Methology to track execution time was found here:
	https://www.geeksforgeeks.org/measure-execution-time-function-cpp/
   -------------------------------------------------------------------------- */
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <wx/wx.h>
#include <chrono>
#include <time.h>
#include <stdlib.h>
#include <iomanip>
#include <utility>

using namespace std;

struct Course
{
	string title;

	string topic;
	string category;
	string subcategory;

	int numRatings;
	double rating;
	double loRating;
	double hiRating;

	string instructor;
	string language;

	int numArticles;
	int numPracticeTests;
	int numCodingExercises;

	int additionalResources;
	// Different data type for duration?
	double videoHours;

	bool bestSeller;

	double price;
};

class UdemyData
{
	private:
		unordered_map<string, vector<Course>> udemyMap;

		// Private Helpers (Reading CSV)
		string getString(istringstream& parser);
		double getDouble(istringstream& parser);
		int getInt(istringstream& parser);
		bool getBool(istringstream& parser);

		// Private Helpers (Sorting)
		bool greaterAlpha(const Course& a, const Course& b);
		bool greaterPrice(const Course& a, const Course& b);
		bool greaterRating(const Course& a, const Course& b);

	public:
		// Constructor(s)
		UdemyData() {};
		UdemyData(string filePath);

		// Modifiers
		void readCSV(string filePath);

		// Getters
		unordered_map<string, vector<Course>>& getMap();
		vector<wxString> getWXCategories();
		vector<Course> getCoursesByRating(vector<string> categories, float rating);
		int getMapSize();
		
		// Output-ers
		void printMap();

		// Sorts
		void shellSort(vector<Course>& OV, int size, bool alpha = false, bool price = false, bool rating = true);
		void mergeUtil(vector<Course>& OV, int beg, int mid, int end, bool alpha, bool price, bool rating);
		void mergeSort(vector<Course>& OV, int beg, int end, bool alpha, bool price, bool rating);
};


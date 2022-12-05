#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <wx/wx.h>
using namespace std;

enum SORT_FILTER { ALPHA = 0b0000, PRICE = 0b0010, RATING = 0b0100, NUM_RATING = 0b1000};

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
	string strBestSeller;

	double price;
};

class UdemyData
{
	private:
		unordered_map<string, vector<Course>> udemyMap;

		// Private Helpers (Misc)
		string tolower(string input);
		string bestSellerToString(bool bestSeller);

		// Private Helpers (Parsing)
		string getString(istringstream& parser);
		int getInt(istringstream& parser);
		double getDouble(istringstream& parser);
		bool getBool(istringstream& parser);

		// Private Helpers (Sorting)
		bool greaterCourse(const Course& a, const Course& b, SORT_FILTER type);

	public:
		// Constructor(s)
		UdemyData() {};
		UdemyData(string filePath);

		// Modifiers
		void readCSV(string filePath);

		// Getters
		vector<wxString> getWXCategories();
		vector<Course> getCoursesByRating(vector<string> categories, float rating);

		// Sorts
		void shellSort(vector<Course>& OV, SORT_FILTER type);
		void mergeSort(vector<Course>& OV, int beg, int end, SORT_FILTER type);
		void mergeUtil(vector<Course>& OV, int beg, int mid, int end, SORT_FILTER type);
};


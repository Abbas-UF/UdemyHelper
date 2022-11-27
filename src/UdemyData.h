#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

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
		unordered_map<string, vector<Course>> udemyMap; // This is going

		// Private Helpers (Reading CSV)
		string getString(istringstream& parser);
		double getDouble(istringstream& parser);
		int getInt(istringstream& parser);
		bool getBool(istringstream& parser);

	public:
		// Constructor(s)
		UdemyData() {};
		UdemyData(string filePath);

		// Modifiers
		void readCSV(string filePath);

		// Getters
		unordered_map<string, vector<Course>>& getMap();
		int getMapSize();
		
		// Output-ers
		//void printMap();

		void tempPrint();
};


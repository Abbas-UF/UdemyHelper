#pragma once

#include <iostream>
#include <string>
#include <map>
using namespace std;

struct Data
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
	double videoDuration;

	bool bestSeller;

	double price;
	double discountedPrice;
};

class UdemyData
{
	private:
		map<string, Data> udemyData;

	public:
		void readCSV(string filePath);
};


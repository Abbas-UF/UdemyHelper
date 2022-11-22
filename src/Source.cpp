#include "UdemyData.h"
#include <iostream>
using namespace std;


int main()
{
	UdemyData udemyData("Files/Udemy_Clean.csv");

	udemyData.printMap();

	cout << "Total number of courses: " << udemyData.getMapSize() << endl;

	return EXIT_SUCCESS;
}
#include "UdemyData.h"
#include <iostream>
using namespace std;

// Some more comments!!!!
// More comments
int main()
{
	UdemyData udemyData("Files/Udemy_Clean.csv");

	//udemyData.printMap();
	udemyData.tempPrint();

	//cout << "Total number of courses: " << udemyData.getMapSize() << endl;

	return EXIT_SUCCESS;
}
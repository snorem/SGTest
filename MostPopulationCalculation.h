#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <limits> // Used to help ensure proper data input

class PopCalc
{
public:
	PopCalc();
	PopCalc(int startYear, int endYear, std::string fileName); 
	// File is verified here and both arrays are filled out here
	void readFile(std::string fileName); 
	int findMostPopulousYear();
	// If desired, can look into subsets of our original set of data
	int findMostPopulousInSubset(int startYear, int endYear);
	int getPopAtYear(int year);
	void displayYearlyPopulations();

	~PopCalc(); 

private:
	int* birthYearTotals;
	int* endYearTotals;
	int startYear_;
	int endYear_;
	// Iterates through each array, adding the total values fo reach year (Current Year value += Previous Year value)
	void setArrays();
	// Sets the values in each array to 0, since reading in data increments each year noted by 1
	void defaultArrays(); 	
};

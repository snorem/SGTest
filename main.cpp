#include "MostPopulationCalculation.h"

/**********************************************************************************
* Problem: 
* Given a list of people with birth and end years, between 1900-2000,
*	find the year with the most people alive.
*
* Solution:
* Create two arrays (alive and deceased), size will be 101 (0-100).
* Read in data from file, and +1 for the respective year of birth/deceased.
* Do one iteration through each array, adding n-1 to the value of n.
* Do one iteration comparing the values of each array at position n.
*	Track the year (n) in an integer, at the end of the iteration, retun the year.
**********************************************************************************/
using namespace std;
void main ()
{
	PopCalc test(1900, 2000, "TestDataCSV.csv"); // Start year, End year, Data file
	
	test.displayYearlyPopulations();

	int mostPopulousYear = test.findMostPopulousYear();

	cout << endl << "The most populous year found was: " << mostPopulousYear
		<< " with " << test.getPopAtYear(mostPopulousYear) << endl << endl;
}

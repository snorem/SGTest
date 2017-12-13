#include "MostPopulationCalculation.h"

/***********************************************************************
* Default Constructor - Does Nothing
***********************************************************************/
PopCalc::PopCalc(){}

/***********************************************************************
* Constructor - Opens filename given. If file can not be opened, tells
* user the file could not be opened and asks for another file name
***********************************************************************/
PopCalc::PopCalc(int startYear, int endYear, std::string fileName)
{
	birthYearTotals = NULL;
	endYearTotals = NULL;
	// Ensure the start year comes before the end year
	startYear_ = startYear < endYear ? startYear : endYear;
	endYear_ = startYear < endYear ? endYear : startYear;
	// +1 is to be inclusive of all years
	const int totalYears = endYear_ - startYear_ + 1; 
	birthYearTotals = new int[totalYears];
	endYearTotals = new int[totalYears];

	readFile(fileName);
}

/***********************************************************************
* Destructor - To clear up the allocated arrays
***********************************************************************/
PopCalc::~PopCalc()
{
	if(birthYearTotals != NULL)
	{
		delete[] birthYearTotals;
		delete[] endYearTotals;
	}
}

/***********************************************************************
* This function performs all of the file-related functions
* First verify that the file exists. If not, inform the user.
* If file is open, begin reading data.
* After data is read from file, close file and adjust array values
*
* Supported files will be in the following format:
*	start year, end year (new line) (repeat)
***********************************************************************/
void PopCalc::readFile(std::string fileName)
{
	using namespace std;
	defaultArrays();
	int birthYear;
	int endYear;
	string readData;

	ifstream file(fileName.c_str());
	// Inform user if named file could not be found/opened
	if(!file.is_open())
	{
		cout << endl << "There was an issue trying to open the named file.";
	}
	else
	{
		// Read in data from the given file and fill out the two arrays
		while(file.good())
		{
			getline(file, readData, ',');
			birthYear = atoi(readData.c_str());
			getline(file, readData, '\n'); // Our file has new lines after each "end date"
			endYear = atoi(readData.c_str());

			// Only need to bother with people who might be alive in our year range
			if(birthYear <= endYear_)
			{
				if(birthYear >= startYear_)
				{
					birthYearTotals[birthYear - startYear_] += 1;
				}
				// If born before the starting year in our timespan, check to see
				// if life ended before the time span as well. If so, ignore data.
				else if(endYear >= startYear_) 
				{
					birthYearTotals[0] += 1;
				}
				// Only need to worry about incrementing the end year if the person was accounted for
				if((endYear <= endYear_)&& (endYear > startYear_))
				{
					endYearTotals[endYear - startYear_] += 1;
				}
			}	
		}
		file.close(); 

		setArrays();
	}
}

/***********************************************************************
* For ease of use - returns the most populated year 
* within the previously set range of years
***********************************************************************/
int PopCalc::findMostPopulousYear()
{
	return findMostPopulousInSubset(startYear_, endYear_);
}

/***********************************************************************
* Finds the most populous year within a subset of the given data
* Calculated by subtracting the total "ends" from the total "births"
* at each given year and returning the year with the largest difference
*
* If desired, use a negative value to indicate years before year 0
***********************************************************************/
int PopCalc::findMostPopulousInSubset(int startYear, int endYear)
{
	if(startYear > endYear) // Swap the years and check within that range
	{
		startYear = startYear ^ endYear;
		endYear = endYear ^ startYear;
		startYear = startYear ^ endYear;
	}
	if(startYear < startYear_) startYear = startYear_;
	if(endYear > endYear_) endYear = endYear_;

	int mostPop = 0;
	int mostPopYear = 0;
	int start = startYear - startYear_;
	int end = endYear - startYear_;

	for(int i = start; i <= end; i++)
	{
		if(getPopAtYear(startYear_+i) > mostPop) 
		{
			mostPop = getPopAtYear(startYear_+i);
			mostPopYear = i;
		}
	}
	return mostPopYear + startYear_;
}

/***********************************************************************
* Returns the population for a given year.
* The arrays are set up to hold "Total Births" and "Total Ends" for
* each year, so Population is (Births - Ends) 
***********************************************************************/
int PopCalc::getPopAtYear(int year)
{
	year = year-startYear_;
	if(year > endYear_) return 0;

	return birthYearTotals[year] - endYearTotals[year];
}

/***********************************************************************
* Displays a message to the user, followed by all population
* values for each year in range. 
*	Total Population is (Total Births - Total Ends) up to that year
***********************************************************************/
void PopCalc::displayYearlyPopulations()
{
	using namespace std;
	cout << "The following are the total population for years "
		<< startYear_ << " through " << endYear_ << ": " << endl << endl;
	int toggleSpacing = 0;
	for(int i = 0; i <= endYear_-startYear_; i++)
	{
		cout << setw(4) << left << startYear_ + i << " : " 
			<< setw(14) << left << getPopAtYear(startYear_+i);

		if(toggleSpacing == 2) 
		{
			cout << endl;
			toggleSpacing = 0;
		}
		else toggleSpacing += 1;
	}
	cout << endl;
}

/***********************************************************************
* After the arrays are initially filled upon the file being read
* this is used to calculate total living/deceased persons per year
***********************************************************************/
void PopCalc::setArrays()
{
	// Start at 1, since year 0 is the baseline
	for(int i = 1; i <= (endYear_ - startYear_); i++)
	{
		birthYearTotals[i] += birthYearTotals[i-1];
		endYearTotals[i] += endYearTotals[i-1];
	}
}

/***********************************************************************
* Sets all values in array to 0
* Used when initially filling the arrays with data
***********************************************************************/
void PopCalc::defaultArrays()
{
	if(birthYearTotals != NULL)
	{
		for(int i = 0; i < (endYear_ - startYear_); i++)
		{
			birthYearTotals[i] = 0;
			endYearTotals[i] = 0;
		}
	}
}

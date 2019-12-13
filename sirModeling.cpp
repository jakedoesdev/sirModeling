/*
Author:   	 Jacob Everett (jae0204)
Date:	  	 09/11/2018
Class:		 CSCE 1030.001
Professor:	 Mark Thompson
Description: This is a program that uses a 2D char array to model the spread of disease in a population 
*/

#include <iostream>
using namespace std;

//global variable declaration
//updating this variable modifies the size of the arrays throughout the program
const int SIZE = 7;

//FUNCTION DECLARATIONS

//initialize a 2D array of size SIZE to a letter value
void initialize_array(char day[][SIZE], int letterValue);

//print a 2D array of size SIZE
void print_region(char day[][SIZE], int size);

//count the number of infected persons found in a 2D array of size SIZE
int count_infected(char day[][SIZE], int size);

//recover infected persons
void recovery(char day1[][SIZE], char day2[][SIZE], int &dayCounter);

//spread infection to relevant population
void spread_infection(char day1[][SIZE], char day2[][SIZE], int &dayCounter);

//ensure user coordinates are valid
bool is_valid(int x, int y);

int main()
{
	char currDay[SIZE][SIZE];  //current day's SIR grid
	char nextDay[SIZE][SIZE];  //next day's SIR grid
	int xCoord, yCoord;		   //user-entered x,y coordinates for beginning infection
	int dayCounter = 0; 	   //Days since initial infection
	
	cout << "+------------------------------------------------+" << endl;
	cout << "|      Computer Science and Engineering          |" << endl;
	cout << "|       CSCE 1030 - Computer Science I           |" << endl;
	cout << "|   Jacob Everett   jae0204 jae0204@my.unt.edu   |" << endl;
	cout << "+------------------------------------------------+" << endl;
	
	//function call to initialize each location in both arrays to 's' (ascii value = 115)
	initialize_array(currDay, 115);
	initialize_array(nextDay, 115);
	
	//while is_valid (bool function that returns true if numbers are in bound) returns false,
	//continue asking for valid entry. Once valid entry is chosen, output choice
	do
	{		
		cout << "Please enter a location to infect: ";
		cin >> xCoord >> yCoord;

		//print error message
		if (!is_valid(xCoord, yCoord))
		{
			cout << "Error! Those coordinates are not valid." << endl << "Please try again with 2 numbers between 1-7." << endl;
		}
	} while (!is_valid(xCoord, yCoord));
	
	//corrects for 0-based array as shown in sample output
	//i.e. if user selects (1, 1) they are actually selecting (0, 0)
	xCoord -= 1;
	yCoord -= 1;

	//inputs initial infection to location specified by user
	currDay[xCoord][yCoord] = 'i';
	
	//prints day 0 using print function (further calls to print function are made inside recovery function)
	cout << "Day " << dayCounter << endl;
	print_region(currDay, SIZE);
	
	//first call to spread function
	spread_infection(currDay, nextDay, dayCounter);
	
	//corrects for 0-based dayCounter and outputs before program end
	cout << "It took " << dayCounter + 1 << " days for the outbreak to end." << endl;
	
	return 0;
}

//FUNCTION DEFINITIONS

//sets all elements in the currDay array to letterValue
void initialize_array(char day[][SIZE], int letterValue)
{
	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			day[i][j] = letterValue;
		}
	}
	return;
}

//prints all elements in selected array
void print_region(char day[][SIZE], int size)
{
	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			cout << day[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	return;
}

//counts number of infected and returns number
int count_infected(char day[][SIZE], int size)
{
	int counter = 0;
	
	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			
			if (day[i][j] == 'i')
			{
				++counter;
			}		
		}
	}
		return counter;
}

//checks if user number is within bounds and returns boolean
bool is_valid(int x, int y)
{
	return (((x >= 1) && (x <= SIZE)) && ((y >= 1) && (y <= SIZE)));
}

//for every susceptible person found in day1(currDay), spread function will check all possible adjacent locations and infect them in day2(nextDay)
//at the completion of the first full run of inner and outer loops, recovery() is called
void spread_infection(char day1[][SIZE], char day2[][SIZE], int &dayCounter)
{
	//declaring outside loop to allow using i and j to determine when recovery() should be called
	int i;
	int j;
	for (i = 0; i < SIZE; ++i)
	{
		for (j = 0; j < SIZE; ++j)
		{	
			//if current index is susceptible
			if (day1[i][j] == 's')
			{
				//check all adjacent indexes for infection
				//check right of current
				if ((day1[i][j+1] == 'i') && ((j+1) <= (SIZE - 1)))
				{
					day2[i][j] = 'i';
				}
				//check left of current
				else if ((day1[i][j-1] == 'i') && ((j-1) >= 0))
				{		
					day2[i][j] = 'i';
				}
				//check above
				else if ((day1[i-1][j] == 'i') && ((i-1) >= 0))
				{			
					day2[i][j] = 'i';
				}
				//check below
				else if ((day1[i+1][j] == 'i') && ((i+1) <= (SIZE - 1)))
				{				
					day2[i][j] = 'i';
				}
				//check lower right diagonal
				else if ((day1[i+1][j+1] == 'i') && ((i+1) <= (SIZE - 1)) && ((j+1) <= (SIZE - 1)))
				{				
					day2[i][j] = 'i';
				}
				//check upper right diagonal
				else if ((day1[i-1][j+1] == 'i') && ((j+1) <= (SIZE - 1)) && ((i-1) >= 0))
				{	
					day2[i][j] = 'i';
				}
				//check lower left diagonal
				else if ((day1[i+1][j-1] == 'i') && ((i+1) <= (SIZE - 1)) && ((j-1) >= 0))
				{		
					day2[i][j] = 'i';
				}
				//check upper left diagonal
				else if ((day1[i-1][j-1] == 'i') && ((i-1) >= 0) && ((j-1) >= 0))
				{				
					day2[i][j] = 'i';
					
				}
			}
		}
		
		//calls recovery at the end of each full iteration through both loops
		if ((i == (SIZE - 1)) && ((j == SIZE)))
		{
			recovery(day1, day2, dayCounter);
		}
	}	
	return;
}

//this function finds each infection in the current day and updates the next day at that location to recovered
//once all i's in the day2 have been set to r, day2's values are copied to day1
void recovery(char day1[][SIZE], char day2[][SIZE], int &dayCounter)
{

	//Finds all infected persons in day1 and copies them to day2
	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			if (day1[i][j] == 'i')
			{
				day2[i][j] = 'r';
			}
		}
	}
	
	//Finds all recovered persons in day2 and copies them to day1
	//Finds all infected persons in day2 and copies them to day1
	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			if (day2[i][j] == 'r')
			{
				day1[i][j] = 'r';
			}
			else if (day2[i][j] == 'i')
			{
				day1[i][j] = 'i';
			}
		}
	}
	
	//increments the dayCounter and outputs the current day and state of infections
	++dayCounter;
	cout << "Day " << dayCounter << endl;
	print_region(day1, SIZE);
	
	//if infected persons still exist in day2, call spread function again
	if (count_infected(day2, SIZE) > 0)
	{
		spread_infection(day1, day2, dayCounter);
	}
	

	return;
}
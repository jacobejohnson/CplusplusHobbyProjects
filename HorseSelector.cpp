#include <iostream>
#include <iomanip>
#include <ctime>
#include <vector>
#include<bits/stdc++.h>
//Jacob Johnson - jacob.johnson365@gmail.com - 5/1/2018
/*This program takes the opening odds set by the track's handicappers and assigns a proportional integer value to the horse
rounded to the nearest whole number (i.e. 20% chance of winning = 20 value).  Then the total of the horses' collective chance of winning
is added up to determiine the max rand.  If horse 1 has a 20% chance of winning, it will own 1-20 on the RNG results, if horse 2 has a 
15% chance of winning, it will own 21-35 on the RNG results and so on.*/

using namespace std;

double impliedProbability(double, double);//implied probability function prototype
void single (vector<int>&, int);//single race output, passes vector as reference
void multi (vector<int>&, int);//mult race output, passes vector as reference

int main()
{
   	vector<int> horses;
	int numHorses;
	double currentValue;
	
	cout << "Enter number of horses: ";
	cin >> numHorses;
	
	for(int i = 0; i < numHorses; i++)
	{	
		double x;//left integer of fractional odds
   		double y;//right integer of fractional odds
   
   		cout << "Enter values for x/y fractional odds for horse " << i+1 << ": \n";
   		cout << "x: ";
   		cin >> x;
   		cout << "y: ";
   		cin >> y;
   
   		currentValue = impliedProbability(x,y);
   		horses.push_back(currentValue);
	}
	
	int total = 0;
	for(int i = 0; i < horses.size(); i++) 
	{
		total += horses[i];	// Accumulate total
	}
	
	srand(time(NULL));//seed rand with machine time
	string betType; //determines which function to call (single or multi)
	cout << "Single race or multi-race? Enter S or M: ";
	cin >> betType;
	transform(betType.begin(), betType.end(), betType.begin(), ::toupper);
	string answer = "Y";//answer to if user is finished
	while (answer != "N" && answer != "n")
	{
		if (betType == "S")
		{
			single(horses, total);//calls single race output function
		}else if (betType == "M")
		{
			multi(horses, total);//calls the mult-race output function
		}else
		{
		cout << "Incorrect entry, please try again \n";
		break;
		}
		cout << endl << endl;
		cout << "Would you like to run the simulation again? Y or N:";
		cin >> answer;
	}
   	cout << endl;
	cout << "GOOD LUCK!";//exit message
 	
	 return 0;
}

double impliedProbability(double x, double y)
{
	return y/(y+x)*100; //calculates and returns the implied odds of the horse based on morning line fractional odds set by handicappers
}

void single (vector<int>& horses, int total)
{
	int index;
	int iterations;
	int numWinners;

	cout << "How many simulations would you like: ";//get iteratioin requirement from user
	cin >> iterations;
	cout << "How many places do you want to output: ";//essentially allows user to ask for exacta, trifects, superfecta, super hi-5
	cin >> numWinners;

	for (index = 1; index <= iterations; index++)
	{
		cout << endl << endl;
		cout << "Simulation " << index << ":";
		for(int i = 1; i <= numWinners; i++)
		{
			int winner = rand()%total+1;
			double tempTotal = 0;	// Used to hold current sum of horses
			for(int c = 0; c < horses.size(); c++)
			{
				tempTotal += horses[c]; // Same functionality as horse1+horse2+horse3+... from original
				if(winner <= tempTotal) 
				{
					cout << endl;
					cout << "Place " << i << ": Horse " << (c+1) << " - " << winner;
					break;	// Exits current for loop
				}	
			}	
		}
	}
}

void multi (vector<int>& horses, int total)
{
	int index;
	int iterations;
	int numWinners;

	cout << "How many simulations would you like: ";//get iteration requirement from user
	cin >> iterations;
	cout << "How many winners per race do you want to output: ";//essentially allows user to ask for exacta, trifects, superfecta, super hi-5
	cin >> numWinners;

	for (index = 1; index <= iterations; index++)
	{
		cout << endl << endl;
		cout << "Simulation " << index << ":";
		for(int i = 1; i <= numWinners; i++)
		{
			int winner = rand()%total+1;
			double tempTotal = 0;	// Used to hold current sum of horses
			for(int c = 0; c < horses.size(); c++)
			{
				tempTotal += horses[c]; // Same functionality as horse1+horse2+horse3+... from original
				if(winner <= tempTotal) 
				{
					cout << "\nHorse " << (c+1) << " - " << winner;
					break;	// Exits current for loop
				}	
			}	
		}
	}
}

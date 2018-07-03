//Praminda Mahesh Imaduwa-Gamage CS225

#include "stdafx.h"
#include "Horse.h"
#include "time.h"
#include <iostream>

using namespace std;
//constructor
Horse::Horse(string horseName, string riderName)
{
	name = horseName;
	rider = riderName;
	srand((unsigned)time(0));
	maxRunningDistPerSecond = rand() % 100 + 1;
	distanceTraveled = 0.0;
	raceWon = 0;
}

//deconstructor
Horse::~Horse()
{
}

//runAsecond: mutator
void Horse::runASecond() {
	distanceTraveled += maxRunningDistPerSecond;
}
//mutator
void Horse::resetClock() {
	maxRunningDistPerSecond = rand() % 100 + 1;
}
//mutator
void Horse::sendToGate() {
	distanceTraveled = 0.0;
}
//mutator
void Horse::setRaceWon(int race) {
	raceWon = raceWon + race;
}
//accesor
int Horse::getRaceWon() {
	return raceWon;
}
//accesor
string Horse::getName() {
	return name;
}
//accesor
int Horse::getTotalbDistance() {
	return distanceTraveled;
}

//display method
void Horse::displayHorse(int goalLength) {

	double displayScale;
	int scalingFactor = 20;
	
	string frame = "||";
	string mark = "->";
	int markLength = mark.length();
	//scaling the display
	displayScale = scalingFactor * distanceTraveled / goalLength;
	frame.insert(1, scalingFactor + 1, ' ');
	
	int ind;
	if (goalLength > 0) {
		for (ind = 0;  ind < displayScale && ind <= scalingFactor; ind++) {
			
			if (ind == scalingFactor) {
				mark = "-|>";
				markLength = mark.length();
			}
			frame.replace(ind + 1, markLength, mark);			
		}
	}
	else {
		frame.replace(1, 1 , ">");
	}
	cout << frame << "\t" << distanceTraveled << "     " + name + ", ridden by " + rider;
	
}
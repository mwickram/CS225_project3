#pragma once
//Praminda Mahesh Imaduwa-Gamage CS 225
#include <string>
using namespace std;
//the Horse class declaration

#ifndef Horse_H
#define Horse_H

class Horse
{
	//variables declaration
private:
	string name;
	string rider;
	int maxRunningDistPerSecond;
	double distanceTraveled;
	int raceWon;
	//functions, getters, and setters declaration
public:
	string getName();
	void runASecond();
	void sendToGate();
	void displayHorse(int goalLength);
	void setRaceWon(int race);
	int getRaceWon();
	int getTotalbDistance();
	void resetClock();
	Horse(string horseName = "", string riderName = "");
	~Horse();
};


#endif // !Horse_H


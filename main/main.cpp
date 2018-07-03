// main.cpp : Defines the entry point for the console application.
//Praminda Mahesh Imaduwa-Gamage CS225

#include "stdafx.h"
#include "Horse.h"
#include "time.h"
#include <string>
#include <iostream>
#include <cctype>
#include <vector>

using namespace std;
//structure declaration and function prototypes
struct horseInfo {
	string horseName;
	int wins;
};
Horse * raceOnce(int &);
void registerNames(string participant, string &);
int readInt(string request);
int readGolLength();
char readyTogo();
void cleanSpace(string &aString);


int main()
{	
	char goAgain;
	int n_races = 0;
	int n_horses = 0;
	Horse * hptr = nullptr;
	horseInfo * records = nullptr;
	const int SIZE = 100;
	records = new horseInfo[SIZE];
	bool recordExist;
	//initialize win variable in structure horseInfo
	for (int ind = 0; ind < SIZE; ind++) {
		records[ind].wins = 0;
	}

	do {
		n_races++;
		hptr = raceOnce(n_horses); //call for a race, hptr points to records of racing
		recordExist = false;
		//check previous racing		
		for (int ind = 0; ind < n_horses; ind++) {
			//if raced before, update wins
			for (int indNL = 0; indNL < SIZE; indNL++) {
				if (records[indNL].horseName == hptr[ind].getName()) {
					records[indNL].wins += hptr[ind].getRaceWon();
					recordExist = true;
				}
			}
			//new racers log horse names & wins
			if (!recordExist) {
				records[ind].horseName = hptr[ind].getName();
				records[ind].wins += hptr[ind].getRaceWon();
			}
			recordExist = false;
		}
		//printing horse name & wins
		for (int indNL = 0; indNL < SIZE; indNL++) {
			for (int ind = 0; ind < n_horses; ind++) {
				if (records[indNL].horseName == hptr[ind].getName()) {
					cout << records[indNL].horseName << " has won " << records[indNL].wins << "/" << n_races << " races." << endl;
				}
			}
		}
	
		cout << "Do you want to continue (y/n)?: ";
		cin >> goAgain;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			goAgain = 'n';
		}
		else if (tolower(goAgain) != 'y' && tolower(goAgain) != 'n') {
			goAgain = 'n';
		}
		cin.ignore(INT_MAX, '\n');

	} while ((tolower(goAgain) != 'n'));

	hptr = nullptr;
	records = nullptr;
	delete[] hptr;
	delete[] records;
	
	system("pause");
    return 0;
}

void cleanSpace(string &aString) {

	int ind = 0;
	//remove all space at the begining of user entry
	while (!isalpha(aString[ind])) {
		ind++;
	}
	aString.erase(0, ind);

	ind = 0;
	//remove all spaces at the end of user entry
	while (!isalpha(aString[aString.size() - 1 - ind])) {
		ind++;
	}
	aString.erase(aString.size() - ind, ind);
	//remove more than one space between two words in user entry
	ind = 0;
	while (aString[ind] != '\0') {
		if (isspace(aString[ind]) && !isalpha(aString[ind + 1])) {
			aString.erase(ind + 1, 1);
		}
		else {
			ind++;
		}
	}
}


//register horse and rider
void registerNames(string participant, string &racer) {
	

	do {
		cout << "Please give me the name of " + participant + " : ";
		getline(cin, racer);
		
		int countSpace = 0;
		bool isSpace;

		for (int ind = 0; ind < racer.length(); ind++) {
			isSpace = isspace(racer[ind]);
			countSpace += isSpace;
		}

		if (countSpace == racer.length()) {
			racer = "";
		}
		else {
			cleanSpace(racer);
		}

		if (racer.empty()) {
			cout << participant + " must me identified before racing" << endl;
		}

	} while (racer.empty());
}


//function for condcuting one race
Horse * raceOnce(int &number_of_horses) {

	int goalLength;
	bool flag;
	string name, rider, readyOption;

	number_of_horses = readInt("Enter number of horses: ");
	cin.ignore(INT_MAX, '\n');
	Horse * horse = nullptr;
	horse = new Horse[number_of_horses];
	vector <string> nameList;

	for (int ind = 0; ind < number_of_horses; ind++) {

		registerNames("horse " + to_string(ind + 1), name);
		registerNames("rider " + to_string(ind + 1), rider);
		nameList.push_back(name);

		if (ind > 0) {
			for (int indofnameList = 0; indofnameList < nameList.size()-1; indofnameList++) {
				if (nameList[indofnameList] == name) {
					name = name + "-" + to_string(ind);
					nameList[indofnameList] = name;
					cout << "Duplicate entry renamed: " << name << endl;
				}
			}
		}
		horse[ind] = {Horse(name, rider)};//calling the constrcutor
		(horse + ind)->sendToGate();
	}

	goalLength = readGolLength();
	cin.ignore(INT_MAX, '\n');
	cout << endl;

	cout << "The start!" << endl << endl;
	for (int ind = 0; ind < number_of_horses; ind++) {
		horse[ind].displayHorse(0);
		cout << endl;
	}
	cout << endl;
	
	int maxDistance = 0;
	int winner = 0;
	int iterator = 0;
	vector<int> distance(number_of_horses);
	int tie_count = 0;

	while (maxDistance <= goalLength) {
		
		for (int ind = 0; ind < number_of_horses; ind++) {
			(horse + ind)->resetClock();
			(horse + ind)->runASecond();

			if (maxDistance < horse[ind].getTotalbDistance()) {
				maxDistance = horse[ind].getTotalbDistance();// the horse in front
				winner = ind;
				distance[0] = winner;
			}//random winner selection if distance same
			else if (maxDistance == horse[ind].getTotalbDistance()) {
				tie_count++;
				distance[tie_count] = ind;
				srand((unsigned)time(0));
				winner = distance[rand() % tie_count];
			}
		}//end of for
		readyOption = readyTogo();
		cout << endl;
		flag = false;
		if (readyOption == "y") {
			for (int ind = 0; ind < number_of_horses; ind++) {
				horse[ind].displayHorse(goalLength);//show the current display, which is in above for loop
				cout << endl;
			}
		} 
		else {
			flag = true;
			break;
		}
		cout << endl;
		iterator++;
	}//end while
	
	 if (!flag) {
		(horse + winner)->setRaceWon(1);
	 }
	 else {
		 for(int ind = 0; ind < number_of_horses; ind++)
		 (horse + ind)->setRaceWon(0);
	 }
	
	return horse;
}

//read only integers
int readInt(string request) {
	int option = 0;
	do {
		try {
			cout << request;
			cin >> option;
			cout << endl;
			//accept only int
			if (cin.fail()) {
				cout << "Invalid entry" << endl;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				option = 0;
			}
			else if (option < 0) {
				throw string("Must be a positive value");//reject negative
			}
		}
		catch (string exceptionString) {
			cout << exceptionString << endl;
			option = 0;
		}
	} while (option == 0);

	return option;
}
//read the goal length entry by user
int readGolLength() {
	int num;
	do {
		num = readInt("Please enter the distance of the race: ");
		if (num < 100) {
			cout << "Distance should be minimum 100" << endl;
		}
	} while (num < 100);
	return num;
}
//valid user entry
char readyTogo(){
	char goAgain;
	do {
		cout << "Are you ready for the next second(y/n)?: ";
		cin >> goAgain;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			goAgain = '-1';
		}
		cin.ignore(INT_MAX, '\n');

	} while (tolower(goAgain) != 'y' && tolower(goAgain) != 'n');
	
	return goAgain;
}
#include "utils.hpp"
#include <iostream>
#include <ctype.h>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <windows.h>
using namespace std;

//----------------------------------------------------------------------
// Random Functions - IMPLEMENTATION 
//----------------------------------------------------------------------
size_t randomNumber(const size_t& min, const size_t& max) {
	return (rand() % (max - min + 1)) + min;
}

//----------------------------------------------------------------------
// Convertion Functions - IMPLEMENTATION 
//----------------------------------------------------------------------

Position strToPosition(const string& str) {
	Position position;
	position.row = str.at(0) - 65;
	position.column = str.at(1) - 97;
	return position;
}

//----------------------------------------------------------------------
// Input Functions - IMPLEMENTATION 
//----------------------------------------------------------------------

Position readPosition() {
	// Input variable
	string input;
	// User Input Loop
	bool isValid = false;
	do {
		getline(cin, input);
		if (input.length() == 2 && isupper(input.at(0)) && islower(input.at(1)))
			isValid = true;
		else
			cout << "Invalid Syntax!" << endl;
	} while (!isValid);
	return strToPosition(input);
}

char readTile() {
	// Input variable
	char input;
	// User Input Loop
	bool isValid = false;
	do {
		cin >> input;
		if (!cin.fail() && cin.peek() == '\n' && isalpha(input))
			isValid = true;
		else {
			cin.clear();
			cout << "Invalid Syntax!" << endl;
		}
		cin.ignore(100, '\n');
	} while (!isValid);
	return input;
}

int readInteger() {
	int input;
	// User Input Loop
	bool isValid = false;
	do {
		cin >> input;
		if (!cin.fail() && cin.peek() == '\n')
			isValid = true;
		else {
			cin.clear();
			cout << "Valid input, please enter an integer!" << endl;
		}
		cin.ignore(100, '\n');
	} while (!isValid);
	return input;
}

//----------------------------------------------------------------------
// Output Functions - IMPLEMENTATION 
//----------------------------------------------------------------------

void setColor(const unsigned int& color, const unsigned int& background_color) {
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	if (background_color == BLACK)
		SetConsoleTextAttribute(hCon, color);
	else
		SetConsoleTextAttribute(hCon, color | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
}

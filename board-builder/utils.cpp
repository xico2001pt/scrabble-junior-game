#include "utils.hpp"
#include <iostream>
#include <ctype.h>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <windows.h>
using namespace std;

//----------------------------------------------------------------------
// Convertion Functions - IMPLEMENTATION 
//----------------------------------------------------------------------

Position strToPosition(const string& str) {
	Position position;
	position.row = str.at(0) - 65;
	position.column = str.at(1) - 97;
	return position;
}

string positionToStr(const Position& position) {
	string str = "";
	char row = position.row + 65;
	char column = position.column + 97;
	str += toupper(row);
	str += column;
	return str;
}

string upperWord(string str) {
	transform(str.begin(), str.end(), str.begin(), ::toupper);
	return str;
}

string lowerWord(string str) {
	transform(str.begin(), str.end(), str.begin(), ::tolower);
	return str;
}

//----------------------------------------------------------------------
// Input Functions - IMPLEMENTATION 
//----------------------------------------------------------------------

bool readInstruction(Instruction& instruction) {
	string instructionString;
	// Input variables
	string initialPosition;
	char orientation;
	string word;
	// Get user input
	bool isValid = false;
	do {
		stringstream ss;
		getline(cin, instructionString);
		ss << instructionString;
		ss >> initialPosition >> orientation >> word;
		if (cin.fail() && cin.eof()) {
			cin.clear();
			return false;
		}
		else if (isupper(initialPosition[0]) && islower(initialPosition[1]) && (orientation == 'H' || orientation == 'V') && word != "")
			isValid = true;
		else
			cerr << "Invalid Syntax!" << endl;
	} while (!isValid);
	// Store user input
	instruction.initialPosition = strToPosition(initialPosition);
	instruction.orientation = orientation;
	instruction.word = upperWord(word);
	return true;
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

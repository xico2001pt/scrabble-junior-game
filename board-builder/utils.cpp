#include "utils.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <windows.h>
using namespace std;

//----------------------------------------------------------------------
// Convertion Functions - DECLARATION 
//----------------------------------------------------------------------

Position strToPosition(string str) {
	Position position;
	position.row = str.at(0) - 65;
	position.column = str.at(1) - 97;
	return position;
}

string positionToStr(Position position) {
	string str = "";
	char row = position.row + 65;
	char column = position.column + 97;
	str += toupper(row);
	str += column;
	return str;
}

string upperWord(string str) {
	transform(str.begin(), str.end(), str.begin(), toupper);
	return str;
}

string lowerWord(string str) {
	transform(str.begin(), str.end(), str.begin(), tolower);
	return str;
}

//----------------------------------------------------------------------
// Input Functions - DECLARATION
//----------------------------------------------------------------------

Instruction readInstruction() {
	stringstream ss;
	string instructionString;
	Instruction instruction;
	// Input variables
	string initialPosition;
	char orientation;
	string word;
	// Get user input
	getline(cin, instructionString);
	ss << instructionString;
	ss >> initialPosition >> orientation >> word;
	// Store user input
	instruction.initialPosition = strToPosition(initialPosition);
	instruction.orientation = orientation;
	instruction.word = word;
	return instruction;
}

//----------------------------------------------------------------------
// Output Functions - DECLARATION 
//----------------------------------------------------------------------

void setColor(unsigned int color, unsigned int background_color) {
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	if (background_color == BLACK)
		SetConsoleTextAttribute(hCon, color);
	else
		SetConsoleTextAttribute(hCon, color | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
}
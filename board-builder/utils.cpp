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
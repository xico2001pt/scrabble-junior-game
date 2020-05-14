#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>
using namespace std;

//----------------------------------------------------------------------
// COLOR CODES
//----------------------------------------------------------------------
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGRAY 7
#define DARKGRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15

//----------------------------------------------------------------------
// STRUCT Position 
//----------------------------------------------------------------------
typedef struct {
	char row;
	char column;
} Position;

//----------------------------------------------------------------------
// STRUCT Instruction 
//----------------------------------------------------------------------
typedef struct {
	Position initialPosition;
	char orientation;
	string word;
} Instruction;

//----------------------------------------------------------------------
// Search Functions - DEFINITION & IMPLEMENTATION 
//----------------------------------------------------------------------
template <typename identifier>
bool isInVector(const identifier& elem, const vector<identifier>& v) {
	for (identifier value : v)
		if (elem == value)
			return true;
	return false;
}

//----------------------------------------------------------------------
// Random Functions - DEFINITION 
//----------------------------------------------------------------------

/**
Gets a random number between the given limits (inclusive)
@param min: lower limit
@param max: upper limit
@return: random non-negative integer between the given limits
*/
size_t randomNumber(const size_t& min, const size_t& max);

//----------------------------------------------------------------------
// Convertion Functions - DEFINITION 
//----------------------------------------------------------------------

/**
Transforms a string position into a struct Position
@param position: string which will be transformed into a struct
@return: struct Position
*/
Position strToPosition(const string& position);

//----------------------------------------------------------------------
// Input Functions - DEFINITION 
//----------------------------------------------------------------------

/**
Reads the user input
return: struct holding the chosen position
*/
Position readPosition();

/**
Reads the user input
return: character holding the chosen tile
*/
char readTile();

/**
Reads an integer
return: integer chosen by the user
*/
int readInteger();
//----------------------------------------------------------------------
// Output Functions - DEFINITION 
//----------------------------------------------------------------------

/**
Set text and background color
@param color: text color code
@param background_color: background color code
@return: (none)
*/
void setColor(const unsigned int& color, const unsigned int& background_color);
#endif

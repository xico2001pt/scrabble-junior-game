#ifndef UTILS_H
#define UTILS_H

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
// Search Functions - DEFINITION & DECLARATION 
//----------------------------------------------------------------------
template <typename identifier>
bool isInVector(identifier elem, vector<identifier> v) {
	for (identifier value : v)
		if (elem == value)
			return true;
	return false;
}

//----------------------------------------------------------------------
// Random Functions - DEFINITION 
//----------------------------------------------------------------------
size_t randomNumber(const size_t min, const size_t max);

//----------------------------------------------------------------------
// Convertion Functions - DEFINITION 
//----------------------------------------------------------------------

/**
Transforms a string position into a struct Position
@param position: string which will be transformed into a struct
@return: struct Position
*/
Position strToPosition(const string position);

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
//----------------------------------------------------------------------
// Output Functions - DEFINITION 
//----------------------------------------------------------------------

/**
Set text and background color
@param color: text color code
@param background_color: background color code
@return: (none)
*/
void setColor(unsigned int color, unsigned int background_color);
#endif

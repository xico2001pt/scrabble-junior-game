#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
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
// Convertion Functions - DEFINITION 
//----------------------------------------------------------------------

/**
Transforms a string position into a struct Position
@param position: string which will be transformed into a struct
@return: struct Position
*/
Position strToPosition(const string& position);

/**
Transforms a struct position into a string
@param position: struct which will be transformed into a string
@return: string
*/
string positionToStr(const Position& position);

/**
Transforms all letters of a string into uppercase
@param str: string which letters will be uppercase
@return: uppercase string
*/
string upperWord(string str);

/**
Transforms all letters of a string into lowercase
@param str: string which letters will be lowercase
@return: lowercase string
*/
string lowerWord(string str);

//----------------------------------------------------------------------
// Input Functions - DEFINITION 
//----------------------------------------------------------------------

/**
Saves the user input in the given parameter unless CTRZ^Z is activated
@param instruction: struct that will hold the user input
return: boolean indicating if the instruction was changed
*/
bool readInstruction(Instruction& instruction);

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

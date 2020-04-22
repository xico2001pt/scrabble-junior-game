#include "Board.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

//----------------------------------------------------------------------
// CLASS Board - IMPLEMENTATION 
//----------------------------------------------------------------------

/**
Constructor
*/
Board::Board(char rows, char columns) {
	// Initialize size of the board
	this->rows = rows;
	this->columns = columns;
	// Allocate memory to board (2D array)
	board = (char **) malloc(rows * sizeof(char *));
	for (char i = 0; i < rows; i++) {
		board[i] = (char*) malloc(columns * sizeof(char));
		memset(board[i], ' ', columns); // Fill each row with empty spaces
	}
}

/**
Transforms all letters of a string into uppercase
@param str: string which letters will be uppercase
@return: uppercase string
*/
string Board::upperWord(string str) const {
	transform(str.begin(), str.end(), str.begin(), toupper);
	return str;
}

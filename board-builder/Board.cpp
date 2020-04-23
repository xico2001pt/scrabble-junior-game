#include "utils.h"
#include "Board.h"
#include <iostream>
#include <fstream>
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
	board = (char**)malloc(rows * sizeof(char*));
	for (char i = 0; i < rows; i++) {
		board[i] = (char*)malloc(columns * sizeof(char));
		memset(board[i], ' ', columns); // Fill each row with empty spaces
	}
}

/**
Adds a word in the array board
@param instruction: Contains the information necessary to add a word on the board
@return: (none)
*/
void Board::addWordOnBoard(Instruction instruction) {
	// Store instruction information
	Position initialPosition = instruction.initialPosition;
	char orientation = instruction.orientation;
	string word = instruction.word;
	// Write word on board
	for (unsigned char i = 0; i < word.length(); i++) {
		if (orientation == 'H')
			board[initialPosition.row][initialPosition.column + i] = word.at(i);
		else
			board[initialPosition.row + i][initialPosition.column] = word.at(i);
	}
}

/**
Display the board in the specified output stream
@param fout: output stream where the board will be displayed
@return: (none)
*/
void Board::displayBoard(ostream& fout) const {
	// Print first row
	fout << ' ';
	for (char i = 0; i < columns; i++)
		fout << ' ' << (char)(97 + i);
	fout << endl;
	// Print remaining rows
	for (char i = 0; i < rows; i++) {
		fout << (char)(65 + i);
		for (char j = 0; j < columns; j++) {
			fout << ' ';
			setColor(BLACK, BROWN); // Change text and background color
			fout << board[i][j];
		}
		setColor(LIGHTGRAY, BLACK); // Reset text and background color
		fout << endl;
	}
}

/**
--
@param --: --
@return: --
*/
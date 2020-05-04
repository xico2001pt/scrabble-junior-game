#include "utils.h"
#include "Board.h"
#include <iostream>
#include <ctype.h>
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
Board::Board(string filename) : filename(filename) {
}

/**
Destructor
*/
Board::~Board() {
	// Free memory in board and orientations board (2D arrays)
	for (char i = 0; i < rows; i++) {
		free(board[i]);
		free(orientationsBoard[i]);
	}
	free(board);
	free(orientationsBoard);
}

/**
--
@param --: --
@return: --
*/
bool Board::checkValidPosition(Position position) const {
	char orientation = orientationsBoard[position.row][position.column];
	char columnCopy = position.column; // Copy to undo changes in case of intersection
	// Horizontal search
	if (orientation == 'H' || orientation == 'I') {
		position.column += -1;
		while (position.column < 0 || !isupper(orientationsBoard[position.row][position.column])) {
			if (position.column < 0 || orientationsBoard[position.row][position.column] == ' ')
				return true;
			position.column += -1;
		}
	}
	position.column = columnCopy;
	// Vertical search
	if (orientation == 'V' || orientation == 'I') {
		position.row += -1;
		while (position.row < 0 || !isupper(orientationsBoard[position.row][position.column])) {
			if (position.row < 0 || orientationsBoard[position.row][position.column] == ' ')
				return true;
			position.row += -1;
		}
	}
	return false;
}

/**
--
@param --: --
@return: --
*/
bool Board::checkPossiblePlaytrough(Player player) const {
	// Iterate through all elements
	for (char i = 0; i < rows; i++)
		for (char j = 0; j < columns; j++)
			if (isupper(orientationsBoard[i][j]) && player.checkHasTile(board[i][j]))
				if (checkValidPosition({ i,j }))
					return true;
	return false;
}

/**
--
@param --: --
@return: --
*/
bool Board::checkCompleteWord(Position position) const {
	char orientation = orientationsBoard[position.row][position.column];
	char columnCopy = position.column; // Copy to undo changes in case of intersection
	/*// Horizontal search
	if (orientation == 'H') {
		position.column += 1;
		while (!isupper(orientationsBoard[position.row][position.column])) {
			if (position.column > columns || orientationsBoard[position.row][position.column] == ' ')
				return true;
			position.column += -1;
		}
	}
	// Vertical search
	*/
	return false;
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
			if (islower(orientationsBoard[i][j])) // Check if has been played
				setColor(LIGHTRED, BLACK);
			else
				setColor(BLACK, BROWN); // Change text and background color
			fout << board[i][j];
		}
		setColor(LIGHTGRAY, BLACK); // Reset text and background color
		fout << endl;
	}
}

/**
Adds a word in the array board
@param instruction: contains the information necessary to add a word on the board
@return: (none)
*/
void Board::addWordOnBoard(Instruction instruction) {
	// Store instruction information
	Position initialPosition = instruction.initialPosition;
	char orientation = instruction.orientation;
	string word = instruction.word;
	// Temporary pointer holder
	char* value;
	// Write word on board
	if (orientation == 'H') {
		for (unsigned char i = 0; i < word.length(); i++) {
			board[initialPosition.row][initialPosition.column + i] = word.at(i);
			value = &(orientationsBoard[initialPosition.row][initialPosition.column + i]);
			if (*value == 'V')
				*value = 'I'; // Intersection
			else
				*value = 'H';
		}
	}
	else {
		for (unsigned char i = 0; i < word.length(); i++) {
			board[initialPosition.row + i][initialPosition.column] = word.at(i);
			value = &(orientationsBoard[initialPosition.row + i][initialPosition.column]);
			if (*value == 'H')
				*value = 'I'; // Intersection
			else
				*value = 'V';
		}
	}
}

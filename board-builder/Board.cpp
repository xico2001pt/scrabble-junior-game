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
Destructor
*/
Board::~Board() {
	for (char i = 0; i < rows; i++)
		free(board[i]);
	free(board);
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
	// Write word on board
	unsigned char i;
	if (orientation == 'H') {
		if (initialPosition.column - 1 >= 0)
			board[initialPosition.row][initialPosition.column - 1] = -1; // Forbidden spot
		for (i = 0; i < word.length(); i++)
			board[initialPosition.row][initialPosition.column + i] = word.at(i);
		if (initialPosition.column + i <= 20)
			board[initialPosition.row][initialPosition.column + i] = -1; // Forbidden spot
	}
	else {
		if (initialPosition.row - 1 >= 0)
			board[initialPosition.row - 1][initialPosition.column] = -1;
		for (i = 0; i < word.length(); i++)
			board[initialPosition.row + i][initialPosition.column] = word.at(i);
		if (initialPosition.row + i <= 20)
			board[initialPosition.row + i][initialPosition.column] = -1;
	}
	// Store in instructions vector
	instructions.push_back(instruction);
}

/**
Check if the given word appears in the words dictionary
@param word: word that will be searched
@return: boolean indicating if the word appears
*/
bool Board::checkWordInDict(string word) const {
	// Lowercase word
	word = lowerWord(word);
	// Open dictionary file
	ifstream dict(DICTIONARY_FILE);
	// Search loop
	string dictWord;
	while (getline(dict, dictWord))
		if (word == dictWord)
			return true;
	return false;
}

/**
Check if position has already been occupied
@param position: struct which will be searched
@return: boolean indicating if position has already been occupied
*/
bool Board::checkPositionInVector(Position position) const {
	for (char i = 0; i < instructions.size(); i++) {
		if ((position.row == instructions[i].initialPosition.row) && (position.column == instructions[i].initialPosition.column))
			return true;
		return false;
	}
}

/**
Check if the instruction is valid based in the adjacent positions 
@param instruction: instruction which will be checked
@param orientations: board containing the orientations of the words (H, V and -)
@return: boolean indicating if the instruction is valid
*/
bool Board::checkAdjacentPositions(Instruction instruction, Board orientations) const {
	// Store instruction information
	Position initialPosition = instruction.initialPosition;
	char orientation = instruction.orientation;
	string word = instruction.word;
	// Store orientations board information
	char** board = orientations.board;
	// Check surrounding orientations
	if (orientation == 'H')
		for (char i = 0; i < word.length(); i++) {
			if (initialPosition.row - 1 >= 0 && (board[initialPosition.row - 1][initialPosition.column] == 'H' || board[initialPosition.row - 1][initialPosition.column] == '-'))
				return false;
			else if (initialPosition.row + 1 <= rows && (board[initialPosition.row + 1][initialPosition.column] == 'H' || board[initialPosition.row + 1][initialPosition.column] == '-'))
				return false;
		}
	else
		for (char i = 0; i < word.length(); i++) {
			if (initialPosition.column - 1 >= 0 && (board[initialPosition.row][initialPosition.column - 1] == 'V' || board[initialPosition.row][initialPosition.column - 1] == '-'))
				return false;
			else if (initialPosition.column + 1 <= columns && (board[initialPosition.row][initialPosition.column + 1] == 'V' || board[initialPosition.row][initialPosition.column + 1] == '-'))
				return false;
		}
	return true;
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
			if (board[i][j] == -1)
				fout << ' ';
			else
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
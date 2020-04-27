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
Board::Board(char rows, char columns, string filename) {
	// Initialize size and name of the board
	this->rows = rows;
	this->columns = columns;
	this->filename = filename;
	// Allocate memory to board and orientations board (2D arrays)
	board = (char**)malloc(rows * sizeof(char*));
	orientationsBoard = (char**)malloc(rows * sizeof(char*));
	for (char i = 0; i < rows; i++) {
		board[i] = (char*)malloc(columns * sizeof(char));
		orientationsBoard[i] = (char*)malloc(columns * sizeof(char));
		// Fill each row with empty spaces
		memset(board[i], ' ', columns);
		memset(orientationsBoard[i], ' ', columns);
	}
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
	unsigned char i;
	if (orientation == 'H') {
		if (initialPosition.column - 1 >= 0)
			board[initialPosition.row][initialPosition.column - 1] = -1; // Forbidden spot
		for (i = 0; i < word.length(); i++) {
			board[initialPosition.row][initialPosition.column + i] = word.at(i);
			value = &(orientationsBoard[initialPosition.row][initialPosition.column + i]);
			if (*value == 'V')
				*value = 'I'; // Intersection
			else
				*value = 'H';
		}
		if (initialPosition.column + i <= 20)
			board[initialPosition.row][initialPosition.column + i] = -1; // Forbidden spot
	}
	else {
		if (initialPosition.row - 1 >= 0)
			board[initialPosition.row - 1][initialPosition.column] = -1; // Forbidden spot
		for (i = 0; i < word.length(); i++) {
			board[initialPosition.row + i][initialPosition.column] = word.at(i);
			value = &(orientationsBoard[initialPosition.row + i][initialPosition.column]);
			if (*value == 'H')
				*value = 'I'; // Intersection
			else
				*value = 'V';
		}
		if (initialPosition.row + i <= 20)
			board[initialPosition.row + i][initialPosition.column] = -1; // Forbidden spot
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
	for (unsigned char i = 0; i < instructions.size(); i++)
		if ((position.row == instructions.at(i).initialPosition.row) && (position.column == instructions.at(i).initialPosition.column))
			return true;
	return false;
}

/**
Check if the instruction is valid based in the adjacent positions
@param instruction: instruction which will be checked
@return: boolean indicating if the instruction is valid
*/
bool Board::checkAdjacentPositions(Instruction instruction) const {
	// Store instruction information
	Position initialPosition = instruction.initialPosition;
	char orientation = instruction.orientation;
	string word = instruction.word;
	// Check surrounding orientations
	if (orientation == 'H')
		for (unsigned char i = 0; i < word.length(); i++) {
			if (initialPosition.row - 1 >= 0 && (orientationsBoard[initialPosition.row - 1][initialPosition.column] == 'H' || orientationsBoard[initialPosition.row - 1][initialPosition.column] == 'I'))
				return false;
			else if (initialPosition.row + 1 <= rows && (orientationsBoard[initialPosition.row + 1][initialPosition.column] == 'H' || orientationsBoard[initialPosition.row + 1][initialPosition.column] == 'I'))
				return false;
		}
	else
		for (unsigned char i = 0; i < word.length(); i++) {
			if (initialPosition.column - 1 >= 0 && (orientationsBoard[initialPosition.row][initialPosition.column - 1] == 'V' || orientationsBoard[initialPosition.row][initialPosition.column - 1] == 'I'))
				return false;
			else if (initialPosition.column + 1 <= columns && (orientationsBoard[initialPosition.row][initialPosition.column + 1] == 'V' || orientationsBoard[initialPosition.row][initialPosition.column + 1] == 'I'))
				return false;
		}
	return true;
}

/**
Checks if the chosen instruction is within the board limits
@param instruction: struct containing the necessary information to check
@return: boolean indicating if the instruction is within the board limits
*/
bool Board::checkInsideBoard(Instruction instruction) const {
	// Store instruction information
	Position initialPosition = instruction.initialPosition;
	char orientation = instruction.orientation;
	string word = instruction.word;
	// Check if the word fits in the board
	if (orientation == 'H')
		if ((initialPosition.column + word.length()) > columns)
			return false;
	else
		if ((initialPosition.row + word.length()) > rows)
			return false;
	return true;
}

/**
Checks if the word respects other words intersections
@param instruction: instruction which will be checked
@return: boolean indicating if the word respects intersections
*/
bool Board::checkIntersection(Instruction instruction) const {
	// Store instruction information
	Position initialPosition = instruction.initialPosition;
	char orientation = instruction.orientation;
	string word = instruction.word;
	// Check if the word intersects other word or a forbidden spot
	if (orientation == 'H')
		for (unsigned char i = 0; i < word.length(); i++) {
			if (board[initialPosition.row][initialPosition.column + i] != ' ') {
				if (board[initialPosition.row][initialPosition.column + i] == -1)
					return false;
				else if (board[initialPosition.row][initialPosition.column + i] != word.at(i))
					return false;
			}
		}
	else
		for (unsigned char i = 0; i < word.length(); i++)
			if (board[initialPosition.row + i][initialPosition.column] != ' ') {
				if (board[initialPosition.row + i][initialPosition.column] == -1)
					return false;
				else if (board[initialPosition.row + i][initialPosition.column] != word.at(i))
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
Saves the board into a text file
@return: (none)
*/
void Board::saveBoard() const {
	ofstream fout(filename + ".txt"); // Create output stream
	fout << (int)rows << " x " << (int)columns << endl;
	for (char i = 0; i < instructions.size(); i++)
		fout << positionToStr(instructions.at(i).initialPosition) << ' ' << instructions.at(i).orientation << ' ' << instructions.at(i).word << endl;
	displayBoard(fout);
	fout.close();
}

/**
--
@param --: --
@return: --
*/
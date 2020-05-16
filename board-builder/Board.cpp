#include "utils.hpp"
#include "Board.hpp"
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
Board::Board(char rows, char columns, string filename) : rows(rows), columns(columns), filename(filename), numberOfTiles(0) {
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
	// Save the dictionary words
	readDictionary();
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
void Board::addWordOnBoard(const Instruction& instruction) {
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
			else {
				*value = 'H';
				numberOfTiles++; // Increase the total number of tiles
			}
		}
		if (initialPosition.column + i < columns)
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
			else {
				*value = 'V';
				numberOfTiles++; // Increase total number of tiles
			}
		}
		if (initialPosition.row + i < rows)
			board[initialPosition.row + i][initialPosition.column] = -1; // Forbidden spot
	}
	// Store in instructions vector
	instructions.push_back(instruction);
}

/**
Gets the number of tiles on the board
@return: number of tiles
*/
unsigned short Board::getNumberOfTiles() const {
	return numberOfTiles;
}

/**
Check if the given word appears in the words dictionary
@param word: word that will be searched
@return: boolean indicating if the word appears
*/
bool Board::checkWordInDict(const string& word) const {
	return binary_search(dictionary.begin(), dictionary.end(), lowerWord(word));
}

/**
Checks if instruction already exists
@param instruction: struct which will be searched
@return: boolean indicating if the instruction already exists
*/
bool Board::checkInstructionInVector(const Instruction& instruction) const {
	// Store instruction information
	Position initialPosition = instruction.initialPosition;
	char orientation = instruction.orientation;
	string word = instruction.word;
	for (unsigned char i = 0; i < instructions.size(); i++)
		if (orientation == instructions.at(i).orientation) // Check equal orientation
			if (word == instructions.at(i).word) // Check equal word
				if ((initialPosition.row == instructions.at(i).initialPosition.row) && (initialPosition.column == instructions.at(i).initialPosition.column)) // Check equal position
					return true;
	return false;
}

/**
Check if the instruction is valid based in the adjacent positions
@param instruction: instruction which will be checked
@return: boolean indicating if the instruction is valid
*/
bool Board::checkAdjacentPositions(const Instruction& instruction) const {
	// Store instruction information
	Position initialPosition = instruction.initialPosition;
	char orientation = instruction.orientation;
	string word = instruction.word;
	// Check surrounding orientations
	if (orientation == 'H')
		for (unsigned char i = 1; i < word.length() - 1; i++) {
			if (initialPosition.row - 1 >= 0 && (orientationsBoard[initialPosition.row - 1][initialPosition.column + i] == 'H' || orientationsBoard[initialPosition.row - 1][initialPosition.column + i] == 'I'))
				return false;
			else if (initialPosition.row + 1 < rows && (orientationsBoard[initialPosition.row + 1][initialPosition.column + i] == 'H' || orientationsBoard[initialPosition.row + 1][initialPosition.column + i] == 'I'))
				return false;
		}
	else
		for (unsigned char i = 1; i < word.length() - 1; i++) {
			if (initialPosition.column - 1 >= 0 && (orientationsBoard[initialPosition.row + i][initialPosition.column - 1] == 'V' || orientationsBoard[initialPosition.row + i][initialPosition.column - 1] == 'I'))
				return false;
			else if (initialPosition.column + 1 < columns && (orientationsBoard[initialPosition.row + i][initialPosition.column + 1] == 'V' || orientationsBoard[initialPosition.row + i][initialPosition.column + 1] == 'I'))
				return false;
		}
	return true;
}

/**
Checks if the chosen instruction is within the board limits
@param instruction: struct containing the necessary information to check
@return: boolean indicating if the instruction is within the board limits
*/
bool Board::checkInsideBoard(const Instruction& instruction) const {
	// Store instruction information
	Position initialPosition = instruction.initialPosition;
	char orientation = instruction.orientation;
	string word = instruction.word;
	// Check if the word fits in the board
	if (orientation == 'H') {
		if ((initialPosition.column + word.length()) > columns)
			return false;
	}
	else {
		if ((initialPosition.row + word.length()) > rows)
			return false;
	}
	return true;
}

/**
Checks if the word respects other words intersections
@param instruction: instruction which will be checked
@return: boolean indicating if the word respects intersections
*/
bool Board::checkIntersection(const Instruction& instruction) const {
	// Store instruction information
	Position initialPosition = instruction.initialPosition;
	char orientation = instruction.orientation;
	string word = instruction.word;
	// Check if the word intersects other word or a forbidden spot
	unsigned char i;
	if (orientation == 'H') {
		if (initialPosition.column - 1 >= 0)
			if (board[initialPosition.row][initialPosition.column - 1] != ' ' && board[initialPosition.row][initialPosition.column - 1] != -1)
				return false;
		for (i = 0; i < word.length(); i++) {
			if (board[initialPosition.row][initialPosition.column + i] != ' ') {
				if (board[initialPosition.row][initialPosition.column + i] == -1)
					return false;
				else if (board[initialPosition.row][initialPosition.column + i] != word.at(i))
					return false;
			}
		}
		if (initialPosition.column + i < columns)
			if (board[initialPosition.row][initialPosition.column + i] != ' ' && board[initialPosition.row][initialPosition.column + i] != -1)
				return false;
	}
	else {
		if (initialPosition.row - 1 >= 0)
			if (board[initialPosition.row - 1][initialPosition.column] != ' ' && board[initialPosition.row - 1][initialPosition.column] != -1)
				return false;
		for (i = 0; i < word.length(); i++)
			if (board[initialPosition.row + i][initialPosition.column] != ' ') {
				if (board[initialPosition.row + i][initialPosition.column] == -1)
					return false;
				else if (board[initialPosition.row + i][initialPosition.column] != word.at(i))
					return false;
			}
		if (initialPosition.row + i < rows)
			if (board[initialPosition.row + i][initialPosition.column] != ' ' && board[initialPosition.row + i][initialPosition.column] != -1)
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
	for (unsigned char i = 0; i < instructions.size(); i++)
		fout << positionToStr(instructions.at(i).initialPosition) << ' ' << instructions.at(i).orientation << ' ' << instructions.at(i).word << endl;
	fout << endl;
	displayBoard(fout);
	fout.close();
}

/**
Reads the dictionary and adds the words to a vector
@return: (none)
*/
void Board::readDictionary()  {
	// Open dictionary file
	ifstream dict(DICTIONARY_FILE);
	// Loop to get every word
	string dictWord;
	while (getline(dict, dictWord))
		dictionary.push_back(dictWord);
}

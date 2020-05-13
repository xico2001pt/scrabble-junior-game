#include "utils.hpp"
#include "Board.hpp"
#include <iostream>
#include <ctype.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

//----------------------------------------------------------------------
// CLASS Board - IMPLEMENTATION 
//----------------------------------------------------------------------

/**
Constructors
*/
Board::Board(ifstream& fin) {
	// Temporary variables
	stringstream ss;
	string line, position, word;
	Instruction instruction;
	char orientation;
	// Initialize size of the board
	char separator;
	short rows, columns;
	getline(fin, line);
	ss << line;
	ss >> rows >> separator >> columns;
	this->rows = rows;
	this->columns = columns;
	// Allocate memory to board and orientations board (2D arrays)
	this->board = (char**)malloc(rows * sizeof(char*));
	this->orientationsBoard = (char**)malloc(rows * sizeof(char*));
	for (char i = 0; i < this->rows; i++) {
		this->board[i] = (char*)malloc(columns * sizeof(char));
		this->orientationsBoard[i] = (char*)malloc(columns * sizeof(char));
		// Fill each row with empty spaces
		memset(this->board[i], ' ', columns);
		memset(this->orientationsBoard[i], ' ', columns);
	}
	// Read instructions
	char remainingWords = 0;
	while (!fin.eof() && line != "") {
		// Clear stream
		ss.ignore(100, '\n');
		ss.clear();
		// Read instruction
		getline(fin, line);
		ss << line;
		ss >> position >> orientation >> word;
		instruction.initialPosition = strToPosition(position);
		instruction.orientation = orientation;
		instruction.word = word;
		this->addWordOnBoard(instruction); // Draw instruction on board
		remainingWords++;
	}
	fin.close();
	this->remainingWords = remainingWords;
}

Board::Board(const Board& other) {
	// Copy some attributes
	this->rows = other.rows;
	this->columns = other.columns;
	this->remainingWords = other.remainingWords;
	// Allocate memory to the new arrays
	this->board = (char**)malloc(rows * sizeof(char*));
	this->orientationsBoard = (char**)malloc(rows * sizeof(char*));
	for (char i = 0; i < this->rows; i++) {
		this->board[i] = (char*)malloc(columns * sizeof(char));
		this->orientationsBoard[i] = (char*)malloc(columns * sizeof(char));
		memcpy(this->board[i], other.board[i], sizeof(char) * this->columns);
		memcpy(this->orientationsBoard[i], other.orientationsBoard[i], sizeof(char) * this->columns);
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
Set the chosen position into a lowercase letter on the orientations board
@param position: struct that represents the chosen position
@return: (none)
*/
void Board::setPlayedLetter(const Position& position) {
	orientationsBoard[position.row][position.column] = tolower(orientationsBoard[position.row][position.column]);
}

/**
Decrement the given value to the remaining words
@param difference: value which will be subtracted
@return: (none)
*/
void Board::subRemainingWords(char difference) {
	remainingWords -= difference;
}

/**
Get letter at the selected position
@param position: position of the letter
@return: character at the indicated position
*/
char Board::getLetter(const Position& position) const {
	return board[position.row][position.column];
}

/**
Get total number of rows
@return: total number of rows
*/
char Board::getRows() const {
	return rows;
}

/**
Get total number of columns
@return: total number of columns
*/
char Board::getColumns() const {
	return columns;
}

/**
Get pointer to board (2D array)
@return: double pointer to board (2D array)
*/
char** Board::getBoard() const {
	return board;
}

/**
Get number of remaining words
@return: number of remaining words
*/
char Board::getRemainingWords() const {
	return remainingWords;
}

/**
Check if tile has already been played
@param position : chosen position
@return: boolen indicating if that tile has already been played
*/
bool Board::checkHasBeenPlayed(const Position& position) const
{
	char row = position.row;
	char column = position.column;
	return (islower(orientationsBoard[row][column]));
}

/**
Checks if the indicated position is within the board size
@param position: position which will be checked
@return: boolean indicating if the position is within the board size
*/
bool Board::checkInsideBoard(const Position& position) const {
	return (position.row >= 0 && position.row < rows&& position.column >= 0 && position.column < columns);
}

/**
Checks if the previous letters were played
@param position: position in the board that will be checked
@return: boolean indicating if the position is valid to play
*/
bool Board::checkValidPosition(Position position) const {
	// Check empty position
	if (board[position.row][position.column] == ' ')
		return false;
	// Adjacent searches
	char orientation = toupper(orientationsBoard[position.row][position.column]);
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
Checks if the given player has at least one possible playthrough
@param Player: player whose choices will be checked
@return: boolean indicating if the player can play
*/
bool Board::checkPossiblePlaytrough(const Player& player) const {
	// Iterate through all elements
	for (char i = 0; i < rows; i++)
		for (char j = 0; j < columns; j++)
			if (isupper(orientationsBoard[i][j]) && player.checkHasTile(board[i][j])) // If hasn't been played yet and the player has it on his hand
				if (checkValidPosition({ i,j }))
					return true;
	return false;
}

/**
Checks if the player completed a word
@param position: position of the chosen letter
@return: number of completed words
*/
char Board::checkCompleteWord(Position position) const {
	char orientation = toupper(orientationsBoard[position.row][position.column]);
	Position positionCopy = position; // Copy to undo changes in case of intersection
	char completedWord = 0; // Used in case of intersection or no completed words
	// Horizontal search
	if (orientation == 'H' || orientation == 'I') {
		// Verify forward
		position.column += 1;
		while (position.column >= columns || !isupper(orientationsBoard[position.row][position.column])) {
			if (position.column >= columns || orientationsBoard[position.row][position.column] == ' ') {
				if (orientation == 'H')
					return 1;
				// Verify backward intersection
				else {
					position = positionCopy;
					position.column += -1;
					while (position.column < 0 || !isupper(orientationsBoard[position.row][position.column])) {
						if (position.column < 0 || orientationsBoard[position.row][position.column] == ' ') {
							completedWord++;
							break;
						}
						position.column += -1;
					}
				}
				break;
			}
			position.column += 1;
		}
	}
	position = positionCopy;
	// Vertical search
	if (orientation == 'V' || orientation == 'I') {
		// Verify forward
		position.row += 1;
		while (position.row >= rows || !isupper(orientationsBoard[position.row][position.column])) {
			if (position.row >= rows || orientationsBoard[position.row][position.column] == ' ') {
				if (orientation == 'V')
					return 1;
				// Verify backward intersection
				else {
					position = positionCopy;
					position.row += -1;
					while (position.row < 0 || !isupper(orientationsBoard[position.row][position.column])) {
						if (position.row < 0 || orientationsBoard[position.row][position.column] == ' ') {
							completedWord++;
							break;
						}
						position.row += -1;
					}
				}
				break;
			}
			position.row += 1;
		}
	}
	return completedWord;
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
				setColor(LIGHTRED, BROWN);
			else
				setColor(BLACK, BROWN); // Change text and background color
			fout << board[i][j];
		}
		setColor(LIGHTGRAY, BLACK); // Reset text and background color
		fout << endl;
	}
}

/**
Adds a word in the arrays board and orientationBoard
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

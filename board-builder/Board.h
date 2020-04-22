#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

//----------------------------------------------------------------------
// CONSTANTS
//----------------------------------------------------------------------
const char MAX_ROWS = 20;
const char MAX_COLUMNS = 20;

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
// CLASS Board - DEFINITION 
//----------------------------------------------------------------------
class Board {
public:
	// constructors & destructors
	Board(char rows, char columns); // Set size and allocate board
	~Board(); // Free allocated memory
	// get methods
	char getRows() const;
	char getColumns() const;
	char getLetter(Position position) const;
	// set methods
	void addWordOnBoard(Instruction instruction);
	// search methods
	bool checkWordInDict(string word) const;
	bool checkPositionInVector(Position position) const;
	bool checkAdjacentPositions(Position position) const; // Check if the position is adjacent to any initial position already chosen
	bool checkInsideBoard(Instruction instruction) const;
	bool checkIntersection(Instruction instruction) const;
	// convertion methods
	Position strToPosition(string position) const; // Auxiliar function
	string positionToStr(Position position) const; // Auxiliar function
	string upperWord(string str) const; // Auxiliar function
	// output stream methods
	void displayBoard(ostream fout) const; // Draw the board in the specified stream
	void saveBoard(ostream fout) const;
	// input methods
	Instruction readInstruction() const; // Auxiliar
private:
	// private methods
	void addCharOnBoard(char letter, Position position);
	// attributes
	char rows;
	char columns;
	vector<Instruction> instructions;
	char** board;
};
#endif

#ifndef BOARD_H
#define BOARD_H

#include "utils.h"
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//----------------------------------------------------------------------
// CONSTANTS
//----------------------------------------------------------------------
#define MAX_SIZE 20
#define MIN_SIZE 0

//----------------------------------------------------------------------
// CLASS Board - DEFINITION 
//----------------------------------------------------------------------
class Board {
public:
	// constructors & destructors
	Board(char rows, char columns); // Set size and allocate board
	~Board(); // Free allocated memory
	// set methods
	void addWordOnBoard(Instruction instruction);
	// search methods
	bool checkWordInDict(string word) const;
	bool checkPositionInVector(Position position) const;
	bool checkAdjacentPositions(Position position) const; // Check if the position is adjacent to any initial position already chosen
	bool checkInsideBoard(Instruction instruction) const;
	bool checkIntersection(Instruction instruction) const;
	// output stream methods
	void displayBoard(ostream &fout) const;
	void saveBoard(ostream &fout) const;
private:
	// attributes
	char rows;
	char columns;
	vector<Instruction> instructions;
	char** board;
};
#endif

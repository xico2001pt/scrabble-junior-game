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
#define MIN_SIZE 1
#define DICTIONARY_FILE "WORDS.txt"

//----------------------------------------------------------------------
// CLASS Board - DEFINITION 
//----------------------------------------------------------------------
class Board {
public:
	// constructors & destructors
	Board(char rows, char columns, string filename); // Set size and allocate boards
	~Board(); // Free allocated memory
	// set methods
	void addWordOnBoard(Instruction instruction);
	// search methods
	bool checkWordInDict(string word) const;
	bool checkInstructionInVector(Instruction instruction) const;
	bool checkAdjacentPositions(Instruction instruction) const;
	bool checkInsideBoard(Instruction instruction) const;
	bool checkIntersection(Instruction instruction) const;
	// output stream methods
	void displayBoard(ostream &fout) const;
	void saveBoard() const;
private:
	// attributes
	char rows;
	char columns;
	string filename;
	vector<Instruction> instructions;
	char** board;
	char** orientationsBoard;
};
#endif

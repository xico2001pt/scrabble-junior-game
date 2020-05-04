#ifndef BOARD_H
#define BOARD_H

#include "utils.h"
#include "Player.h"
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//----------------------------------------------------------------------
// CONSTANTS
//----------------------------------------------------------------------


//----------------------------------------------------------------------
// CLASS Board - DEFINITION 
//----------------------------------------------------------------------
class Board {
public:
	// constructors & destructors
	Board(string filename); // Set size and allocate boards
	~Board(); // Free allocated memory
	// set methods
	void setPlayedLetter(Position position);
	void subRemainingWords();
	// get methods
	char getLetter(Position position) const;
	// search methods
	bool checkInsideBoard(Position position) const;
	bool checkValidPosition(Position position) const;
	bool checkPossiblePlaytrough(Player player) const;
	bool checkCompleteWord(Position position) const;
	// output stream methods
	void displayBoard(ostream& fout) const;
private:
	// private methods
	void addWordOnBoard(Instruction instruction);
	// attributes
	char rows;
	char columns;
	string filename;
	char** board;
	char** orientationsBoard; // Saves the orientation of the letters
	char remainingWords;
};
#endif

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


//----------------------------------------------------------------------
// CLASS Board - DEFINITION 
//----------------------------------------------------------------------
class Board {
public:
	// constructors & destructors
	Board(string filename); // Set size and allocate boards
	~Board(); // Free allocated memory
	// set methods
	void setLetter(Position position);
	// get methods
	char getLetter(Position position) const;
	// search methods
	bool checkInsideBoard(Instruction instruction) const;
	bool checkValidPosition() const;
	bool checkPossiblePlaytrough(vector<char> hand) const;
	bool checkCompleteWord(Position position) const;
	// output stream methods
	void displayBoard(ostream& fout) const;
	void loadBoard();
private:
	// attributes
	char rows;
	char columns;
	string filename;
	char** board;
	char** orientationsBoard; // Saves the orientation of the letters
	char remainingWord;
};
#endif

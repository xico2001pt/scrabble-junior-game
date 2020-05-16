#ifndef BOARD_HPP
#define BOARD_HPP

#include "utils.hpp"
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//----------------------------------------------------------------------
// CONSTANTS
//----------------------------------------------------------------------
#define MAX_SIZE 20
#define MIN_SIZE 5
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
	void addWordOnBoard(const Instruction& instruction);
	// get methods
	unsigned short getNumberOfTiles() const;
	// search methods
	bool checkWordInDict(const string& word) const;
	bool checkInstructionInVector(const Instruction& instruction) const;
	bool checkAdjacentPositions(const Instruction& instruction) const;
	bool checkInsideBoard(const Instruction& instruction) const;
	bool checkIntersection(const Instruction& instruction) const;
	// output stream methods
	void displayBoard(ostream& fout) const;
	void saveBoard() const;
private:
	// private methods
	void readDictionary();
	// attributes
	char rows;
	char columns;
	string filename;
	vector<Instruction> instructions;
	char** board;
	char** orientationsBoard; // Saves the orientation of the letters
	unsigned short numberOfTiles;
	vector<string> dictionary;
};
#endif

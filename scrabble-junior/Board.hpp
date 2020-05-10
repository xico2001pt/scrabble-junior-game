#ifndef BOARD_HPP
#define BOARD_HPP

#include "utils.hpp"
#include "Player.hpp"
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//----------------------------------------------------------------------
// CLASS Board - DEFINITION 
//----------------------------------------------------------------------
class Board {
public:
	// constructors & destructors
	Board(ifstream& fin); // Set size and allocate boards
	~Board(); // Free allocated memory
	// set methods
	void setPlayedLetter(const Position& position);
	void subRemainingWords();
	// get methods
	char getLetter(const Position& position) const;
	char getRows() const;
	char getColumns() const;
	char** getBoard() const;
	char getRemainingWords() const;
	// search methods
	bool checkInsideBoard(const Position& position) const;
	bool checkValidPosition(Position position) const;
	bool checkPossiblePlaytrough(const Player& player) const;
	bool checkCompleteWord(Position position) const;
	// output stream methods
	void displayBoard(ostream& fout) const;
private:
	// private methods
	void addWordOnBoard(const Instruction& instruction);
	// attributes
	char rows;
	char columns;
	char** board;
	char** orientationsBoard; // Saves the orientation of the letters
	char remainingWords;
};
#endif

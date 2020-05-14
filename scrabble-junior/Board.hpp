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
	Board(const Board& other); // Copy constructor
	~Board(); // Free allocated memory
	// set methods
	void setPlayedLetter(const Position& position);
	void subRemainingWords(char difference);
	// get methods
	char getLetter(const Position& position) const;
	char getRows() const;
	char getColumns() const;
	char** getBoard() const;
	char getRemainingWords() const;
	// search methods
	bool checkHasBeenPlayed(const Position& position) const;
	bool checkInsideBoard(const Position& position) const;
	bool checkValidPosition(Position position) const;
	bool checkPossiblePlaytrough(const Player& player) const;
	char checkCompleteWord(Position position) const;
	// output stream methods
	void displayBoard(ostream& fout) const;
private:
	// private methods
	void addWordOnBoard(const Instruction& instruction);
	bool checkAllPlayedUp(Position position) const;
	bool checkAllPlayedDown(Position position) const;
	bool checkAllPlayedRight(Position position) const;
	bool checkAllPlayedLeft(Position position) const;
	// attributes
	char rows;
	char columns;
	char** board;
	char** orientationsBoard; // Saves the orientation of the letters
	char remainingWords;
};
#endif

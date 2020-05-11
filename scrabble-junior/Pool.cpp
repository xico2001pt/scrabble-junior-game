#include "utils.hpp"
#include "Pool.hpp"
#include <iostream>
#include <ctype.h>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

//----------------------------------------------------------------------
// CLASS Pool - IMPLEMENTATION 
//----------------------------------------------------------------------

/**
Constructor
*/
Pool::Pool(char** board, char rows, char columns) {
	for (char i = 0; i < rows; i++)
		for (char j = 0; j < columns; j++)
			if (isalpha(board[i][j]))
				availableTiles.push_back(board[i][j]);
	shuffleTiles(); // Initial shuffle
}

/**
Destructor
*/
Pool::~Pool() {
}

/**
Adds a tile in the pool
@param letter: letter that will be added
@return: (none)
*/
void Pool::addTile(const char& letter) {
	availableTiles.push_back(letter);
}

/**
Removes a tile from the pool
@param index: index of the tile which will be removed
@return: (none)
*/
void Pool::removeTile(const size_t& index) {
	availableTiles.erase(availableTiles.begin() + index);
}

/**
Gets the number of available tiles
@return: integer indicating the number of available tiles
*/
size_t Pool::getAvailableTilesNumber() const {
	return availableTiles.size();
}

/**
Shuffles the pool randomly
@return: (none)
*/
void Pool::shuffleTiles() {
	random_shuffle(availableTiles.begin(), availableTiles.end());
}

/**
Gets a random tile from de the pool and removes it
@return: character representing the chosen tile
*/
char Pool::getRandomTile() {
	// Select random index
	size_t index = randomNumber(0, availableTiles.size() - 1);
	// Pick and delete selected letter
	char letter = availableTiles.at(index);
	removeTile(index);
	return letter;
}

/**
Gets a starting hand
@return: vector containing the starting hand
*/
vector<char> Pool::getRandomHand() {
	vector<char> hand;
	for (char i = 0; i < INITIAL_TILES; i++)
		hand.push_back(getRandomTile());
	return hand;
}

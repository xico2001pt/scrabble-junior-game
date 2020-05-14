#include "utils.hpp"
#include "Board.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

//----------------------------------------------------------------------
// CLASS Player - IMPLEMENTATION 
//----------------------------------------------------------------------

/**
Constructor
*/
Player::Player(vector<char> hand, short ID) : score(0), hand(hand), ID(ID) {
}

/**
Destructor
*/
Player::~Player() {
}

/**
Increment the player's score
@param increment : value to add to the score
@return: (none)
*/
void Player::increaseScore(const char& increment) {
	score += increment;
}

/**
Recover a tile from the pool to player's hand
@param pool: pool containing the remaining tiles
@return: (none)
*/
void Player::recoverTileFromPool(Pool& pool) {
	// Get random tile from the pool
	char letter = pool.getRandomTile();
	// Add tile to player's hand
	hand.push_back(letter);
}

/**
Remove the chosen letter from the player's hand
@param letter: letter which will be removed
@return: (none)
*/
void Player::removeTileFromHand(const char& letter) {
	hand.erase(find(hand.begin(), hand.end(), letter));
}

/**
Trades one tile if the player can't make a move
@param pool: pool containing the remaining tiles
@return: (none)
*/
void Player::tradeTiles(Pool& pool) {
	bool isValid = false;
	do {
		char input = readTile(); // Reads valid input
		if (isInVector(input, hand)) {
			removeTileFromHand(input);
			recoverTileFromPool(pool);
			pool.addTile(input);
			isValid = true;
		}
		else
			cout << "Please choose a tile that you have!" << endl;
	} while (!isValid);
}

/**
Gets the current score of the player
@return: score of the player
*/
unsigned char Player::getScore() const {
	return score;
}

/**
Gets the ID of the player
@return: ID of the player
*/
short Player::getID() const {
	return ID;
}

/**
Checks if player has tile on his hand
@param letter: tile which will be searched
@return: boolean indicating whether the player has the tile or not
*/
bool Player::checkHasTile(const char& letter) const {
	return isInVector<char>(letter, hand);
}

/**
Display the player's hand in the specified output stream
@param fout: output stream where the hand will be displayed
@return: (none)
*/
void Player::displayTiles(ostream& fout) const {
	unsigned char i; // Temporary variable
	// Display tiles
	for (i = 0; i < hand.size(); i++)
		fout << hand.at(i) << ' ';
	// Display missing spaces
	for (i; i < 7; i++)
		fout << "  ";
}

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "utils.hpp"
#include "Pool.hpp"
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//----------------------------------------------------------------------
// CONSTANTS
//----------------------------------------------------------------------
#define MAX_PLAYERS 4
#define MIN_PLAYERS 2

//----------------------------------------------------------------------
// CLASS Player - DEFINITION 
//----------------------------------------------------------------------
class Player {
public:
	// constructors & destructors
	Player(vector<char> hand);
	~Player();
	// set methods

	// get methods
	unsigned char getScore() const;
	// search methods
	bool checkHasTile(const char &letter) const;
	// output stream methods
	void displayTiles(ostream& fout) const;
	// other methods
	void play();
private:
	// private methods
	void recoverTileFromPool(Pool &pool);
	void removeTileFromHand(const char &letter);
	void tradeTiles(Pool& pool);
	// attributes
	unsigned char score;
	vector<char> hand;

};
#endif

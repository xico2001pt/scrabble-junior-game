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
	Player(vector<char> hand, short ID);
	~Player();
	// set methods
	void increaseScore(const char& increment);
	void recoverTileFromPool(Pool& pool);
	void removeTileFromHand(const char& letter);
	void tradeTiles(Pool& pool);
	// get methods
	unsigned char getScore() const;
	short getID() const;
	// search methods
	bool checkHasTile(const char& letter) const;
	// output stream methods
	void displayTiles(ostream& fout) const;
private:
	// attributes
	unsigned char score;
	vector<char> hand;
	short ID;
};
#endif

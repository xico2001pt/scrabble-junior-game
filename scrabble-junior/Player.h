#ifndef PLAYER_H
#define PLAYER_H

#include "utils.h"
#include "Board.h"
#include "Pool.h"
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//----------------------------------------------------------------------
// CONSTANTS
//----------------------------------------------------------------------


//----------------------------------------------------------------------
// CLASS Player - DEFINITION 
//----------------------------------------------------------------------
class Player {
public:
	// constructors & destructors
	Player();
	~Player();
	// set methods

	// get methods

	// search methods
	bool checkHasTile(Position position, Board board) const;
	// output stream methods
	void displayTiles(ostream& fout) const;
	// other methods
	void play();
private:
	// private methods
	void recoverTileFromPool(Pool pool);
	void removeTileFromHand(char letter);
	void tradeTiles(Pool pool);
	// attributes
	unsigned char score = 0;
	vector<char> hand;

};
#endif

#ifndef POOL_H
#define POOL_H

#include "Player.h"
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//----------------------------------------------------------------------
// CONSTANTS
//----------------------------------------------------------------------


//----------------------------------------------------------------------
// CLASS Pool - DEFINITION 
//----------------------------------------------------------------------
class Pool {
public:
	// constructors & destructors
	Pool(char** board);
	~Pool();
	// random methods
	void shuffleTiles();
	char getRandomTile(); // Deletes tile from vector
	vector<char> getRandomHand();
private:
	// private methods

	// attributes
	vector<char> availableTiles;
};
#endif

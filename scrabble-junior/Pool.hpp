#ifndef POOL_HPP
#define POOL_HPP

#include <fstream>
#include <string>
#include <vector>
using namespace std;

//----------------------------------------------------------------------
// CONSTANTS
//----------------------------------------------------------------------
#define INITIAL_TILES 7

//----------------------------------------------------------------------
// CLASS Pool - DEFINITION 
//----------------------------------------------------------------------
class Pool {
public:
	// constructors & destructors
	Pool(char** board, char rows, char columns);
	~Pool();
	// set methods
	void addTile(const char& letter);
	void removeTile(const size_t& index); // Deletes tile from vector
	// get methods
	size_t getAvailableTilesNumber() const;
	// random methods
	void shuffleTiles();
	char getRandomTile();
	vector<char> getRandomHand();
private:
	// attributes
	vector<char> availableTiles;
};
#endif

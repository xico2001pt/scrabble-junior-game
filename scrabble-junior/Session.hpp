#ifndef SESSION_HPP
#define SESSION_HPP

#include "utils.hpp"
#include "Board.hpp"
#include "Player.hpp"
#include "Pool.hpp"
#include <vector>
using namespace std;

//----------------------------------------------------------------------
// CONSTANTS
//----------------------------------------------------------------------
#define PLAYS_PER_TURN 2

//----------------------------------------------------------------------
// CLASS Session - DEFINITION 
//----------------------------------------------------------------------
class Session {
public:
	// constructors & destructors
	Session(Board board, Pool pool, char numberOfPlayers);
	~Session();
	// get methods
	vector<Player> getPlayers() const;
	// output stream methods
	void displaySessionInfo() const;
	void play(Player& player);
	char checkWinner() const;
private:
	// attributes
	Board board;
	vector<Player> players;
	Pool pool;
};
#endif

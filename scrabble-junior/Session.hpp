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
	Session(Board board, int numberOfPlayers);
	~Session();
	// output stream methods
	void displaySessionInfo(ostream& fout) const;
	void displayLeaderboard(ostream& fout) const;
	// search methods
	bool checkHasEnoughTiles() const;
	// play methods
	void gameSession();
	void playTurn(Player& player);
	void playTile(Player& player);
private:
	// attributes
	Board scrabbleBoard;
	Pool pool;
	vector<Player> players;
};
#endif

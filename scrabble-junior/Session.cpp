#include "Session.hpp"
#include "utils.hpp"
#include "Board.hpp"
#include "Player.hpp"
#include "Pool.hpp"
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

//----------------------------------------------------------------------
// CLASS Session - IMPLEMENTATION 
//----------------------------------------------------------------------

/**
Constructor
*/
Session::Session(Board board, Pool pool, char numberOfPlayers) {
}

/**
Destructor
*/
Session::~Session() {
}

void Session::play(Player& player) {
	Position position;
	char completedWords, tilesPlayed = 0;
	while (tilesPlayed < PLAYS_PER_TURN && board.checkPossiblePlaytrough(player)) {
		position = readPosition();
		if (!board.checkInsideBoard(position))
			cerr << "";
		else if (board.checkHasBeenPlayed(position))
			cerr << "";
		else if (!player.checkHasTile(board.getLetter(position)))
			cerr << "";
		else if (!board.checkValidPosition(position))
			cerr << "";
		else {
			board.setPlayedLetter(position);
			player.removeTileFromHand(board.getLetter(position));
			if (pool.getAvailableTilesNumber > 0)
				player.recoverTileFromPool(pool);
			completedWords = board.checkCompleteWord(position);
			player.increaseScore(completedWords);
			board.subRemainingWords(completedWords);
			tilesPlayed++;
		}
	}
	if (tilesPlayed == 0)
		for (char i = 0; i < min((size_t)PLAYS_PER_TURN, pool.getAvailableTilesNumber()); i++)
			player.tradeTiles(pool);
}
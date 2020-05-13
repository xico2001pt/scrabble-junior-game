#include "Session.hpp"
#include "utils.hpp"
#include "Board.hpp"
#include "Player.hpp"
#include "Pool.hpp"
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
using namespace std;

//----------------------------------------------------------------------
// CLASS Session - IMPLEMENTATION 
//----------------------------------------------------------------------

/**
Constructor
*/
Session::Session(Board board, char numberOfPlayers) : scrabbleBoard(board), pool(Pool(board)) {
	for (short i = 0; i < numberOfPlayers; i++)
		players.push_back(Player(this->pool.getRandomHand(), i + 1));
}

/**
Destructor
*/
Session::~Session() {
}

void Session::displaySessionInfo(ostream& fout) const {
	system("cls"); // Clear console
	fout << "Remaining Pool Tiles: ";
	setColor(YELLOW, BLACK);
	fout << pool.getAvailableTilesNumber() << endl;
	setColor(LIGHTGRAY, BLACK); // Reset text and background color

	scrabbleBoard.displayBoard(fout);

	fout << "-------------------------------------------" << endl;
	for (Player player : players) {
		fout << "| Player " << player.getID() << ": ";
		player.displayTiles(fout);
		cout << "| Score: " << setw(6) << (int)player.getScore() << " |" << endl;
	}
	fout << "-------------------------------------------" << endl;
}

bool Session::checkHasEnoughTiles() const {
	return (pool.getAvailableTilesNumber() >= INITIAL_TILES * players.size());
}

void Session::gameSession() {
	// Check for enough tiles
	if (!checkHasEnoughTiles())
		cerr << "There aren't enough tiles to everyone!\nThe game will be shut down!" << endl;
	// Game Loop
	char currentPlayer = 0;
	while (scrabbleBoard.getRemainingWords() > 0) {
		playTurn(players.at(currentPlayer));
		currentPlayer = (currentPlayer + 1) % players.size();
	}
	// Display leaderboard

}

void Session::playTurn(Player& player) {
	char tilesPlayed = 0;
	displaySessionInfo(cout);
	while (tilesPlayed < PLAYS_PER_TURN && scrabbleBoard.checkPossiblePlaytrough(player)) {
		setColor(LIGHTBLUE, BLACK);
		cout << "Player " << player.getID();
		setColor(LIGHTGRAY, BLACK);
		cout << ", choose a position to play:" << endl;
		playTile(player);
		displaySessionInfo(cout);
		tilesPlayed++;
	}
	if (tilesPlayed == 0)
		for (size_t i = 0; i < min((size_t)PLAYS_PER_TURN, pool.getAvailableTilesNumber()); i++)
			player.tradeTiles(pool);
}

void Session::playTile(Player& player) {
	Position position;
	char completedWords;
	bool isValid = false;
	while (!isValid) {
		position = readPosition();
		if (!scrabbleBoard.checkInsideBoard(position))
			cerr << "The chosen position does not belong to the board!" << endl;
		else if (scrabbleBoard.checkHasBeenPlayed(position))
			cerr << "That position has already been played!" << endl;
		else if (!scrabbleBoard.checkValidPosition(position))
			cerr << "The chosen position is invalid!" << endl;
		else if (!player.checkHasTile(scrabbleBoard.getLetter(position)))
			cerr << "The tile corresponding to the chosen position is not in your hand!" << endl;
		else {
			isValid = true;
			scrabbleBoard.setPlayedLetter(position);
			player.removeTileFromHand(scrabbleBoard.getLetter(position));
			if (pool.getAvailableTilesNumber() > 0)
				player.recoverTileFromPool(pool);
			completedWords = scrabbleBoard.checkCompleteWord(position);
			player.increaseScore(completedWords);
			scrabbleBoard.subRemainingWords(completedWords);
		}
	}
}
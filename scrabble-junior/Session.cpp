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
Session::Session(Board board, int numberOfPlayers) : scrabbleBoard(board), pool(Pool(board)) {
	for (short i = 0; i < numberOfPlayers; i++)
		players.push_back(Player(this->pool.getRandomHand(), i + 1));
}

/**
Destructor
*/
Session::~Session() {
}

/**
Displays the board and the players scores and hands
@param fout: output stream where the session info will be displayed
@return: (none)
*/
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
		fout << "| Score: " << setw(6) << (int)player.getScore() << " |" << endl;
	}
	fout << "-------------------------------------------" << endl;
}

/**
Displays the leaderboard
@param fout: output stream where the session info will be displayed
@return: (none)
*/
void Session::displayLeaderboard(ostream& fout) const {
	system("cls");
	fout << "|-------   LEADERBOARD   -------|" << endl;
	for (Player player : players)
		fout << "|    Player " << player.getID() << "       " << right << setw(3) << (int)player.getScore() << left << " PTS     |" << endl;
	fout << "|-------------------------------|" << endl;
}

/**
Checks if there are enough initial tiles for every player
@return: boolean indicating if the enough initial tiles for every player
*/
bool Session::checkHasEnoughTiles() const {
	return (pool.getAvailableTilesNumber() >= INITIAL_TILES * players.size());
}

/**
Manages the entire game
@return: (none)
*/
void Session::gameSession() {
	// Check for enough tiles
	if (!checkHasEnoughTiles())
		cerr << "There aren't enough tiles to everyone!\nThe game will be shut down!" << endl;
	else {
		// Game Loop
		char currentPlayer = 0;
		while (scrabbleBoard.getRemainingWords() > 0) {
			playTurn(players.at(currentPlayer));
			currentPlayer = (currentPlayer + 1) % players.size();
		}
		cout << "All tiles have been played!" << endl;
		getchar(); // Wait for the user to continue
		// Display leaderboard
		displayLeaderboard(cout);
		getchar(); // Wait for the user to continue
	}
}

/**
Manages each turn
@param player: player who is playing the turn
@return: (none)
*/
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
	if (tilesPlayed == 0) {
		if (pool.getAvailableTilesNumber() == 0)
			cout << "You can't play in this turn!" << endl;
		for (size_t i = 0; i < min((size_t)PLAYS_PER_TURN, pool.getAvailableTilesNumber()); i++) {
			cout << "Choose the tile you want to trade:" << endl;
			player.tradeTiles(pool);
		}
	}
	else if (tilesPlayed == 1 && scrabbleBoard.getRemainingWords() > 0) {
		cout << "You can't play a second tile!" << endl;
		getchar(); // Wait for the user to continue
	}
}

/**
Manages the game according to the chosen tile
@param player: player who is playing the turn
@return: (none)
*/
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
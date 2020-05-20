/*
FILE   : main.cpp
DATE   : 2020/05/02
AUTHOR : Francisco Cerqueira, Vasco Alves
PROGRAM PURPOSE:
- Allow user to play Scrabble Junior with up to 3 friends
*/

#include "utils.hpp"
#include "Board.hpp"
#include "Session.hpp"
#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>
using namespace std;

int main() {
	srand(time(NULL)); // Randomize values
	// Ask for input filename
	string filename;
	cout << "Insert the board filename:" << endl;
	getline(cin, filename);
	// Validate file
	ifstream fin(filename + ".txt");
	if (fin.fail()) {
		cerr << "Input file opening failed!" << endl;
		getchar(); // Wait for the user to continue
		exit(1); // Stop the program with exit code != 0
	}
	// Ask for number of players
	cout << "Choose the number of players (2-4):" << endl;
	int numberOfPlayers = readInteger();
	while (numberOfPlayers < MIN_PLAYERS || numberOfPlayers > MAX_PLAYERS) {
		cerr << "Choose a number between (including) " << MIN_PLAYERS << " and " << MAX_PLAYERS << "!" << endl;
		numberOfPlayers = readInteger();
	}
	// Game setup
	Board board(fin); // Create Board
	Pool pool(board); // Create Pool
	if (pool.getAvailableTilesNumber() < INITIAL_TILES * numberOfPlayers) {
		cerr << "There aren't enough tiles to everyone!\nThe game will be shut down!" << endl;
		getchar(); // Wait for the user to continue
		exit(1); // Stop the program with exit code != 0
	}
	Session session(board, pool, numberOfPlayers); // Create Session
	// Play the game
	session.gameSession();
	return 0;
}
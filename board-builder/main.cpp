/*
FILE   : main.cpp
DATE   : 2020/04/20
AUTHOR : Francisco Cerqueira, Vasco Alves
PROGRAM PURPOSE:
- Allow user to create a board that can be used to play Scrabble Junior
*/

#include "utils.h"
#include "Board.h"
#include <iostream>
using namespace std;

// Currently being used to test and debug methods
int main() {
	Board board(15, 15, "BOARD");
	board.addWordOnBoard({ {0,1},'V',"ABCABC" });
	board.addWordOnBoard({ {2,0},'H',"ACCABB" });
	board.displayBoard(cout);
	// cout << board.checkIntersection({ { 0,0 }, 'H', "AAC" });
	board.saveBoard();
	getchar();
	return 0;
}
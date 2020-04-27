/*
FILE   : main.cpp
DATE   : 2020/04/20
AUTHOR : Francisco Cerqueira, Vasco Alves
PROGRAM PURPOSE:
- To be added...
*/

#include "utils.h"
#include "Board.h"
#include <iostream>
using namespace std;

// Currently being used to test and debug methods
int main() {
	//ofstream fout("save.txt");
	Board board(15, 15);
	Board ori(15, 15);
	//board.displayBoard(fout);
	board.addWordOnBoard({ {0,1},'V',"ABC" });
	board.addWordOnBoard({ {2,0},'H',"ACC" });
	ori.addWordOnBoard({ {0,1},'V',"VVV" });
	ori.addWordOnBoard({ {2,0},'H',"H-" });
	board.displayBoard(cout);
	cout << board.checkAdjacentPositions({ {0,0},'H',"ABCD" }, ori);
	getchar();
	return 0;
}
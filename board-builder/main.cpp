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
	Board board(10, 10);
	board.addWordOnBoard({ {2,3},'V',"PAULO" });
	board.addWordOnBoard({ {3,2},'H',"MARTA" });
	board.displayBoard(cout);
	getchar();
	return 0;
}
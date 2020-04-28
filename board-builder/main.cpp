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

int main() {
	// Ask board size
	unsigned int rows, columns;
	char separator;
	bool isValid=false;
	cout << "Choose a size to the board (rows x columns):" << endl;
	while (!isValid) {
		cin >> rows >> separator >> columns;
		if (cin.fail() || cin.peek() != '\n') {
			cerr << "Invalid Format!" << endl;
			cin.clear();
		}
		else if (rows < MIN_SIZE || rows > MAX_SIZE || columns < MIN_SIZE || columns > MAX_SIZE)
			cerr << "Invalid Dimensions!" << endl;
		else
			isValid = true;
		cin.ignore(1000, '\n');
	}
	// Ask board filename
	string filename;
	cout << "Choose a name to the board:" << endl;
	getline(cin, filename);
	// Create board object
	Board board((char)rows, (char)columns, filename);
	// While loop
	Instruction instruction;
	bool running = true;
	while (running) {
		system("cls"); // Clear console
		board.displayBoard(cout);
		cout << "Insert instruction (Ex: Ca H DOG):\n(CTRL^Z to exit)" << endl;
		if (!readInstruction(instruction))
			running = false;
		else if (board.checkInstructionInVector(instruction)) {
			cerr << "The instruction has already been used!" << endl;
			getchar();
		}
		else if (!board.checkInsideBoard(instruction)) {
			cerr << "The word doesn't fit in the board!" << endl;
			getchar();
		}
		else if (!board.checkAdjacentPositions(instruction) || !board.checkIntersection(instruction)) {
			cerr << "Invalid position!" << endl;
			getchar();
		}
		else if (!board.checkWordInDict(instruction.word)) {
			cerr << "Please choose a word from the dictionary!" << endl;
			getchar();
		}
		else
			board.addWordOnBoard(instruction);
	}
	// Save file
	board.saveBoard();
	cout << "The board was successfully saved!" << endl;
	getchar();
	return 0;
}

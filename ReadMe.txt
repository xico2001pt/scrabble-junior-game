------------------------------------------------------------------------------
		SCRABBLE JUNIOR GAME  - PROG/MIEIC, 2019/20
------------------------------------------------------------------------------
Authors:Francisco Cerqueira 	(up201905337)
	Vasco Alves 		(up201808031)
Class:	1MIEIC07
Group:	T7G06

------------------------------------------------------------------------------
				DEVELOPMENT STATE
------------------------------------------------------------------------------
When developing the program, the following recomendations were respected:
	- Adequate choice of identifiers of types, variables and functions.
	- Code and functions commenting.
	- Modular structure of the code.
	- Adequate choice of function prototypes, namely, appropriate choice of 
	parameters passed by value and by reference and adequate use of const qualifiers.
	- Separation, as much as possible, of data processing from program input/output.
	- Precautions were taken in order to prevent the program to stop working due to 
	incorrect input by the user, specially values outside the allowed ranges, and so on.
	- Code efficiency and robustness.

------------------------------------------------------------------------------
				BOARD BUILDER
------------------------------------------------------------------------------
WORK OVERVIEW:
	The objective was to develop a program to build game boards for the 
	Scrabble Junior game, with the user choosing which words will be 
	placed in the board, ALWAYS respecting the positioning rules.

OBJECTIVES OVERVIEW:
	All the objectives were accomplished, including the 2D view of the board at 
	the end of the file, which was optional.

PROGRAM FLOW:
	1. Ask the user to input the board size (between MIN_SIZE and MAX_SIZE) and 
	the name of the file in which will be saved.
	2. Creation of the board object, dinamically allocating the necessary memory 
	and saving the dictionary words.
	3. Main loop of the program, where the user will insert instructions, whose 
	validation will be verified by the program. The loop ends when the user 
	inserts CTRL^Z (EOF).
	4. The board is saved to a .txt file in case the total number of letters is 
	equal or greater than 14.

ALGORITHMS & DATA STRUCTURES USED:
	- Two arrays called board and orientationsBoard were used to save the words 
	and the orientation of each letter (H, V or I), respectively.
	- A struct composed by the initial position, orientation and a word is used to represent an instruction.
	- When a word is added to the board, the board and the orientationsBoard 
	are automatically updated and the tile before the beginning and after the 
	end of the word, are marked to represent a forbidden spot.
	- The steps to validate an instruction are:
		1. Check if the instruction has already been chosen.
		2. Check if the word fits in the board.
		3. Check if the adjacent orientations are valid. *Explained in detail below
		4. Check if the word intersects well with the words already on board. **Explained in detail below
		5. Check if the word is in the dictionary.

* It was empirically observed that any lateral adjacent tile must have the opposite orientation to the chosen word;
** Besides the direct intersection with other words, the spot before the first tile and after the last tile must be empty;

------------------------------------------------------------------------------
				SCRABBLE JUNIOR
------------------------------------------------------------------------------
WORK OVERVIEW:
	The objective was to develop a program to play the game Scrabble Junior. 
	The objective of the game is to cover the gameboard letters with matching 
	letter tiles, and collect the most scoring chips by completing words.
	The playing program allows two to four players to play the game, detecting 
	the end of the game and announcing the winner.

OBJECTIVES OVERVIEW:
	All the objectives were accomplished.
	Aditionally, a leaderboard was displayed at the end of the game.

PROGRAM FLOW:
	1. Ask the user to input the filename, verifying its validation, and the 
	number of players (between MIN_PLAYERS and MAX_PLAYERS).
	2. Verify if the number of tiles is enough for each player to have 7 initial tiles.
	3. Main loop of the game, where each player plays according to the official rules. 
	(https://www.hasbro.com/common/instruct/Scrabble_Junior.pdf)
	4. Announce the end of the game and display the leaderboard.

ALGORITHMS & DATA STRUCTURES USED:
	- Classes were used to represent and manipulate the Board, Player, Pool and the Session.
	- The pool is built according to the board initial tiles.
	- A vector of players is used to keep the player's data and order.
	- To represent that a tile has been already played, the corresponding tile 
	in the orientationsBoard is set to lowercase. ***Explained in detail below
	- The algorithms used to verify if the move completed a word is 
	described in the code with comments.
	- The steps to validate a move are:
		1. Check if the tile is not outside the board.
		2. Check if the move has already been played.
		3. Check if the move respects the official rules (the played letter does not 
		match with the letter in the chosen position, ...).
		4. Check if the tile is in the player's hand.

***Example of the board when Eb and Bg were played (on board they are represented in red and in orientationsBoard in lowercase)
	board					orientationsBoard
-------------------------------		--------------------------------
  a b c d e f g h i j k l m n o   	  a b c d e f g h i j k l m n o
A   F           D     E G G S		A   V           V     H H I H
B   R   B     B U Z Z     O		B   V   V     h I H I     V
C M U S I C     C   E     A R M		C H I H I H     V   V     I H V
D   I   C       K   B O A T   O		D   V   V       V   I H H I   V
E   T O Y   S       R         N		E   i H I   V       V         V
F       C   H       A R C A D E		F       V   V       I H I H H V
G       L   E   T       A     Y		G       V   V   V       V     V
H     T E L E V I S I O N		H     H I H I H I H H H I
I           P   G       D O G		I           V   V       I H I
J         J     E   B O Y   R		J         V     V   H H I   V
K       W A T E R           A X		K       H I H H I           I H
L         C             B   P		L         V             V   V
M     S   K         A   A   E		M     V   V         V   V   V
N   Q U E E N     A P P L E S		N   H I H I H     H I H I H I
O     N   T         E   L		O     V   V         V   V
#include <stdbool.h>
#ifndef HEADER
#define HEADER

typedef struct{			// creating a structure type
	// declaring subelements of the structure
	char** board;		// subelement board with double pointers
	char** tempBoard;	// subelement tempBoard with double pointers to store the original values and mines of the game
	int row;			// subelement row to store the row dimension of the board
	int col;			// subelement col to store the column dimension of the board
	int seed;			// subelement seed to store the seed of the game
	int mines;			// subelement mines to store the number of mines in the game
} game;

bool read_args(int argumentCount, char* array[], game* gamename);
void create_board(game* gamename);
void place_mines(game* gamename,char* seed);
void destroy_board(game* gamename);
void print_board(game* gamename);
void testprint_board(game* gamename);
void setToHashtags(game* gamename);

void numLabel(game* gamename);
void copyElements(game* gamename);

void playGame(game* gamename);
void getMove(game* gamename);
bool validPlay(int inputRow,int inputCol,int choice, game gamename);
void checkDigit(game* gamename, int currRow, int currCol);
bool isgameover(game* gamename);

void startGame(game* gamename,char* seed);

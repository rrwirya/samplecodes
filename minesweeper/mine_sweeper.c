#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "header.h"

void startGame(game* gamename,char* seed){		// function startGame as a combination of several functions to start the game, accepts one input argument
	// calling multiple custom functions
	create_board(gamename);			// calling create_board
	place_mines(gamename,seed);			// calling place_mines
	numLabel(gamename);				// calling numLabel
	copyElements(gamename);			// calling copyElements
	setToHashtags(gamename);		// calling setToHashtags
	print_board(gamename);			// calling print_board
}

int main(int argc, char* argv[]){
	// declaring a variable
	game minesweeper;					// declaring a structure (game) with a name variable minesweeper
	
	// calling read_args
	read_args(argc,argv,&minesweeper);	// calling the first read_args function to check the amount of input arguments entered

	// assigning other variables
	minesweeper.row = atoi(argv[1]);	// assigning the number of rows into subelement row of the structure
	minesweeper.col = atoi(argv[2]);	// assigning the number of columns into subelement col of the structure
	minesweeper.mines = atoi(argv[3]);	// assigning the number of mines into subelement mines of the structure
	// minesweeper.seed = atoi(argv[4]);	// assigning the seed into subelement seed of the structure
	
	// calling other functions
	startGame(&minesweeper,argv[4]);			// calling startGame
	testprint_board(&minesweeper);		// calling testprint_board
	playGame(&minesweeper);				// calling playGame
	destroy_board(&minesweeper);		// calling destroy_board
	
	return 0;
}

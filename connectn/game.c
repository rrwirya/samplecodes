/*
	This part of the program plays the game, checks if the part of the
	board entered by the user is valid, and puts the respective pieces
	into the board. This program is a sub program of connectn.c.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "connectn.h"

void play_game(char** board, int turn, int rows, int cols, int wincondition){																										
	/*
		A function to play the game. This function will call print_board to print
		the board and the updated version of the board after every turn, and 
		get_play to receive user input values for the piece locations in the board.
	*/
	// !game_over(board, rows, cols, wincondition)
	// declaring variables
	char pieces[] = "XO";								// pieces as the pieces that will be used in the game
	//int k = 0;
	
	// making the game run
	while(!game_over(board, rows, cols, wincondition))	// loop to make the game run until the game is over
	{
		print_board(board,rows,cols);					// printing the board using the function print_board
		get_play(&board, pieces[turn], rows, cols);	
		turn = (turn + 1) % 2;							// changing the turn every time to switch between players
		//k = k+1;
	}
	print_board(board,rows,cols);
	if(game_won(board,rows,cols,wincondition)){			// if a player wins the game
		if(turn==1){									// if it was about to be the second player's turn
			printf("Player 1 Won!\n");					// player 1 won message shown
		}
		else{
			printf("Player 2 Won!\n");					// player 2 won message shown
		}
	}
	else
	{
		printf("Tie game!\n");							// if nobody won, game is tie message shown
	}
	return;
}

void get_play(char*** board, char piece, int row, int col){																																																										
	/*
		A function to receive user input value from the user. This function
		also updates the board elements with pieces after the user enters
		a valid input argument. This function calls the function play_is_valid
		to determine if the user input value is a valid argument for this game.
	*/
	
	// declaring variables
	int inputcol = -1;			// variable inputcol as the variable that will be used to store the user input value
	int numargsinputed = -1;	// variable numargsinputed as the variable that will be used to determine the amount of user input values entered
	int i;						// variable i that will be used inside a for loop

	
	// loop to check if the value is valid
	while(!(play_is_valid(*board, inputcol, col, numargsinputed)))					// if the value is not a valid argument
	{
		printf("Enter a column between 0 and %d to play in: ", col-1);				// prompting the user for user input value
		numargsinputed = scanf("%d", &inputcol);									// numargsinputed to store the value of the amount of input arguments by the user
	}
	
	for(i = (row-1); i >= 0 ; --i){				// for loop according to the number of rows, but from bottom to top
		if((*board)[i][inputcol]=='*')			// if there is a blank space in the board on that column, checking row by row
		{
			(*board)[i][inputcol] = piece;		// assign that particular space with a symbol according to the turn
			break;
		}
	}
	return;
}

bool play_is_valid(char** board, int inputcol, int col, int numargs){																									
	/*
		A function to check if the value entered by the user is a valid
		user input argument.
	*/
	
	// declaring variables
	int boardcolumns = col - 1;	// boardcolumns variable as the right edge boundary of the board
	
	// checking the validity of the user input argument
	if(numargs!=1)														// if the amount of input arguments is not one
	{
		return false;
	}
	if( (inputcol < 0) || (inputcol > boardcolumns) )					// if the inputcol value is beyond the horizontal boundaries of the array
	{
		return false;						
	}
	else if( board[0][inputcol] != '*' )								// if the top row of the input column is not empty
	{
		return false;
	}
	else																// if all of the conditions above were passed
	{
		return true;
	}
}

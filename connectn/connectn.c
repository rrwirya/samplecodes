/*
	This part of the program reads the input arguments that was 
	entered into the Terminal. This program runs the main functions
	required to run the connectn game. This program calls functions
	located in other parts of the programs. Sub programs of this main
	program include: board.c, game.c, and win.c.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "connectn.h"

bool read_args(int commandCount){																																					
	/*
		A function to check the amount of input arguments entered 
		in the terminal. Returns true or false depending on the amount
		arguments entered.
		Assumption: All the arguments entered are integers
	*/
	
    if(commandCount < 4)							// if input arguments is less than four
	{
        printf("Not enough arguments entered\n");	// print not enough arguments messae
        printf("Usage connectn.out num_rows num_columns number_of_pieces_in_a_row_needed_to_win\n");
        exit (EXIT_SUCCESS);						// exit command with fail status
    }
    else if(commandCount > 4)						// if input arguments is more than four
	{
        printf("Too many arguments entered\n");	// print too many arguments message
        printf("Usage connectn.out num_rows num_columns number_of_pieces_in_a_row_needed_to_win\n");
        exit (EXIT_SUCCESS);						// exit command with fail status
    } 	
    else											// if input arguments is exactly four
	{
        return true;								// return true if arguments is only four
    }
}

int main(int argc, char* argv[]){
	// declaring variables
    char** board;									// variable board as a double pointer value to represent a 2D array
    int turn;										// variable turn that will be used to change the turns of the game

	// calling a function
    read_args(argc);								// calling the first function read_args
	
	// declaring more variables after the program passed read_args
	// if the program doesn't pass read_args, the program will automatically close itself
	int rows = atoi(argv[1]);						// converting the first argument vector into variable rows using atoi command
	int cols = atoi(argv[2]);						// converting the second argument vector into variable cols using atoi command
	int winstreak = atoi(argv[3]);					// converting the third argument vector into variable winstreak using atoi command

	// calling other functions
    create_board(&board, &turn, rows, cols);		// calling create_board to create the board based on the dimensions determined by the user
	play_game(board, turn, rows, cols, winstreak);	// playing the game by calling play_game, which calls other functions
	destroy_board(&board,rows);						// destroying the board to free up memory after the game is over by calling destroy_board
	return 0;
}

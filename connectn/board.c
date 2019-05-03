/*
	This part of the program creates the board and displays the board
	of the game. This part of the program also deletes the board once
	the game is over. This part of the program belongs to the original
	connectn.c program.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "connectn.h"

void create_board(char*** board, int* turn, int rows, int cols){																													
	/*
		A function to allocate memory for the connectn board.
	*/
	
	// declaring variables
    int currentRow;		// variable currentRow that will be used in a for loop
    int currentCol;		// variable currentCol that will be used in a for loop
	*turn = 0;			// turn variable that always points to 0 as to make player 1 move first
	
	// allocating memory for the board
    (*board) = (char**)malloc(rows * sizeof(char*));					// allocating memory for the pointer of the board
    for(currentRow = 0; currentRow < rows; currentRow++)				// for loop according to the number of rows in the board
	{
		(*board)[currentRow] = (char*)malloc(cols * (sizeof(char)));	// allocating memory for each column in the board
		for(currentCol = 0; currentCol < cols; currentCol++)			// for loop according to the number of columns in the board
		{
			(*board)[currentRow][currentCol] = '*';						// assigning an asterisk symbol into each part of the board
		}
    }
    return;
}

void destroy_board(char*** board, int rows){																																		// FUNCTION (MIGHT HAVE) PASSED
	/*
		A function to destroy the board, in order to free up
		the memory that has been used for the program to run.
		The program is called after the game is over.
	*/
	
	// declaring variables
    int currentRow;			// variable currentRow that will be used in a for loop

	// free-ing up the board pointer
    for(currentRow = 0; currentRow < rows; ++currentRow)		// for loop according to the number of rows
	{		
        free((*board)[currentRow]);								// free-ing memory in each row
    }
    free(*board);												// free-ing memory that was used for the board
    *board = NULL;
    return;
}

void print_board(char** board, int rows, int cols){																																	
	/*
		This function was created to display the board in the terminal.
		This function will be called in the play_game function, where it
		will be called several times until the game is over. The function
		also displays the updated version of the board after pieces are applied.
	*/
	
	// declaring variables
    int currCol;				// variable currCol that will be used in a for loop
	int currRow;				// variable currRow that will be used in a for loop
	int rowHeaders = rows - 1;	// variable rowHeaders that will be used to print the header of the rows in the board
	int colHeaders = 0;			// variable colHeaders that will be used to print the header of the columns in the board
		
	// displaying the board and the header
	for(currRow = 0; currRow < rows ; currRow++)		// for loop according to the number of rows
	{
        printf("%d ", rowHeaders);						// printing the header with the variable rowHeaders
        for(currCol = 0; currCol < cols; currCol++)		// for loop according to the number of columns
		{
            printf("%c ", board[currRow][currCol]);		// printing the board
        }
		printf("\n");
		rowHeaders--;									// rowHeaders decreases after each iteration
    }
	
	printf(" ");										// printing a spacebar to align the column header
	
	// displaying the column header
	for(colHeaders = 0; colHeaders < cols; colHeaders++)// for loop according to the number of columns
	{
		printf(" %d", colHeaders);						// printing the header with the variable colHeaders
	}
	printf("\n");										
    return;
}

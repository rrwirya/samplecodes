/*
	This part of the program checks the win conditions that is required
	to terminate the game. This program contains multiple win conditions,
	a function to determine if the game is a tie or a won, and a function
	to end the game. This program is a sub program of connectn.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "connectn.h"

bool row_win(char** board, int rows, int cols, int wincon){
	/*
		A function to check if any player has won by alligning
		their pieces horizontally (in one row).
	*/
	
	// declaring variables
	int i,j,k;	// variable i (as a row index) that will be used in a for loop
				// variable j (as a column index) that will be used in a for loop
				// variable k (as a winstreak index) that will be used in a for loop

	// checking for any streaks
	for(i = 0; i < rows ; ++i)							// for loop according to the number of rows
	{
		for(j = 0; j <= (cols - wincon) ; ++j)			// for loop according to the number of columns
		{
			if(board[i][j] != '*')						// if an element ont the board has a piece
			{
				for(k = 1; k < wincon; ++k)				// for loop according to the win streak determined by the user
				{
					if(board[i][j] != board[i][j+k])	// checking if the pieces doesn't match each other
					{
						break;							// breaking the whole command
					}		
				}
				if(k == wincon)							// if the streak (with variable k) is the same as the determined win streak
				{
					return true;						// returning true for row_win
				}					
			}		
		}
	}
	return false;
}

bool col_win(char** board, int rows, int cols, int wincon){
	/*
		A function to check if any player has won by alligning
		their pieces vertically (in one column).
	*/
	
	// declaring variables
	int i,j,k;	// variable i (as a row index) that will be used in a for loop
				// variable j (as a column index) that will be used in a for loop
				// variable k (as a winstreak index) that will be used in a for loop
	
	// checking for any streaks
	for(i = 0; i <= (rows - wincon) ; i++)					// for loop according to the number of rows
	{
		for(j = 0; j < cols ; j++)							// for loop according to the number of columns
		{
			if(board[i][j] != '*')							// if an element ont the board has a piece
			{
				for(k = 1; k < wincon; k++)					// for loop according to the win streak determined by the user
				{
					if(board[i][j] != board[i+k][j])		// checking if the pieces doesn't match each other
					{
						break;								// breaking the whole command
					}
				}
				if(k == wincon)								// if the streak (with variable k) is the same as the determined win streak
				{	
					return true;							// returning true for col_win
				}
			}
		}
	}
	return false;
}

bool left_to_right_diag_win(char** board, int rows, int cols, int wincon){
	/*
		A function to check if any player has won by alligning
		their pieces diagonally, from left top side to bottom
		right side.
	*/
	
	// declaring variables
	int i,j,k;  // variable i (as a row index) that will be used in a for loop
				// variable j (as a column index) that will be used in a for loop
				// variable k (as a winstreak index) that will be used in a for loop
	
	// checking for any diagonal (left top to right bottom) streaks
	for(i = 0; i < (rows-wincon+1); i++)				// for loop according to the rows that needs to be checked		
	{
		for(j = 0; j < (cols-wincon+1); j++)			// for loop according to the columns that needs to be checked
		{
			if(board[i][j]!='*')						// if a particular element in the array is not empty
			{
				for(k = 0; k < wincon ; k++)			// for loop according to the winstreak
				{
					if(board[i][j]!=board[i+k][j+k])	// if the next diagonal elements are not the same with the certain element in the outer if statement
					{
						break;							// breaking the loop
					}
				}
				if(k == wincon)							// if the above for loop runs successfully
				{
					return true;						// return true value
				}
			}
		}
	}
	return false;
}

bool right_to_left_diag_win(char** board, int rows, int cols, int wincon){
	/*
		A function to check if any player has won by alligning
		their pieces diagonally, from right top side to bottom
		left side.
	*/
	
	// declaring variables
	int i,j,k;  // variable i (as a row index) that will be used in a for loop
				// variable j (as a column index) that will be used in a for loop
				// variable k (as a winstreak index) that will be used in a for loop
	
	// checking for any diagonal (right top to left bottom) streaks
	for(i = 0; i < (rows-wincon+1); i++)				// for loop according to the rows that needs to be checked
	{
		for(j = (cols - 1); j >= wincon - 1; j--)		// for loop according to the columns that needs to be checked
		{
			if(board[i][j]!='*')						// if a particular element in the array is not empty
			{
				for(k = 0; k < wincon ; k++)			// for loop according to the winstreak
				{
					if(board[i][j] != board[i+k][j-k])	// if the next diagonal elements are not the same with the certain element in the outer if statement
					{
						break;							// breaking the loop
					}
				}
				if(k == wincon)							// if the above for loop runs successfully
				{
					return true;						// return true value
				}
			}
		}
	}
	return false;
}

bool game_won(char** board, int rows, int cols, int wincondition){
	/*
		A function to check if the game is won by a player or not
	*/
	
	// returning boolean values based on the types of win streak
	return row_win(board,rows,cols,wincondition) || col_win(board,rows,cols,wincondition) || left_to_right_diag_win(board,rows,cols,wincondition) || right_to_left_diag_win(board,rows,cols,wincondition);	
}

bool tie_game(char** board, int rows, int cols, int wincondition){																													
	/*
		A function to check if the game is not a win and a tie instead
	*/
	
	// declaring variables
	int i,j;						// variable i that will represent row number, and variable j that will represent column number
	int count = 0;					// variable count that will be used to detect if the board is full or not
	
	// for loop to check if the board is fully filled
	for(i = 0; i<rows ; i++){		// for loop according to the number of rows
		for(j = 0; j<cols ; j++){	// for loop according to the number of columns
			if(board[i][j]!='*'){	// if a particular position is filled
				count++;			// adding the amount of count
			}
		}
	}
	if(count==(rows*cols))			// if the number of count is equal to rows*cols
	{
		return true;
	}
	else							// if the value of count is not equal to rows*cols
	{
		return false;
	}
	
}

bool game_over(char** board, int rows, int cols, int wincondition){
	/*
		A function to return a boolean for game_over as to end the game
	*/
	
	return game_won(board,rows,cols,wincondition) || tie_game(board,rows,cols,wincondition);	// returning boolean values based on the type of end games (win or tie)
}

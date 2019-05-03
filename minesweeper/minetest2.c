#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

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



	// READ_ARGS
	
	
	
bool read_args(int argumentCount, char* array[], game* gamename){			// function read_args to determine if the number of input arguments is enough for the program
	if ( argumentCount<4 ){													// if arguments input is less than 4
		printf("Not enough arguments. Usage:\n");							// printing the not enough arguments entered sentence
		printf("./mine_sweeper.out num_rows num_cols num_mines [seed])");
		exit (EXIT_SUCCESS);												// exit the program
	}
	else if ( argumentCount>5 ){											// if arguments input is more than 5
		printf("Too many arguments. Usage:\n");								// printing the too much arguments entered sentence
		printf("./mine_sweeper.out num_rows num_cols num_mines [seed])");
		exit (EXIT_SUCCESS);												// exit the program
	}/*
	else if ( argumentCount==5 ){											// if arguments entered is 5
		srand(atoi(array[4]));												// setting the srand to the seed number which is the fourth argument 
		return true;
	}
	else if ( argumentCount==4 ){											// if arguments entered is 4
		srand(time(NULL));													// setting the srand related to time
		return true;
	}*/
	else{
		return true;
	}
}



	// CREATE_BOARD, DESTROY_BOARD, PRINT_BOARD, PLACE_MINES, SETTOHASHTAGS, TESTPRINT_BOARD



void create_board(game* gamename){											// function create_board to create the boards that will be used, accepts one input argument, which is a structure 
	// declaring variables
	int i,j;						// variable i that will be used as an index for row, and variable j that will be used as an index for column			
	int row = gamename->row;		// variable row which represents the number of rows in the game
	int col = gamename->col;		// variable col which represents the number of columns in the game
	
	// allocating space for element board of the structure
	(*gamename).board = (char**)malloc(row * sizeof(char*));		// malloc for the board
	for( i=0 ; i<row ; i++ ){										// for loop according to rows
		(*gamename).board[i] = (char*)malloc(col * sizeof(char));	// malloc for each column
		for( j=0 ; j<col ; j++ ){									// for loop according to columns
			(*gamename).board[i][j] = '#';							// assigning a hashtag symbol to each element within the board
		}
	}
	
	// allocating space for element tempBoard of the structure
	(*gamename).tempBoard = (char**)malloc(row * sizeof(char*));		// malloc for the temporary board
	for( i=0 ; i<row ; i++ ){											// for loop according to rows
		(*gamename).tempBoard[i] = (char*)malloc(col * sizeof(char));	// malloc for each column
		for( j=0 ; j<col ; j++ ){										// for loop according to columns
			(*gamename).tempBoard[i][j] = '#';							// assigning a hashtag symbol to each element within the board
		}
	}
}

void place_mines(game* gamename,char* seed){				// function place_mines to assign mines onto the board randomly, accepts one input argument, which is a structure
	// declaring variables
	int row,col;					// row and col variables that will be used to temporarily store the index column and row that will be used to place the mines
	int num_mines_placed = 0;		// num_mines_placed variable to count the amount of mines assigned onto the board
	int num_rows = gamename->row;	// variable num_rows which represents the number of rows in the board
	int num_cols = gamename->col;	// variable num_cols which represents the number of columns in the board
	
	if(seed == NULL){
		srand(time(NULL));
	}
	else{
		srand(atoi(seed));
	}
	
	// placing the mines in the board
	while(num_mines_placed < gamename->mines){	// while loop based on the amount of mines placed is according to the user input value
		row = rand() % num_rows;				// setting a random location for row
		col = rand() % num_cols;				// setting a random location for col
		
		if(gamename->board[row][col] != '*'){	// if there are no mines in that particular position that was randomized
			gamename->board[row][col] = '*';	// assigning a mine onto that place
			num_mines_placed++;					// incrementing num_mines_placed, to break the while loop after certain iterations
		}
	}
}

void destroy_board(game* gamename){		// function destroy_board to destroy the boards created with malloc, accepts one input argument, which is a structure	
	// declaring variables
	int rows = gamename->row;			// variable rows to represent the total number of rows in the boards		
    int i;								// variable i as to represent an index of each row
	
	// free-ing subelement board of the structure
    for( i=0; i<rows; i++ ){			// for loop according to the number of rows		
        free(gamename->board[i]);		// free-ing the row elements of the board					
    }			
	free(gamename->board);				// free-ing the board itself
	
	// free-ing subelement tempBoard of the structure
	for( i=0 ; i<rows; i++ ){			// for loop according to the number of rows
		free(gamename->tempBoard[i]);	// free-ing the row elements of the tempBoard
	}
	free(gamename->tempBoard);			// free-ing the tempBoard itself
	
    return;
}

void print_board(game* gamename){		// function print_board to print the board that will be played on, accepts one input argument, which is a structure																																
    // declaring variables
	int i,j;					// variable i and j that will be respectively used for row and column indexes in a for loop				
	int row = gamename->row;	// variable row to represent the total number of rows in a board
	int col = gamename->col;	// variable col to represent the total number of columns in a board
	int rowHeaders = row - 1;	// variable rowHeaders that will be used to print the row header of the board	
	int colHeaders = 0;			// variable colHeaders that will be used to print the column header of the board
			
	// printing the elements within the board
	for( i=0; i<row ; i++ ){		// for loop according to the number of rows
        printf("%d ", rowHeaders);	// printing rowHeaders first					
        for( j=0; j<col ; j++ ){	// for loop according to the number of columns
			printf("%c ", gamename->board[i][j]);	// printing the elements within the board
        }
		printf("\n");				
		rowHeaders--;				// decreasing the value of rowHeaders after each iteration					
    }
	printf(" ");					// printing a spacebar				
	for( j=0; j<col; j++ ){			// for loop according to the number of columns
		printf(" %d", colHeaders);	// printing the colHeaders
		colHeaders++;				// incrementing colHeaders
	}
	printf("\n");										
    return;
}

void testprint_board(game* gamename){					// function testprint_board to print the subelement tempBoard of the structure		
														// this function is unecessarily needed to run the program, but may be used for certain purposes like debugging
    // declaring variables
	int i,j;						// variables i and j that will be used as row and column indexes in for loops respectively
	int row = gamename->row;		// variable row to represent the number of rows in a board
	int col = gamename->col;		// variable col to represent the number of cols in a board
	int rowHeaders = row - 1;		// variable rowHeaders that will be used to print the row header of the board 
	int colHeaders = 0;				// variable colHeaders that will be used to print the column header of the board
		
	// printing the elements within tempBoard
	for( i=0; i<row ; i++ ){		// for loop according to the number of rows
        printf("%d ", rowHeaders);	// printing rowHeaders first					
        for( j=0; j<col ; j++ ){	// for loop according to the number of columns
			printf("%c ", gamename->tempBoard[i][j]);	// printing the elements within tempBoard
        }
		printf("\n");
		rowHeaders--;				// decreasing the value of rowHeaders after each iteration								
    }
	printf(" ");					// printing a spacebar							
	for( j=0; j<col; j++ ){			// for loop according to the number of columns
		printf(" %d", colHeaders);	// printing the colHeaders
		colHeaders++;				// incrementing colHeaders
	}
	printf("\n");										
    return;
}

void setToHashtags(game* gamename){								// function setToHashtags to change the values of board back into hashtags, accepts one argument only
	// declaring variables
	int rows = gamename->row;				// variable rows that represents the number of rows in a board
	int cols = gamename->col;				// variable cols that represents the number of columns in a board
	int i,j;								// variables i and j that will be used as a row and column index within a for loop
	
	// setting the board into hashtags
	for( i=0 ; i<rows ; i++ ){				// for loop according to the rows
		for( j=0; j<cols ; j++ ){			// for loop according to the columns
			gamename->board[i][j] = '#';	// setting the elements within board of the structure into hashtags
		}
	}
	
	// finding the amount of mines
	for( i=0 ; i<rows ; i++ ){									// for loop according to the rows
		for( j=0; j<cols ; j++ ){								// for loop according to the columns
			if( gamename->tempBoard[i][j] == '*' ){				// finding the mines from tempBoard
				printf("Placing mine at %d, %d\n",rows-1-i,j);	// printing the amount of mines in a sentence
			}
		}
	}
}



	// NUMLABEL,COPYELEMENTS


	
void numLabel(game* gamename){						// function numLabel to label the numbers in the tiles, which will be obtained from the number of nearby mines
													// accepts only one input argument structure
	
	// declaring variables
	int i = 0;										// variable i to represent row indexes that will be used in multiple for loops
	int j = 0;										// variable j to represent column indexes that will be used in multiple for loops
	int rows = gamename->row;						// variable rows to represent the total number of rows in the board
	int cols = gamename->col;						// variable cols to represent the total number of columns in the board
	int numMinesPerTile[rows][cols];				// an Array numMinesPerTile to temporarily store the amount of mines found nearby a certain tile
	
	// for loop to set all the elements of numMinesPerTile to zero
	for( i=0 ; i<rows ; i++ ){						
		for( j=0 ; j<cols ; j++ ){
			numMinesPerTile[i][j] = 0;				// assigning zero as to set zero as the initial count of the number of mines found nearby a certain tile
		}
	}
	
	// for loop and multiple if statements to find the nearby mines
	for( i=0 ; i<rows ; i++ ){						// for loop according to rows
		for( j=0 ; j<cols ; j++ ){					// for loop according to columns
			if(gamename->board[i][j] == '*'){		// if a mine is found in a certain location
				if(i<(rows-1)){
					numMinesPerTile[i+1][j]++;		// adding the count in the tile above the mine
				}
				if(i>0){
					numMinesPerTile[i-1][j]++;		// adding the count in the tile below the mine
				}
				if(j<(cols-1)){
					numMinesPerTile[i][j+1]++;		// adding the count in the tile beside (right) the mine
				}
				if(j>0){
					numMinesPerTile[i][j-1]++;		// adding the count in the tile beside (left) the mine
				}
				if((i<(rows-1))&&(j<(cols-1))){
					numMinesPerTile[i+1][j+1]++;	// adding the count in the tile diagonally right top of the mine
				}
				if((i<(rows-1))&&(j>0)){
					numMinesPerTile[i+1][j-1]++;	// adding the count in the tile diagonally left top of the mine
				}
				if((i>0)&&(j<(cols-1))){
					numMinesPerTile[i-1][j+1]++;	// adding the count in the tile diagonally right bottom of the mine
				}
				if((i>0)&&(j>0)){
					numMinesPerTile[i-1][j-1]++;	// adding the count in the tile diagonally left bottom of the mine
				}
			}
		}
	}
	
	// assigning the unique numbers into board
	for( i=0 ; i<rows ; i++ ){									// for loop according to the number of rows
		for( j=0 ; j<cols ; j++ ){								// for loop according to the number of columns
			if(gamename->board[i][j] != '*'){					// if a certain tile is not a mine
				char numMines = numMinesPerTile[i][j] + '0';	// converting numMinesPerTile into a character
				gamename->board[i][j] = numMines;				// storing the numerical character onto board
			}
		}
	}
	return;
}

void copyElements(game* gamename){								// function copyElements to copy values from board into tempBoard, as to store the mines and numbers in tempBoard
	// declaring variables
	int rows = gamename->row;			// variable rows to represent the number of rows in a board		
	int cols = gamename->col;			// variable cols to represent the number of columns in a board
	int i,j;							// variables i and j to represent the row and column indexes used in a for loop
	
	// copying the values 
	for( i=0 ; i<rows ; i++ ){											// for loop according to the number of rows					
		for( j=0 ; j<cols ; j++ ){										// for loop according to the number of columns
			gamename->tempBoard[i][j] = gamename->board[i][cols-1-j];	// copying the element with assignments
		}
	}
}



	// PLAYGAME, GETMOVE, VALIDPLAY, CHECKZERO

	

void playGame(game* gamename){									// playGame function to play the game until the game is over
	// running multiple custom functions
	while(!isgameover(gamename)){								// while the game is not over, continuing the game
		getMove(gamename);										// calling function getMove with one input argument gamename
		printf("There are %d mines left\n",gamename->mines);	// printing the number of mines left sentence
		print_board(gamename);									// calling the function print_board with one input argument gamename
	}
	printf("You won!!\n");										// if the person has won, printing the winning sentence
	exit (EXIT_SUCCESS);										// exit the program
}

void getMove(game* gamename){									// function getMove to obtain a move from the user
	// declaring variables
	int inputRow = -1;					// variable inputRow that will store the user input value for the row	
	int inputCol = -1;					// variable inputCol that will store the user input value for the column
	int choice = -1;					// variable choice that will store the user input value for the options
	int rows = gamename->row - 1;		// variable rows that will store the number of total rows in the board
	
	// asking the user for user input values
	while(!validPlay(inputRow,inputCol,choice,*gamename)){													// iterating the loop everytime the move entered is not valid
		printf("Enter row a row between 0-%d and a column between 0-%d: ",gamename->row-1,gamename->col-1);	// printing the sentence that prompts user input
		scanf("%d %d",&inputRow,&inputCol);							// scanning the values into inputRow and inputCol
		if(gamename->board[rows - inputRow][inputCol] == '?'){		// if the location chosen has a question mark symbol in the tile, printing a certain set of options
			printf("Enter Action\n");
			printf("0. UnQuestion\n");
			printf("1. Cancel\n");
			printf("Action: ");
			scanf("%d",&choice);
		}
		else{														// otherwise, printing the normal set of options for the particular chosen tile
			printf("Enter Action\n");
			printf("0. Reveal\n");
			printf("1. Question\n");
			printf("2. Mark\n");
			printf("3. Cancel\n");
			printf("Action:");
			scanf("%d",&choice);
		}
	}

	// after an option has been chosen
	if(choice==0){												// if choice is zero	
		if(gamename->board[rows-inputRow][inputCol] == '?'){	// if the tile was previously a question mark symbol
			gamename->board[rows-inputRow][inputCol] = '#';		// setting the element of the tile back into a hashtag
			print_board(gamename);								// printing the board
			playGame(gamename);									// calling the function playGame
		}
		else{													// otherwise
			gamename->board[rows - inputRow][inputCol] = gamename->tempBoard[rows - inputRow][inputCol];	// revealing the tile that was chosen by the user
			if(gamename->tempBoard[rows - inputRow][inputCol]=='*'){										// if the tile chosen was a mine
				testprint_board(gamename);																	// printing the answer board or tempBoard
				printf("You Lost :(\n");																	// printing the losing sentence
				exit (EXIT_SUCCESS);																		// exit the program
			}
			int currentRow = rows - inputRow;																// declaring currentRow variable 
			checkDigit(gamename,currentRow,inputCol);														// calling checkDigit function
		}
	}
	else if(choice==1){											// if choice is a one
		gamename->board[rows-inputRow][inputCol] = '?';			// assigning a question mark symbol onto the board
	}
	else if(choice==2){											// if choice is a two
		gamename->board[rows-inputRow][inputCol] = '!';			// assigning an exclamation mark symbol onto the board
		if(gamename->tempBoard[rows-inputRow][inputCol]=='*'){	// if there was originally a mine on that particular position
			gamename->mines--;									// reducing the amount of mines from the structure
		}
	}
	else{														// otherwise
		getMove(gamename);										// calling getMove as a recursion
	}
}

bool validPlay(int inputRow,int inputCol,int choice, game gamename){	// validPlay function to check if the move chosen is a valid move
	// declaring variables
	int rows = gamename.row - 1;					// variable rows that represents the total rows in a board	
	int cols = gamename.col - 1;					// variable cols that represents the total columns in a board
	
	// checking conditions
	if( (inputRow<0) || (inputRow>rows) ){			// if the row input was out of bound
		return false;								// returning false 
	}
	else if( (inputCol<0) || (inputCol>cols) ){		// if the column input was out of bound
		return false;								// returning false
	}
	else if( (choice<0) || (choice>3) ){			// if the choice was 'out of bound'
		return false;								// returning false
	}
	else if(isdigit(gamename.board[rows-inputRow][inputCol])){	// if the tile chosen was already revealed (is a digit)
		printf("This tile is already revealed.\n");				// printing the tile is revealed sentence
		return false;											// returning false
	}
	else{				// otherwise
		return true;	// return true
	}
}

void checkDigit(game* gamename, int currRow, int currCol){		// checkDigit function to check the amount of digits found
	// declaring variables
	int totCols = gamename->col;								// variable totCols to represent the total number of columns in a board
	int totRows = gamename->row;								// variable totRows to represent the total number of rows in a board
	
	// if statements for recursions
	if(isdigit(gamename->tempBoard[currRow][currCol])){								// if a digit is found on a particular location
		gamename->board[currRow][currCol] = gamename->tempBoard[currRow][currCol];	// assigning that tile with its respective number
		if((currRow+1)<totRows){													
			if(isdigit(gamename->tempBoard[currRow+1][currCol])){					// if another digit is found on top of that tile
				if(gamename->board[currRow+1][currCol]=='#'){						// if it is a closed tile
					checkDigit(gamename,currRow+1,currCol);							// calling checkZero function again with different arguments
				}
			}
		}
		if(currRow>0){
			if(isdigit(gamename->tempBoard[currRow-1][currCol])){					// if another digit is found on the bottom of that tile
				if(gamename->board[currRow-1][currCol] == '#'){						// if it is a closed tile
					checkDigit(gamename,currRow-1,currCol);							// calling checkZero function again with different arguments
				}
			}
		}
		if((currCol+1)<totCols){
			if(isdigit(gamename->tempBoard[currRow][currCol+1])){					// if another digit is found on the right side of that tile
				if(gamename->board[currRow][currCol+1] == '#'){						// if it is a closed tile
					checkDigit(gamename,currRow,currCol+1);							// calling checkZero function again with different arguments
				}
			}
		}
		if(currCol>0){
			if(isdigit(gamename->tempBoard[currRow][currCol-1])){					// if another digit is found on the left side of that tile
				if(gamename->board[currRow][currCol-1] == '#'){						// if it is a closed tile
					checkDigit(gamename,currRow,currCol-1);							// calling checkZero function again with different arguments
				}
			}
		}
		if(((currRow+1)<totRows)&&((currCol+1)<totCols)){
			if(isdigit(gamename->tempBoard[currRow+1][currCol+1])){					// if another digit is found on the top right side of that tile
				if(gamename->board[currRow+1][currCol+1] == '#'){					// if it is a closed tile
					checkDigit(gamename,currRow+1,currCol+1);						// calling checkZero function again with different arguments
				}
			}
		}
		if(((currRow+1)<totRows)&&(currCol>0)){
			if(isdigit(gamename->tempBoard[currRow+1][currCol-1])){					// if another digit is found on the top left side of that tile
				if(gamename->board[currRow+1][currCol-1] == '#'){					// if it is a closed tile
					checkDigit(gamename,currRow+1,currCol-1);						// calling checkZero function again with different arguments
				}
			}
		}
		if(((currRow)>0)&&((currCol+1)<totCols)){
			if(isdigit(gamename->tempBoard[currRow-1][currCol+1])){					// if another digit is found on the bottom right side of that tile
				if(gamename->board[currRow-1][currCol+1] == '#'){					// if it is a closed tile
					checkDigit(gamename,currRow-1,currCol+1);						// calling checkZero function again with different arguments
				}
			}
		}
		if((currRow>0)&&(currCol>0)){
			if(isdigit(gamename->tempBoard[currRow-1][currCol-1]=='0')){			// if another digit is found on the bottom left side of that tile
				if(gamename->board[currRow-1][currCol-1] == '#'){					// if it is a closed tile
					checkDigit(gamename,currRow-1,currCol-1);						// calling checkZero function again with different arguments
				}
			}
		}
	}
	else{
		return;
	}
}



	// ISGAMEOVER
	
	
	
bool isgameover(game* gamename){					// isgameover function to check if the game is already over
	// declaring variables
	int numRows = gamename->row;					// variable numRows to represent the total number of rows in a board			
	int numCols = gamename->col;					// variable numCols to represent the total number of columns in a board
	int i,j;										// variables i and j to represent the row and column indexes that will be used in a for loop
	int remainingSymbols = 0;						// variable remainingSymbols to count the amount of symbols left on the board
	for( i=0 ; i<numRows ; i++ ){					// for loop according to the number of rows
		for ( j=0 ; j<numCols ; j++ ){				// for loop according to the number of columns
			if( gamename->board[i][j] == '#' ){	// CHECK AGAIN
				remainingSymbols++;					// incrementing remainingSymbols
			}
		}
	}
	if(remainingSymbols!=0){						// if remainingSymbols is not zero
		return false;								// game is not over
	}
	else{											// otherwise
		return true;								// game is over
	}
}	



	// STARTGAME, MAIN



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

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

bool read_args(int argumentCount);

void create_board(char*** board, int row, int col);
void place_mines(char*** board, int num_rows, int num_cols, int num_mines, int seed);
void destroy_board(char*** board, int rows);
void print_board(char** board, int rows, int cols);

void numLabel(char*** board, int rows, int cols);

typedef struct{
	int numMinesNearby;
	char symbolOnTile;
	bool mineCheck;
	int rowIndex;
	int colIndex;
} tileStatusStruct;



	// READ_ARGS
	
	
	
bool read_args(int argumentCount){
	if ( argumentCount<4 ){
		printf("Not enough arguments entered.\n");
		printf("Usage: mine_sweeper.out num_rows num_cols num_mines seed(optional)");
		exit (EXIT_SUCCESS);
	}
	else if ( argumentCount>5 ){
		printf("Too many arguments entered.\n");
		printf("Usage: mine_sweeper.out num_rows num_cols num_mines seed(optional)");
		exit (EXIT_SUCCESS);
	}/*
	else if( argumentCount==5 ){
		*seed = atoi(argumentList[4]);
		return true;
	}
	else if( argumentCount==4 ){
		*seed = srand((int)time(NULL));
		return true;
	}*/
	else{
		return true;
	}
}



	// CREATE_BOARD, PLACE_MINES, DESTROY_BOARD, PRINT_BOARD



void create_board(char*** board, int row, int col){
	int currentRow, currentCol;
	
	(*board) = (char**)malloc(row*sizeof(char*));
	for( currentRow=0 ; currentRow<row ; currentRow++ ){
		(*board)[currentRow] = (char*)malloc(col * (sizeof(char)));
		for( currentCol=0 ; currentCol<col ; currentCol++ ){
			(*board)[currentRow][currentCol] = '#';
		}
	}
	return;
}

void place_mines(char*** board, int num_rows, int num_cols, int num_mines, int seed){
	srand(seed); // only once
	
	int num_mines_placed = 0;
	int row,col;
	while(num_mines_placed < num_mines){
		row = rand() % num_rows;
		col = rand() % num_cols;
		
		if((*board)[row][col] != '*'){
			(*board)[row][col] = '*';
			num_mines_placed++;
		}
	}
}

void destroy_board(char*** board, int rows){																																		
    int currentRow;			
    for(currentRow = 0; currentRow < rows; ++currentRow)		
	{		
        free((*board)[currentRow]);								
    }
    free(*board);												
    *board = NULL;
    return;
}

void print_board(char** board, int rows, int cols){																																	
    int currCol;				
	int currRow;				
	int rowHeaders = rows - 1;	
	int colHeaders = 0;			
		
	for(currRow = 0; currRow < rows ; currRow++)		
	{
        printf("%d ", rowHeaders);						
        for(currCol = 0; currCol < cols; currCol++)		
		{
			printf("%c ", board[currRow][currCol]);
			
        }
		printf("\n");
		rowHeaders--;									
    }
	
	printf(" ");										
	
	for(colHeaders = 0; colHeaders < cols; colHeaders++)
	{
		printf(" %d", colHeaders);						
	}
	printf("\n");										
    return;
}



	// NUMLABEL, COPYTOSTRUCT, COVERBOARD



void numLabel(char*** board, int rows, int cols){
	int i = 0;
	int j = 0;
	
	int numMinesPerTile[rows][cols];
	
	for( i=0 ; i<rows ; i++ ){
		for( j=0 ; j<cols ; j++ ){
			numMinesPerTile[i][j] = 0;
		}
	}
	
	for( i=0 ; i<rows ; i++ ){
		for( j=0 ; j<cols ; j++ ){
			if((*board)[i][j] == '*'){
				if(i<(rows-1)){
					numMinesPerTile[i+1][j]++;
				}
				if(i>0){
					numMinesPerTile[i-1][j]++;
				}
				if(j<(cols-1)){
					numMinesPerTile[i][j+1]++;
				}
				if(j>0){
					numMinesPerTile[i][j-1]++;
				}
				if((i<(rows-1))&&(j<(cols-1))){
					numMinesPerTile[i+1][j+1]++;
				}
				if((i<(rows-1))&&(j>0)){
					numMinesPerTile[i+1][j-1]++;
				}
				if((i>0)&&(j<(cols-1))){
					numMinesPerTile[i-1][j+1]++;
				}
				if((i>0)&&(j>0)){
					numMinesPerTile[i-1][j-1]++;
				}
			}
		}
	}
	
	for( i=0 ; i<rows ; i++ ){
		for( j=0 ; j<cols ; j++ ){
			if((*board)[i][j] != '*'){
				char numMines = numMinesPerTile[i][j] + '0';
				(*board)[i][j] = numMines;
			}
		}
	}
	return;
}
/*
tileStatusStruct copyToStruct(char** board, int rows, int cols, tileStatusStruct*** structName){
	int i = 0; int j = 0;
	for( i=0 ; i<rows ; i++ ){
		for( j=0 ; j<cols ; j++ ){
			structName[i][j].symbolOnTile = board[i][j];
			structName[i][j].rowIndex = i;
			structName[i][j].colIndex = j;
			if(board[i][j]=='*'){
				structName[i][j].mineCheck = true;
			}
			else{
				structName[i][j].numMinesNearby = board[i][j];
			}
			printf("%c ",structName[i][j].symbolOnTile);
		}
		printf("\n");
	}
	return structName;
}
*/
void coverBoard(char*** board, int rows, int cols){
	
	
}



	// PLAYGAME



void play_game(char** board){
	int turns;
	for( turns=0 ; turns<100 ; turns++ ){
		
	}
	
	
	
	
	
}


	
	// MAIN



int main(int argc, char* argv[]){
	char** board;
	//int seed;
	
	read_args(argc);
	
	int num_rows = atoi(argv[1]);
	int num_cols = atoi(argv[2]);
	int num_mines = atoi(argv[3]);
	
	int seed = atoi(argv[4]);

	//tileStatusStruct TILESTRUCT[num_rows][num_cols];
	
	create_board(&board,num_rows,num_cols);
	place_mines(&board,num_rows,num_cols,num_mines,seed);
	numLabel(&board,num_rows,num_cols);
	print_board(board,num_rows,num_cols);
	printf("\n\n");
	//TILESTRUCT = copyToStruct(board,num_rows,num_cols,TILESTRUCT);
	
	destroy_board(&board,num_rows);
}

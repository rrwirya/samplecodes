#include <stdbool.h>
	#ifndef CONNECTN
	#define CONNECTN

bool read_args(int commandCount);

void create_board(char*** board, int* turn, int rows, int cols);
void destroy_board(char*** board, int rows);
void print_board(char** board, int rows, int cols);

bool row_win(char** board, int rows, int cols, int wincon);
bool col_win(char** board, int rows, int cols, int wincon);
bool left_to_right_diag_win(char** board, int rows, int cols, int wincon);
bool right_to_left_diag_win(char** board, int rows, int cols, int wincon);
bool game_won(char** board, int rows, int cols, int wincondition);
bool tie_game(char** board, int rows, int cols, int wincondition);
bool game_over(char** board, int rows, int cols, int wincondition);

void play_game(char** board, int turn, int rows, int cols, int wincondition);
void get_play(char*** board, char piece, int row, int col);
bool play_is_valid(char** board, int inputcol, int col, int numargs);

#endif

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define USER 'O'
#define COMP 'X'
#define EMPTY ' '
#define MAX 1000
#define MIN -1000

#ifdef _WIN32
#define COLOR_RED     ""
#define COLOR_GREEN   ""
#define COLOR_RESET   ""
#else
#define COLOR_RED 	 "\033[31m"
#define COLOR_GREEN  "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_RESET  "\033[0m"
#endif

struct Game {
	char board[3][3];
	char winner, turn;
	bool tied;
};

struct Move {
	int row, col;
};

void print_board(struct Game G);
void print_result(struct Game G);
int board_value(struct Game G);
int minimax(struct Game G);
bool game_complete(struct Game *G);
bool rematch(void);
struct Game game_init(char first_player);
struct Game board_update(struct Game G, struct Move m);
struct Move user_move(struct Game G);
struct Move computer_move(struct Game G);
struct Move *possible_moves(struct Game G, int *count);

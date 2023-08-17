#define USER 'O'
#define COMP 'X'
#define EMPTY ' '
#define MAX 1000
#define MIN -1000

/* Color compatibility for Windows */
#ifdef _WIN32
#include <windows.h>
#define COLOR_RED		SetConsoleTextAttribute(hConsole, FOREGROUND_RED)
#define COLOR_GREEN		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN)
#define COLOR_YELLOW	SetConsoleTextAttribute(hConsole,\
						FOREGROUND_RED | FOREGROUND_GREEN)
#define COLOR_RESET		SetConsoleTextAttribute(hConsole,\
						FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)
HANDLE hConsole;

#else
#define COLOR_RED 	 printf("\033[31m")
#define COLOR_GREEN  printf("\033[32m")
#define COLOR_YELLOW printf("\033[33m")
#define COLOR_RESET  printf("\033[0m" )
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

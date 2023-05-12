#include "helpers.c"

int main(void)
{
	struct Game G;
	struct Move move;
	char first_player = USER;

	// Windows specific configurations
    #ifdef _WIN32
	    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	    UINT old_cp = GetConsoleOutputCP();
	    SetConsoleOutputCP(CP_UTF8); // Set console code page to UTF-8
    #endif

	do {
		G = game_init(first_player);
		print_board(G);

		do {
			move = (G.turn == USER) ? user_move(G) : computer_move(G);
			G = board_update(G, move);
			print_board(G);
		} while (!game_complete(&G));

		print_result(G);

	} while (rematch());

	// Reset console code page to original value (Windows)
	#ifdef _WIN32
		SetConsoleOutputCP(old_cp);
	#endif

	return 0;
}


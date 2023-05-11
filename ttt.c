#include "helpers.c"

int main(int argc, char *argv[])
{
	struct Game G;
	struct Move move;
	char first_player = USER;

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

	return 0;
}


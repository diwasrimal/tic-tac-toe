#include "helpers.h"


struct Game game_init(char first_player)
{
	struct Game G;
	G.winner = '\0';
	G.tied = false;
	G.turn = first_player;

	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			G.board[r][c] = EMPTY;
		}
	}

	return G;
}

struct Game board_update(struct Game G, struct Move m)
{
	struct Game new;

	// Copy the board and make the move
	for (int r = 0; r < 3; r++)
		for (int c = 0; c < 3; c++)
			new.board[r][c] = G.board[r][c];

	new.board[m.row][m.col] = G.turn;
	new.turn = (G.turn == USER) ? COMP : USER;
	return new;
}

void print_board(struct Game G)
{
    {
        printf("\n");
        printf("\t\t    1   2   3   \n");
        printf("\t\t  ┌───┬───┬───┐  \n");
    }
    
    for (int r = 0; r < 3; r++) {
        printf("\t\t%d │ ", r + 1);

        for (int c = 0; c < 3; c++) {
            if (G.board[r][c] == USER) COLOR_GREEN;
            if (G.board[r][c] == COMP) COLOR_RED;

            printf("%c", G.board[r][c]);
            COLOR_RESET;
            printf(" │ ");

        } printf("\n");

        if (r <= 1) 
        printf("\t\t  ├───┼───┼───┤  \n");
    }

    {
    	printf("\t\t  └───┴───┴───┘  \n");
    	printf("\n");
    }
}

struct Move user_move(struct Game G)
{
	struct Move m;
	char ch;

    do {
    	int i = 0;
        printf("Move (#row #col): ");
        while ((ch = getchar()) != '\n') {
            if (isdigit(ch)) {
                if (i == 0) m.row = ch - '0' - 1;	// -1 to match indexing of board
                if (i == 1) m.col = ch - '0' - 1;
                i++;
            }
        }
    } while (m.row < 0 || m.row > 2 ||
	    	m.col < 0 || m.col > 2 ||
	    	G.board[m.row][m.col] != EMPTY);

	return m;
}

struct Move computer_move(struct Game G)
{
	struct Move best_move, curr_move, *pmoves;
	int total_moves, curr_value, best_value;

	pmoves = possible_moves(G, &total_moves);
	printf("Computer moving...\n");

	// Computer tries to maximize the outcome
	best_value = MIN;

	for (int i = 0; i < total_moves; i++) {
		curr_move = pmoves[i];
		curr_value = minimax(board_update(G, curr_move));

		if (curr_value > best_value) {
			best_value = curr_value;
			best_move = curr_move;
		}

		// Best possible max value
		if (best_value == 1)
			break;
	}

	free(pmoves);
	return best_move;
}

int minimax(struct Game G)
{
	if (game_complete(&G))
		return board_value(G);

	int total_moves, curr_value, best_value;
	struct Move curr_move, *pmoves;

	pmoves = possible_moves(G, &total_moves);

	// Computer is maximizing player
	if (G.turn == COMP) {
		best_value = MIN;

		for (int i = 0; i < total_moves; i++) {
			curr_move = pmoves[i];
			curr_value = minimax(board_update(G, curr_move));

			if (curr_value > best_value)
				best_value = curr_value;

			// Best possible value for maximixing player
			if (best_value == 1)
				break;
		}
	}

	// User is minimizing player
	else {
		best_value = MAX;

		for (int i = 0; i < total_moves; i++) {
			curr_move = pmoves[i];
			curr_value = minimax(board_update(G, curr_move));

			if (curr_value < best_value)
				best_value = curr_value;

			// Best possible value for maximixing player
			if (best_value == -1)
				break;
		}
	}

	free(pmoves);
	return best_value;
}

int board_value(struct Game G)
{
	if (G.tied) return 0;
	if (G.winner == COMP) return 1;
	if (G.winner == USER) return -1;
}

struct Move *possible_moves(struct Game G, int *count)
{
	int i = -1;
	struct Move *moves = malloc(sizeof(struct Move) * 9);

	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			if (G.board[r][c] == EMPTY) {
				++i;
				moves[i].row = r;
				moves[i].col = c;
			}
		}
	}

	*count = i + 1;
	return moves;
}

bool game_complete(struct Game *G)
{
	// Game will complete in case of win, or a tie.
	char (*b)[3] = G->board;

	// Check matching rows
	for (int r = 0; r < 3; r++) {
		if (b[r][0] == b[r][1] && b[r][0] == b[r][2] && b[r][0] != EMPTY) {
			G->winner = b[r][0];
			return true	;
		}
	}

	// Check matching cols
	for (int c = 0; c < 3; c++) {
		if (b[0][c] == b[1][c] && b[0][c] == b[2][c] && b[0][c] != EMPTY) {
			G->winner = b[0][c];
			return true;
		}
	}

	// Matching diagonals
	if (((b[0][0] == b[1][1] && b[2][2] == b[1][1]) ||
		 (b[0][2] == b[1][1] && b[2][0] == b[1][1])) &&
		b[1][1] != EMPTY) {
		G->winner = b[1][1];
		return true;
	}

	// Game ties when every box is filled, but nobody wins
	for (int r = 0; r < 3; r++)
		for (int c = 0; c < 3; c++)
			if (b[r][c] == EMPTY)  // Empty box remaining
				return false;

	G->tied = true;
	return true;
}

void print_result(struct Game G)
{
	if (G.winner == COMP) {
		COLOR_RED;
		printf("\nComputer wins!\n");
	}
	else if (G.winner == USER) {
		COLOR_GREEN;
		printf("\nYou win!\n");
	}
	else if (G.tied) {
		COLOR_YELLOW;
		printf("\nTIE!\n");
	}
	COLOR_RESET;
}

bool rematch(void)
{
	char r, ch;

	printf("Play Again? [y/n]: ");
	r = getchar();
	while ((ch = getchar()) != '\n');

	return (r == 'y');
}

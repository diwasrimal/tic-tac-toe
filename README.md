# Tic Tac Toe

### Clone and build
```sh
git clone https://github.com/diwasrimal/tic-tac-toe.git
cd tic-tac-toe
```
I suppose that you have `gcc` installed.
```sh
gcc -std=c11 -o ttt ttt.c
```
Run using `./ttt` or `.\ttt.exe` depending on your system.

### Working
* `X` is computer (maximizing player).
* `O` is user (minimizing player).
* `USER` goes first by default.

| Function             | Use                                                                                        |
|----------------------|--------------------------------------------------------------------------------------------|
| `game_init()`        | Initializes the game board and selects the first player.                                   |
| `print_board()`      | Prints a colorful board.                                                                   |
| `board_update()`     | Updates the board with given move.                                                         |
| `possible_moves()`   | Returns all possible moves for a given board.                                              |
| `game_complete()`    | Checks if game has ended and sets `winner` or `tied` variables accordingly.                |
| `user_move()`        | Prompts user for a move and returns that move.                                             |
| `computer_move()`    | Uses `minimax()` to find the best possible computer move.                                  |
| `board_value()`      | Gives out the numerical value of board after the game ends (used by `minimax()`).          |
| `minimax()`          | Runs a recursive adversarial algorithm to find the best possible move for a given board.   |
| `print_result()`     | Prints out the winner, or declares a tie.                                                  |
| `rematch()`          | Asks for rematch                                                                           |

#### Pseudocode for minimax

```
function minimax(board):
    if game_complete(board):
        return board_value(board)

    if player is maximizing:
        best_value = -infinity
        for each move in possible moves:
            new_board = update_board(board, move)
            best_value = max(new_board, best_value)

    else if player is minimizing:
        best_value = infinity
        for each move in possible moves:
            new_board = update_board(board, move)
            best_value = min(new_board, best_value)

    return best_value
```

Note that there must be a way to differentiate maximizing and minimizing
player while running the minimax algorithm. I've used `G.turn` to know if its
`COMP`'s turn (maximizing) or `USER`'s turn (minimizing).

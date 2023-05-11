### Players
* `X` is computer, and the maximizing player
* `O` is user, and the minimizing player
* `O` goes first


### Functions:
* `game_init()`: Initializes the game board and selects the first player.
* `print_board()`: Prints a colorful board.
* `board_update()`: Updates the board with given move.
* `possible_moves()`: Returns all possible moves for a board.
* `game_complete()`: Checks if game has ended and sets `winner` or `tied` boolean.
* `board_value()`: Gives out the numerical value of terminated board.
* `max_value()`: Returns the max value possible for a given board.
* `min_value()`: Returns the min value possible for a given board.
* `minimax()`: Runs the minimax algorithm on updated board.
* `print_result()`: Prints out the winner, or declares a tie.


#### Maximizing Algorithm:

```
function max_value(board):
	if game_complete(board):
		return board_value(board)

	highest_val = -inf
	for each move in possible_moves:
		highest_val = max(highest_val, min_value(update_board(board, move)))
```

#### Minimizing Algorithm:
```
function min_value(board):
	if game_complete(board):
		return board_value(board)

	lowest_val = inf
	for each move in possible_moves:
		lowest_val = min(lowest_val, max_value(update_board(board, move)))
```

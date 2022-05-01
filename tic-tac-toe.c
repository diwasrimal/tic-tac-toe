#include "helpers.c"

/* algorithm of this game
1. make GUI of block
2. update block with spaces
3. keep doing these until game finishes ;
        take user input
            take rows and cols
            insert 'x' at that place if empty
        take computer's input
            find the most optimal move 
                if you can win, make the winning move
                else block user from winning
            else just move randomly
    upadate block
    if somebody wins, quit 
    else keep playing
    goto step 3
end */

// MAIN
int main(void)
{
    // seeding time
    srand(time(0));
    
	newBlock();
    updateBlock();

    // first round
    userInput();
    fstCompInput();
    updateBlock();

	do
	{
    	repeatInputs();
	}
	while(winner() == ' ');			// nobody has won, so play another round

  	// somebody other than ' ' has won
  	printWinner(winner());
}

void userInput()
{
    // prompt user for his move
    int row, col;
    printf("Where do you want X ? (#row-#col) ");
	scanf("%d-%d", &row,&col);
    row--; col--;

    if(validMove(row, col))
        block[row][col] =  PLAYER;
    else
    {
        printf("\nINVALID MOVE!!!\n");
        userInput();
    }
}

void fstCompInput()
{
    // if the player didn't take the middle, well, we'll take it.
    // if the player took the middle, a move at corner sounds good.
    if(block[1][1] == ' ') {
        block[1][1] = COMPUTER;
        return;
    }
    int cornerIndices[4][2] = {{0,0},{0,2},{2,0},{2,2}};
    int randCorner = rand() % 4;
    int idx1 = cornerIndices[randCorner][0];
    int idx2 = cornerIndices[randCorner][1];
    block[idx1][idx2] == ' ' ? block[idx1][idx2] = COMPUTER: fstCompInput();
    
}

void randomInput()
{
    int randRow = rand() % 3;
    int randCol = rand() % 3;

    if(block[randRow][randCol] == ' ')
    	block[randRow][randCol] = COMPUTER;
    else if(freeSpaces() == 0)
        return;
    else
        randomInput();
}

void computerInput()
{
    if(canWin(COMPUTER)) return;
    if(canWin(PLAYER)) return;
    // both can't win then,
    randomInput();
}

int check(char checkType, int pos, char playerType)
    {
    char arr[3];
    // check for rows
    if(checkType == 'r')
        for(int i = 0; i < 3; i++)
            arr[i] = block[pos][i];    

    // check for cols
    if(checkType == 'c')
        for(int i = 0; i < 3; i++)
            arr[i] = block[i][pos];

    // check for diags
    if(checkType == 'm')                      // main diagonal(top left to bottom right)
        for(int i = 0; i < 3; i++)
            arr[i] = block[i][i];
    else if(checkType == 'o')                   // other diagonal
        for(int i = 0; i < 3; i++)
            arr[i] = block[i][2-i];

    bool zero = (arr[1] == playerType && arr[2] == playerType && arr[0] == ' ');
    bool one = (arr[0] == playerType && arr[2] == playerType && arr[1] == ' ');
    bool two = (arr[0] == playerType && arr[1] == playerType && arr[2] == ' ');

    if(zero) return 0;
    if(one) return 1;
    if(two) return 2;
    return -1;          // no right place found  
}

char winner()
{
    // matching rows
    for(int row = 0; row < 3; row++)
        if(block[row][0] == block[row][1] && block[row][0] == block[row][2])
            return block[row][0];

    // matching columns
    for(int col = 0; col < 3; col++)
        if(block[0][col] == block[1][col] && block[0][col] == block[2][col])
            return block[0][col];

    // matching diagonals
    if ( (block[0][0] == block[1][1] && block[0][0] == block[2][2]) || (block[0][2] == block[1][1] && block[0][2] == block[2][0]) )
        return block[1][1];

    // no winner until the end of all freespaces
    else if(freeSpaces() == 1)
        return 'T';				// game has tied
    else
        return ' ';            //  nobody wins
}

void repeatInputs()
{
    userInput();
    computerInput();
    updateBlock();
}

bool canWin(char playerType)
{
    int goodIndex;

    // go through every row
    for(int thisRow = 0; thisRow < 3; thisRow++)
    {
        // check if this row can make user win
        goodIndex = check('r', thisRow, playerType);
        if(goodIndex != -1) {
            block[thisRow][goodIndex] = COMPUTER;
            return true;
        }
    }
    
    // go through every col
    for(int thisCol = 0; thisCol < 3; thisCol++)
    {
        // check if this col can make user win
        goodIndex = check('c', thisCol, playerType);
        if(goodIndex != -1) {
            block[goodIndex][thisCol] = COMPUTER;
            return true;
        } 
    }
    // check diagonals
    goodIndex = check('m', 0, playerType);           // checking for main diagonal
    if(goodIndex != -1){
        block[goodIndex][goodIndex] = COMPUTER;
        return true;
    }
    goodIndex = check('o', 0, playerType);           // checking another diagonal
    if(goodIndex != -1){
        block[goodIndex][2-goodIndex] = COMPUTER;
        return true;
    }

    // if nothing matching
    return false;
}

void newBlock()
{
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
        	block[i][j] = ' ';
}


void updateBlock()
{
    printf("\n------------------------------------------------------------------------\n\n");
    printf("\t\t   ____________________\n");
    printf("\t\t  |  ________________  |\n");
    printf("\t\t  | |                | |\n");
    printf("\t\t  | |  #  1  2  3    | |\n");
    printf("\t\t  | |  1 %c | %c | %c   | |\n", block[0][0], block[0][1], block[0][2]);
    printf("\t\t  | |   ---|---|---  | |\n");
    printf("\t\t  | |  2 %c | %c | %c   | |\n", block[1][0], block[1][1], block[1][2]);
    printf("\t\t  | |   ---|---|---  | |\n");
    printf("\t\t  | |  3 %c | %c | %c   | |\n", block[2][0], block[2][1], block[2][2]);
    printf("\t\t  | |________________| |\n");
    printf("\t\t  |____________________|\n");
    printf("\n\n------------------------------------------------------------------------\n\n");
}

int freeSpaces()
{
	int spaces = 9;
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			if(block[i][j] != ' ')
				spaces--;
		}
	}
	return spaces;
}

bool validMove(int row, int col)
{
    return (block[row][col] == ' ' && row < 3 && row >= 0 &&  col < 3 && col >= 0);
}

void printWinner(char winnerName)
{
    if (winnerName == 'O')
    	printf("COMPUTER WINS!!!");
    else if (winnerName == 'X')
    	printf("YOU WIN!!!");
    else
    	printf("TIE!");
    
    // ask if he wants to play again
    printf("\n\nPlay Again (y/n) ? "); char c = getche();
    if(c == 'y')
    {
    	system("cls");
    	main();
	}
    else
    {
		printf("\n\nThanks for playing! \n\n");
    	return;
	}
    
}



#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>

char block[3][3];
const char PLAYER = 'X';
const char COMPUTER = 'O';

// functions
void newBlock();
void updateBlock();
void userInput();
void randomInput();
void fstCompInput();
void printWinner(char winnerName);
void computerInput();
void repeatInputs();
int freeSpaces();
int check(char checkType, int pos, char playerType);
char winner();
bool validMove(int row, int col);
bool canWin(char winnerType);


#ifndef WINS_H_
#define WINS_H_

#define ROWS 6
#define COLS 7

void initGrid();
void board();
void fillBox();
void pick();
int checkWin(char coin);
int checkStreak(char coin, int *i, int *j);
int checkTie();
void preventWin(int i, int j);
void tryToWin(int i, int j);

char grid[ROWS][COLS];
char visited[6][7];
char header[] = "  A   B   C   D   E   F   G  ";
char separator[] = "|---|---|---|---|---|---|---|";
int box = 0;
char coin = 'X';
int rowFlag = 0;
int colFlag = 0;
int posDFlag = 0;
int negDFlag = 0;
char player = 'X';
char comp = 'O';

#endif
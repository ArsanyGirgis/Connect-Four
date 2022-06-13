#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "wins.h"

void initGrid()
{
    // set grid as empty character:
    int i, j;

    for (i = 0; i < ROWS; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            grid[i][j] = ' ';    // designing the board as 2-dim array
            visited[i][j] = ' '; // marking pattern already taken care of
        }
    }
}

void board()
{
    // prints current game:
    printf("%s\n", header);
    printf("%s\n", separator);

    int i, j;

    for (i = 0; i < ROWS; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            printf("| %c ", grid[i][j]);
        }
        // complete the shape of the game
        printf("|\n");
        printf("%s\n", separator);
    }
}

void fillBox()
{
    /*user doesn't need t enter the exact
    location in terms of [row][colomn]*/
    int level;

    for (level = ROWS - 1; level >= 0; level--)
    {
        // bottom level is ROWS-1
        if (grid[level][box] == ' ')
        {
            grid[level][box] = coin;
            break;
        }
    }
}

void pick()
{
    char c;
    // the user only needs a letter for choosing
    while (1)
    {
        printf("\npick box: ");
        scanf(" %c", &c);
        switch (c)
        {
        case 'A':
        case 'a':
            box = 0;
            break;
        case 'B':
        case 'b':
            box = 1;
            break;
        case 'C':
        case 'c':
            box = 2;
            break;
        case 'D':
        case 'd':
            box = 3;
            break;
        case 'E':
        case 'e':
            box = 4;
            break;
        case 'F':
        case 'f':
            box = 5;
            break;
        case 'G':
        case 'g':
            box = 6;
            break;

        default:
            box = 404;
            printf("\nWrong letter! Try again.\n\n");
            board();
        }
        // break while as right letter is picked
        if ((box >= 0 && box <= 6) && (grid[0][box] == ' '))
        {
            fillBox();
            coin = (coin == 'X') ? 'O' : 'X';
            break;
        }
        if ((grid[0][box] == 'X') || (grid[0][box] == 'O'))
            printf("Column is full,");
    }
}
int checkWin(char coin)
{
    // wins (returns 1) when 4 coins are row, column or diagonal connected

    /*each row has 4 different combinations to win
    to take into account the limits of the board
    counts if found from first until fourth

    */
    int r, c, itr;
    int count;
    int combinations = 4; // COLS - 3

    for (r = 0; r < ROWS; ++r)
    {
        for (c = 0; c < combinations; ++c)
        {
            count = 0;
            for (itr = 0; itr < 4; ++itr)
            {
                if (grid[r][c + itr] == coin)
                    count++;
            }
            if (count == 4)
                return 1;
        }
    }

    /*
    each column has 3 different combinations to connect 4

    */

    combinations = 3; // ROWS - 3

    for (c = 0; c < COLS; ++c)
    {
        for (r = 0; r < combinations; ++r)
        {
            count = 0;
            for (itr = 0; itr < 4; ++itr)
            {
                if (grid[r + itr][c] == coin)
                    count++;
            }
            if (count == 4)
                return 1;
        }
    }

    // positive sloped diagonals view
    for (r = 3; r < ROWS; ++r)
    {
        for (c = 0; c < COLS - 3; ++c)
        {
            count = 0;
            for (itr = 0; itr < 4; ++itr)
            {
                if (grid[r - itr][c + itr] == coin)
                    count++;
            }
            if (count == 4)
                return 1;
        }
    }

    // negative sloped diagonals view
    for (r = 0; r < ROWS - 3; ++r)
    {
        for (c = 0; c < COLS - 3; ++c)
        {
            count = 0;
            for (itr = 0; itr < 4; ++itr)
            {
                if (grid[r + itr][c + itr] == coin)
                    count++;
            }
            if (count == 4)
                return 1;
        }
    }

    return 0;
}

int checkStreak(char coin, int *i, int *j)
{

    int r, c, itr;
    int count;
    int iIndex = (int)*i;
    int jIndex = (int)*j;

    for (r = 0; r < ROWS; ++r)
    {
        for (c = 0; c < COLS; ++c)
        {
            count = 0;
            for (itr = 0; itr < 4; ++itr)
            {
                if (grid[r][c + itr] == coin)
                    count++;
            }

            if (count == 3 && grid[r][c] == coin && grid[r][c + 1] == coin && grid[r][c + 2] == coin && visited[iIndex][jIndex] != 'r')
            {
                rowFlag = 3;
                *i = r;
                *j = c;
                return 3;
            }
            else if (count == 2 && grid[r][c] == coin && grid[r][c + 1] == coin && visited[iIndex][jIndex] != 'r')
            {
                rowFlag = 2;
                *i = r;
                *j = c;
                return 2;
            }
        }
    }
    for (c = 0; c < COLS; ++c)
    {
        for (r = 0; r < ROWS; ++r)
        {
            count = 0;
            for (itr = 0; itr < 4; ++itr)
            {
                if (grid[r + itr][c] == coin)
                    count++;
            }
            // order important
            if (count == 3 && grid[r][c] == coin && (grid[r + 1][c] == coin) && (grid[r + 2][c] == coin) && visited[iIndex][jIndex] != 'c')
            {
                colFlag = 3;
                *i = r;
                *j = c;
                return 3;
            }
            else if ((count == 2) && (grid[r][c] == coin) && (grid[r + 1][c] == coin) && visited[iIndex][jIndex] != 'c')
            {
                colFlag = 2;
                *i = r;
                *j = c;
                return 2;
            }
        }
    }

    // positive sloped diagonals view
    for (r = 3; r < ROWS; ++r)
    {
        for (c = 0; c < COLS; ++c)
        {
            count = 0;
            for (itr = 0; itr < 4; ++itr)
            {
                if (grid[r - itr][c + itr] == coin)
                    count++;
            }

            if (count == 3 && grid[r][c] == coin && grid[r - 1][c + 1] == coin && grid[r - 2][c + 2] == coin)
            {
                posDFlag = 3;
                *i = r;
                *j = c;
                return 3;
            }
            else if (count == 2 && grid[r][c] == coin && grid[r - 1][c + 1] == coin)
            {
                posDFlag = 2;
                *i = r;
                *j = c;
                return 2;
            }
        }
    }

    // negative sloped diagonals view
    for (r = 0; r < ROWS - 3; ++r)
    {
        for (c = 0; c < COLS - 3; ++c)
        {
            count = 0;
            for (itr = 0; itr < 4; ++itr)
            {
                if (grid[r + itr][c + itr] == coin)
                    count++;
            }

            if (count == 3 && grid[r][c] == coin && grid[r + 1][c + 1] == coin && grid[r + 2][c + 2] == coin && visited[iIndex][jIndex] != 'n')
            {
                negDFlag = 3;
                *i = r;
                *j = c;
                return 3;
            }
            else if (count == 2 && grid[r][c] == coin && grid[r + 1][c + 1] == coin && visited[iIndex][jIndex] != 'n')
            {
                negDFlag = 2;
                *i = r;
                *j = c;
                return 2;
            }
        }
    }
    if (count == 1)
        return 1;

    return 0;
}

int checkTie()
{
    int space = 0;
    for (int i = 0; i < ROWS; i++)
    {
        for (int j; j < COLS; j++)
        {
            if (grid[i][j] == ' ')

                space = 1;

            else
                space = 0;
        }
    }
    if (space == 0)
        return 1;

    return 0;
}

void preventWin(int i, int j)
{

    //  position of box
    // printf("%d %d %d %d %d %d  ", i, j, box, checkStreak('X', &i, &j), rowFlag, colFlag);
    if (checkStreak(player, &i, &j) == 3)
    {

        // row
        if (rowFlag == 3 && visited[i][j] != 'r')
        {
            if (i + 1 <= 5)
            {
                if ((grid[i + 1][j + 3] != ' ') && (grid[i][j + 3] == ' '))
                {
                    box = j + 3;
                    // printf("%d %d %d u1", i, j, box);
                    fillBox();
                    coin = (coin == 'X') ? 'O' : 'X';
                    rowFlag = 0;
                    visited[i][j] = 'r';
                }
                else
                {
                    if (j - 1 >= 0)
                    {
                        if ((grid[i][j - 1] == ' ') && (grid[i - 1][j - 1] != ' '))
                        {
                            // printf("\nIm Herer3\n");
                            box = j - 1;
                            // printf("%d %d %d u2", i, j, box);
                            fillBox();
                            coin = (coin == 'X') ? 'O' : 'X';
                            rowFlag = 0;
                            visited[i][j] = 'r';
                        }
                        else
                        {
                            // printf("rand1");
                            srand((unsigned)time(NULL));
                            box = rand() % 7; // 7 columns
                            // printf("%d %d %d %d %d", i, j, box, checkStreak('X', &i, &j), rowFlag);
                            fillBox();
                            coin = (coin == 'X') ? 'O' : 'X';
                        }
                    }
                    else
                    {
                        // printf("rand2");
                        srand((unsigned)time(NULL));
                        box = rand() % 7; // 7 columns
                        // printf("%d %d %d %d %d", i, j, box, checkStreak('X', &i, &j), rowFlag);
                        fillBox();
                        coin = (coin == 'X') ? 'O' : 'X';
                    }
                }
            }
            else
            {
                if (grid[i][j + 3] == ' ')
                {
                    // printf("\nIm Herenr\n");
                    box = j + 3;
                    // printf("%d %d %d", i, j, box);
                    fillBox();
                    coin = (coin == 'X') ? 'O' : 'X';
                    rowFlag = 0;
                    visited[i][j] = 'r';
                }
                else if (j - 1 >= 0)
                {
                    if ((grid[i][j - 1] == ' ') && (grid[i + 1][j - 1] != ' '))
                    {
                        // printf("\nIm Herer3\n");
                        box = j - 1;
                        // printf("%d %d %d", i, j, box);
                        fillBox();
                        coin = (coin == 'X') ? 'O' : 'X';
                        rowFlag = 0;
                        visited[i][j] = 'r';
                    }
                    else
                    {
                        // printf("rand3");
                        srand((unsigned)time(NULL));
                        box = rand() % 7; // 7 columns
                        // printf("%d %d %d %d %d", i, j, box, checkStreak('X', &i, &j), rowFlag);
                        fillBox();
                        coin = (coin == 'X') ? 'O' : 'X';
                    }
                }
                else
                {
                    // random
                    // printf("rand4 ");
                    srand((unsigned)time(NULL));
                    box = rand() % 7; // 7 columns
                    // printf("%d %d %d %d %d", i, j, box, checkStreak('X', &i, &j), rowFlag);
                    fillBox();
                    coin = (coin == 'X') ? 'O' : 'X';
                }
            }
        }
        // colomn
        else if (colFlag == 3 && visited[i][j] != 'c')
        {
            // printf("col swap2");
            box = j;
            fillBox();
            coin = (coin == 'X') ? 'O' : 'X';
            colFlag = 0;
            visited[i][j] = 'c';
        }
        // diagonal
        else if (posDFlag == 3 && visited[i][j] != 'p')
        {
            if (grid[i - 3][j + 3] == ' ' && grid[i - 2][j + 3] != ' ')
            {
                // printf("pd swap2");
                box = j + 3;
                fillBox();
                coin = (coin == 'X') ? 'O' : 'X';
                posDFlag = 0;
                visited[i][j] = 'p';
            }
            else
            {
                // random
                // printf("rand41 ");
                srand((unsigned)time(NULL));
                box = rand() % 7; // 7 columns
                // printf("%d %d %d %d %d", i, j, box, checkStreak('X', &i, &j), rowFlag);
                fillBox();
                coin = (coin == 'X') ? 'O' : 'X';
            }
        }
        else if (negDFlag == 3 && visited[i][j] != 'n')
        {
            if (grid[i + 3][j + 3] == ' ' && grid[i + 2][j + 3] == ' ')
            {
                // printf("nd swap4");
                box = j + 3;
                fillBox();
                coin = (coin == 'X') ? 'O' : 'X';
                negDFlag = 0;
                visited[i][j] = 'n';
            }
            else
            {
                // random
                // printf("rand42 ");
                srand((unsigned)time(NULL));
                box = rand() % 7; // 7 columns
                // printf("%d %d %d %d %d", i, j, box, checkStreak('X', &i, &j), rowFlag);
                fillBox();
                coin = (coin == 'X') ? 'O' : 'X';
            }
        }
    }

    else if (checkStreak(player, &i, &j) == 2)
    {
        // row
        if (rowFlag == 2 && visited[i][j] != 'r')
        {
            if (i + 1 <= 5)
            {
                if (grid[i + 1][j + 2] != ' ' && grid[i][j + 2] == ' ' && posDFlag == 0)
                {
                    // printf("\nIm Here 2row\n");
                    box = j + 2;
                    // printf("%d %d %d", i, j, box);
                    fillBox();
                    coin = (coin == 'X') ? 'O' : 'X';
                    rowFlag = 0;
                    visited[i][j] = 'r';
                }
                else
                {
                    if (j - 1 >= 0)
                    {
                        if ((grid[i][j - 1] == ' ') && (grid[i + 1][j - 1] != ' '))
                        {
                            // printf("\n left 2 \n");
                            box = j - 1;
                            // printf("%d %d %d", i, j, box);
                            fillBox();
                            coin = (coin == 'X') ? 'O' : 'X';
                            rowFlag = 0;
                            visited[i][j] = 'r';
                        }
                        else
                        {
                            // printf("rand5 ");
                            srand((unsigned)time(NULL));
                            box = rand() % 7; // 7 columns
                            // printf("%d %d %d %d %d", i, j, box, checkStreak('X', &i, &j), rowFlag);
                            fillBox();
                            coin = (coin == 'X') ? 'O' : 'X';
                        }
                    }
                    else
                    {
                        // printf("rand6 ");
                        srand((unsigned)time(NULL));
                        box = rand() % 7; // 7 columns
                        // printf("%d %d %d %d %d", i, j, box, checkStreak('X', &i, &j), rowFlag);
                        fillBox();
                        coin = (coin == 'X') ? 'O' : 'X';
                    }
                }
            }
            else
            {
                if (grid[i][j + 2] == ' ' && visited[i][j] == 'r')
                {
                    // printf("\nIm Here bottom\n");
                    box = j + 2;
                    // printf("%d %d %d", i, j, box);
                    fillBox();
                    coin = (coin == 'X') ? 'O' : 'X';
                    rowFlag = 0;
                    visited[i][j] = 'r';
                }
                else if (j - 1 >= 0)
                {
                    if (grid[i][j - 1] == ' ')
                    {
                        // printf("\n left 2 bott \n");
                        box = j - 1;
                        // printf("%d %d %d", i, j, box);
                        fillBox();
                        coin = (coin == 'X') ? 'O' : 'X';
                        rowFlag = 0;
                        visited[i][j] = 'r';
                    }
                    else
                    {
                        // printf("rand7");
                        srand((unsigned)time(NULL));
                        box = rand() % 7; // 7 columns
                        // printf("%d %d %d %d %d", i, j, box, checkStreak('X', &i, &j), rowFlag);
                        fillBox();
                        coin = (coin == 'X') ? 'O' : 'X';
                    }
                }
                else
                {
                    // printf("rand8 ");
                    srand((unsigned)time(NULL));
                    box = rand() % 7; // 7 columns
                    // printf("%d %d %d %d %d", i, j, box, checkStreak('X', &i, &j), rowFlag);
                    fillBox();
                    coin = (coin == 'X') ? 'O' : 'X';
                }
            }
        }
        // colomn
        else if (colFlag == 2 && visited[i][j] != 'c')
        {
            // printf("col swap");
            //  box = j;
            fillBox();
            coin = (coin == 'X') ? 'O' : 'X';
            colFlag = 0;
            visited[i][j] = 'c';
        }
        // diagonal
        else if (posDFlag == 2 && visited[i][j] != 'p')
        {
            if (grid[i - 2][j + 2] == ' ' && grid[i - 1][j + 2] != ' ')
            {
                // printf("pd swap1");
                box = j + 2;
                fillBox();
                coin = (coin == 'X') ? 'O' : 'X';
                posDFlag = 0;
                visited[i][j] = 'p';
            }
            else
            {
                // printf("rand81 ");
                srand((unsigned)time(NULL));
                box = rand() % 7; // 7 columns
                // printf("%d %d %d %d %d", i, j, box, checkStreak('X', &i, &j), rowFlag);
                fillBox();
                coin = (coin == 'X') ? 'O' : 'X';
            }
        }
        else if (negDFlag == 2 && visited[i][j] != 'n')
        {
            if (grid[i + 2][j + 2] == ' ' && grid[i + 1][j + 2] == ' ')
            {
                // printf("nd swap1");
                box = j + 2;
                fillBox();
                coin = (coin == 'X') ? 'O' : 'X';
                negDFlag = 0;
                visited[i][j] = 'n';
            }
            else
            {
                // printf("rand82 ");
                srand((unsigned)time(NULL));
                box = rand() % 7; // 7 columns
                // printf("%d %d %d %d %d", i, j, box, checkStreak('X', &i, &j), rowFlag);
                fillBox();
                coin = (coin == 'X') ? 'O' : 'X';
            }
        }
        else
        {
            // random
            // printf("rand9 ");
            srand((unsigned)time(NULL));
            box = rand() % 7; // 7 columns
            // printf("%d %d %d %d %d", i, j, box, checkStreak('X', &i, &j), rowFlag);
            fillBox();
            coin = (coin == 'X') ? 'O' : 'X';
        }
    }

    else
    {
        // random
        // printf("rand10 ");
        srand((unsigned)time(NULL));
        box = rand() % 7; // 7 columns
        // printf("%d %d %d %d %d", i, j, box, checkStreak('X', &i, &j), rowFlag);
        fillBox();
        coin = (coin == 'X') ? 'O' : 'X';
    }
}

void tryToWin(int i, int j)
{
    //  position of box
    // printf("%d %d %d %d %d %d  ", i, j, box, checkStreak('X', &i, &j), rowFlag, colFlag);
    if (checkStreak(comp, &i, &j) == 3)
    {

        // row
        if (rowFlag == 3)
        {
            if (i + 1 <= 5)
            {
                if (grid[i][j + 3] == ' ')
                {
                    box = j + 3;
                    // printf("%d %d %d u1", i, j, box);
                    fillBox();
                    coin = (coin == 'X') ? 'O' : 'X';
                    rowFlag = 0;
                }
                else
                {
                    if (j - 1 >= 0)
                    {
                        if (grid[i][j - 1] == ' ')
                        {
                            // printf("\nIm Herern3\n");
                            box = j - 1;
                            // printf("%d %d %d u2", i, j, box);
                            fillBox();
                            coin = (coin == 'X') ? 'O' : 'X';
                            rowFlag = 0;
                        }
                        else
                        {
                            // printf("rand1");
                            srand((unsigned)time(NULL));
                            box = rand() % 7; // 7 columns
                            // printf("%d %d %d %d %d", i, j, box, checkStreak('X', &i, &j), rowFlag);
                            fillBox();
                            coin = (coin == 'X') ? 'O' : 'X';
                        }
                    }
                    else
                    {
                        // printf("rand2");
                        srand((unsigned)time(NULL));
                        box = rand() % 7; // 7 columns
                        // printf("%d %d %d %d %d", i, j, box, checkStreak('X', &i, &j), rowFlag);
                        fillBox();
                        coin = (coin == 'X') ? 'O' : 'X';
                    }
                }
            }
            else
            {
                if (grid[i][j + 3] == ' ')
                {
                    // printf("\nIm Herennr\n");
                    box = j + 3;
                    // printf("%d %d %d", i, j, box);
                    fillBox();
                    coin = (coin == 'X') ? 'O' : 'X';
                    rowFlag = 0;
                }
                else if (j - 1 >= 0)
                {
                    if (grid[i][j - 1] == ' ')
                    {
                        // printf("\nIm Herer3d\n");
                        box = j - 1;
                        // printf("%d %d %d", i, j, box);
                        fillBox();
                        coin = (coin == 'X') ? 'O' : 'X';
                        rowFlag = 0;
                        visited[i][j] = 'r';
                    }
                    else
                    {
                        // printf("rand3");
                        srand((unsigned)time(NULL));
                        box = rand() % 7; // 7 columns
                        // printf("%d %d %d %d %d", i, j, box, checkStreak('X', &i, &j), rowFlag);
                        fillBox();
                        coin = (coin == 'X') ? 'O' : 'X';
                    }
                }
                else
                {
                    // random
                    // printf("rand4 ");
                    srand((unsigned)time(NULL));
                    box = rand() % 7; // 7 columns
                    // printf("%d %d %d %d %d", i, j, box, checkStreak('X', &i, &j), rowFlag);
                    fillBox();
                    coin = (coin == 'X') ? 'O' : 'X';
                }
            }
        }
        // colomn
        else if (colFlag == 3)
        {
            // printf("col swadp2");
            box = j;
            fillBox();
            coin = (coin == 'X') ? 'O' : 'X';
            colFlag = 0;
        }
        // diagonal
        else if (posDFlag == 3)
        {
            if (grid[i - 3][j + 3] == ' ' && grid[i - 2][j + 3] != ' ')
            {
                // printf("pd swap2");
                box = j + 3;
                fillBox();
                coin = (coin == 'X') ? 'O' : 'X';
                posDFlag = 0;
            }
            else
            {
                // random
                // printf("rand41 ");
                srand((unsigned)time(NULL));
                box = rand() % 7; // 7 columns
                // printf("%d %d %d %d %d", i, j, box, checkStreak('X', &i, &j), rowFlag);
                fillBox();
                coin = (coin == 'X') ? 'O' : 'X';
            }
        }
        else if (negDFlag == 3)
        {
            if (grid[i + 3][j + 3] == ' ' && grid[i + 2][j + 3] == ' ')
            {
                // printf("nd swap4");
                box = j + 3;
                fillBox();
                coin = (coin == 'X') ? 'O' : 'X';
                negDFlag = 0;
            }
            else
            {
                // random
                // printf("rand42 ");
                srand((unsigned)time(NULL));
                box = rand() % 7; // 7 columns
                // printf("%d %d %d %d %d", i, j, box, checkStreak('X', &i, &j), rowFlag);
                fillBox();
                coin = (coin == 'X') ? 'O' : 'X';
            }
        }
    }

    else if (checkStreak(comp, &i, &j) == 2)
    {
        // row
        if (rowFlag == 2)
        {
            if (i + 1 <= 5)
            {
                if (grid[i + 1][j + 2] != ' ' && grid[i][j + 2] == ' ' && posDFlag == 0)
                {
                    // printf("\nIm Here 2row\n");
                    box = j + 2;
                    // printf("%d %d %d", i, j, box);
                    fillBox();
                    coin = (coin == 'X') ? 'O' : 'X';
                    rowFlag = 0;
                }
                else
                {
                    if (j - 1 >= 0)
                    {
                        if (grid[i][j - 1] == ' ')
                        {
                            // printf("\n left 2 \n");
                            box = j - 1;
                            // printf("%d %d %d", i, j, box);
                            fillBox();
                            coin = (coin == 'X') ? 'O' : 'X';
                            rowFlag = 0;
                        }
                        else
                        {
                            // printf("rand5 ");
                            srand((unsigned)time(NULL));
                            box = rand() % 7; // 7 columns
                            // printf("%d %d %d %d %d", i, j, box, checkStreak('X', &i, &j), rowFlag);
                            fillBox();
                            coin = (coin == 'X') ? 'O' : 'X';
                        }
                    }
                    else
                    {
                        // printf("rand6 ");
                        srand((unsigned)time(NULL));
                        box = rand() % 7; // 7 columns
                        // printf("%d %d %d %d %d", i, j, box, checkStreak('X', &i, &j), rowFlag);
                        fillBox();
                        coin = (coin == 'X') ? 'O' : 'X';
                    }
                }
            }
            else
            {
                if (grid[i][j + 2] == ' ')
                {
                    // printf("\nIm Here dbottom\n");
                    box = j + 2;
                    // printf("%d %d %d", i, j, box);
                    fillBox();
                    coin = (coin == 'X') ? 'O' : 'X';
                    rowFlag = 0;
                }
                else if (j - 1 >= 0)
                {
                    if (grid[i][j - 1] == ' ')
                    {
                        // printf("\n left 2 bott \n");
                        box = j - 1;
                        // printf("%d %d %d", i, j, box);
                        fillBox();
                        coin = (coin == 'X') ? 'O' : 'X';
                        rowFlag = 0;
                    }
                    else
                    {
                        // printf("rand7");
                        srand((unsigned)time(NULL));
                        box = rand() % 7; // 7 columns
                        // printf("%d %d %d %d %d", i, j, box, checkStreak('X', &i, &j), rowFlag);
                        fillBox();
                        coin = (coin == 'X') ? 'O' : 'X';
                    }
                }
                else
                {
                    // printf("rand8 ");
                    srand((unsigned)time(NULL));
                    box = rand() % 7; // 7 columns
                    // printf("%d %d %d %d %d", i, j, box, checkStreak('X', &i, &j), rowFlag);
                    fillBox();
                    coin = (coin == 'X') ? 'O' : 'X';
                }
            }
        }
        // colomn
        else if (colFlag == 2)
        {
            // printf("col swap");
            //  box = j;
            fillBox();
            coin = (coin == 'X') ? 'O' : 'X';
            colFlag = 0;
            visited[i][j] = 'c';
        }
        // diagonal
        else if (posDFlag == 2)
        {
            if (grid[i - 2][j + 2] == ' ')
            {
                // printf("pd swap1");
                box = j + 2;
                fillBox();
                coin = (coin == 'X') ? 'O' : 'X';
                posDFlag = 0;
            }
            else
            {
                // printf("rand81 ");
                srand((unsigned)time(NULL));
                box = rand() % 7; // 7 columns
                // printf("%d %d %d %d %d", i, j, box, checkStreak('X', &i, &j), rowFlag);
                fillBox();
                coin = (coin == 'X') ? 'O' : 'X';
            }
        }
        else if (negDFlag == 2)
        {
            if (grid[i + 2][j + 2] == ' ' && grid[i + 1][j + 2] == ' ')
            {
                // printf("nd swap1");
                box = j + 2;
                fillBox();
                coin = (coin == 'X') ? 'O' : 'X';
                negDFlag = 0;
            }
            else
            {
                // printf("rand82 ");
                srand((unsigned)time(NULL));
                box = rand() % 7; // 7 columns
                // printf("%d %d %d %d %d", i, j, box, checkStreak('X', &i, &j), rowFlag);
                fillBox();
                coin = (coin == 'X') ? 'O' : 'X';
            }
        }
        else
        {
            // random
            // printf("rand9 ");
            srand((unsigned)time(NULL));
            box = rand() % 7; // 7 columns
            // printf("%d %d %d %d %d", i, j, box, checkStreak('X', &i, &j), rowFlag);
            fillBox();
            coin = (coin == 'X') ? 'O' : 'X';
        }
    }
    else if (checkStreak(comp, &i, &j) == 1)
    {
        if (grid[i - 1][j] == ' ')
        {
            fillBox();
            coin = (coin == 'X') ? 'O' : 'X';
        }
        else if (grid[i][j + 1] == ' ')
        {
            box = j + 1;
            fillBox();
            coin = (coin == 'X') ? 'O' : 'X';
        }
        else if (grid[i][j - 1] == ' ')
        {
            box = j - 1;
            fillBox();
            coin = (coin == 'X') ? 'O' : 'X';
        }
        else if (grid[i - 1][j + 1] == ' ')
        {
            box = j + 1;
            fillBox();
            coin = (coin == 'X') ? 'O' : 'X';
        }
        else if (grid[i - 1][j - 1] == ' ')
        {
            box = j - 1;
            fillBox();
            coin = (coin == 'X') ? 'O' : 'X';
        }
        else
        {
            if (i + 1 < 5)
            {
                if (grid[i + 1][j + 1] == ' ')
                {
                    box = j + 1;
                    fillBox();
                    coin = (coin == 'X') ? 'O' : 'X';
                }
                else if (grid[i + 1][j - 1] == ' ')
                {
                    box = j - 1;
                    fillBox();
                    coin = (coin == 'X') ? 'O' : 'X';
                }
            }
        }
    }
    else
    {
        // random
        // printf("rand10 ");
        srand((unsigned)time(NULL));
        box = rand() % 7; // 7 columns
        // printf("%d %d %d %d %d", i, j, box, checkStreak('X', &i, &j), rowFlag);
        fillBox();
        coin = (coin == 'X') ? 'O' : 'X';
    }
}
// main function
int main()
{
    int mode = 0;
    int compI = 0;
    int compJ = 0;
    printf("\nWelcome to 4 Wins\n\n");
    printf("Would you like to 1-player mode or 2-player mode?\nFor 1-player mode press 1 and for 2-player mode press 2, please\nMode: ");

    scanf("%d", &mode);
    while (mode != 1 && mode != 2)
    {
        printf("You have entered an invalid number\nPlease enter the number 1 for 1-player mode or 2 for 2-player mode\nMode: ");
        scanf("%d", &mode);
    }

    initGrid();

    printf("Would you like to play with coin X or coin O\ncoin: ");
    scanf(" %c", &coin);
    if (coin == 'x')
        coin = 'X';
    else if (coin == 'o')
        coin = 'O';
    while (coin != 'X' && coin != 'O')
    {
        printf("Wrong coin, Please try again!\ncoin: ");
        scanf(" %c", &coin);

        if (coin == 'x')
            coin = 'X';
        else if (coin == 'o')
            coin = 'O';
    }

    if (mode == 2)
    {

        board();

        while (1)
        {
            printf("Player %c, your turn!\n", coin);
            pick();
            printf("\n\n");
            board();
            if (checkWin('X'))
            {
                printf("\n\nPlayer X wins!\n\n");
                break;
            }
            if (checkWin('O'))
            {
                printf("\n\nPlayer O wins!\n\n");
                break;
            }
            if (checkTie())
            {
                printf("\n\nIt is a tie!\n\n");
                break;
            }
        }
    }
    else if (mode == 1)
    {
        // char player, comp;
        char strategy;
        printf("Would you like to play in prevent winning strategy or try to win\n");
        printf("For prevent winning strategy please press p\nAnd for try to win strategy press t\nStrategy: ");
        scanf(" %c", &strategy);
        if (strategy == 'P')
            strategy = 'p';
        else if (strategy == 'T')
            strategy = 't';

        while (strategy != 'p' && strategy != 't')
        {
            printf("Wrong strategy, Please try again!\nStrategy: ");
            scanf(" %c", &strategy);

            if (strategy == 'P')
                strategy = 'p';
            else if (strategy == 'T')
                strategy = 't';
        }

        if (coin == 'X')
        { // player
            player = 'X';
            comp = 'O';
        }
        else if (coin == 'O')
        { // comp
            player = 'O';
            comp = 'X';
        }
        printf("\n\n");
        board();
        while (1)
        {
            pick();
            printf("\n\n");
            board();

            if (checkWin(player))
            {
                printf("\n\nYou won!\n\n");
                break;
            }
            if (checkWin(comp))
            {
                printf("\n\nThe Computer wins!\n\n");
                break;
            }
            if (checkTie())
            {
                printf("\n\nIt is a tie!\n\n");
                break;
            }

            if (strategy == 'p')
            {
                preventWin(compI, compJ);
            }
            else if (strategy == 't')
            {
                tryToWin(compI, compJ);
            }

            printf("\n\n");
            board();

            if (checkWin(player))
            {
                printf("\n\nYou won!\n\n");
                break;
            }
            if (checkWin(comp))
            {
                printf("\n\nThe Computer wins!\n\n");
                break;
            }
            if (checkTie())
            {
                printf("\n\nIt is a tie!\n\n");
                break;
            }
        }
    }

    else
    {
        printf("You have entered an invalid number\nPlease enter the number 1 for 1-player mode or 2 for 2-player mode\nMode: ");
    }
    scanf(" %c", &coin); // To prevent the cmd from closing
    return 0;
}

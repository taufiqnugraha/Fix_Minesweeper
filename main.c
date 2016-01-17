#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define ROWS 12
#define COLS 20
#define BOMBS 8

#define BOMB 9

void inc(int board[ROWS][COLS], int row, int col)
{
    if (row < 0 || row >= ROWS) return;
    if (col < 0 || col >= COLS) return;
    if (board[row][col] % 10 == BOMB) return;
    board[row][col]++;
}

/*
 *      Set up board and pre-calculate adjacent bombs
 */
void board_init(int board[ROWS][COLS])
{
    int i, j, n;

    for (j = 0; j < ROWS; j++) {
        for (i = 0; i < COLS; i++) {
            board[j][i] = 10;
        }
    }

    n = 0;
    while (n < BOMBS) {
        j = rand() % ROWS;
        i = rand() % COLS;

        if (board[j][i] % 10 != BOMB) {
            board[j][i] = 19;
            inc(board, j - 1, i - 1);
            inc(board, j - 1, i);
            inc(board, j - 1, i + 1);
            inc(board, j,     i - 1);
            inc(board, j,     i + 1);
            inc(board, j + 1, i - 1);
            inc(board, j + 1, i);
            inc(board, j + 1, i + 1);
            n++;
        }
    }
}

/*
 *      Reveal tile and propagate revelation
 */
void board_reveal(int board[ROWS][COLS], int row, int col)
{
    if (row < 0 || row >= ROWS) return;     /* skip off-board tiles */
    if (col < 0 || col >= COLS) return;

    if (board[row][col] < 10) return;       /* already revealed, skip */
    if (board[row][col] >= 20) return;      /* must remove flag first, skip */

    if (board[row][col] % 10 == BOMB) {
        int i, j;

        printf("Bang!\n");

        for (j = 0; j < ROWS; j++) {
            for (i = 0; i < COLS; i++) {
                if (board[j][i] % 10 == BOMB) board[j][i] = BOMB;
            }
        }     
    } else {
        board[row][col] %= 10;
        if (board[row][col] == 0) {
            board_reveal(board, row - 1, col);
            board_reveal(board, row, col - 1);
            board_reveal(board, row, col + 1);
            board_reveal(board, row + 1, col);
        }
    }
}

void board_print(int board[ROWS][COLS])
{
    int i, j;

    for (j = 0; j < ROWS; j++) {
        putchar(' ');

        for (i = 0; i < COLS; i++) {
            const char *tile = ".12345678*##########PPPPPPPPPP";
            int k = board[j][i];

            putchar(tile[k]);
        }

        putchar('\n');
    }
}

int main()
{
    int board[ROWS][COLS];

    srand(time(NULL));
    board_init(board);
    board_reveal(board, 0, 0);
    board_print(board);

    return 0;
}

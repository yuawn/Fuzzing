#if KLEE
#include <klee/klee.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>

#define COL 11
#define ROW 7
#define MOVE_MAX 28


char maze[ROW][COL] = {
    "+-+---+---+",
    "| |     |#|",
    "| | --+ | |",
    "| |   | | |",
    "| +-- | | |",
    "|     |   |",
    "+-----+---+"
};


int wall[ROW][COL] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};


void render() {

    system("clear");

    for (int i = 0; i < ROW; ++i) {

        for (int j = 0; j < COL; ++j) {

            printf("%c", maze[i][j]);

        }

        printf("\n");

    }

    printf("\n");

}


int main() {

    int x = 1, y = 1;
    int step = 0;
    char moves[MOVE_MAX];

    maze[y][x] = 'O';
    wall[y][x] = 1; // can't go back

#if KLEE
    klee_make_symbolic(moves, MOVE_MAX, "moves");
#else
    read(0, moves, MOVE_MAX);
#endif

    do {

        switch (moves[step]) {
            case 'w':
                --y;
                break;
            case 's':
                ++y;
                break;
            case 'a':
                --x;
                break;
            case 'd':
                ++x;
                break;
            default:
                puts("Wrong command! (only w,s,a,d accepted!)");
                exit(-2);
        }

        if (maze[y][x] == '#') {

            puts("You win :D");
            printf("Solution %s\n", moves);
#if KLEE
            klee_assert(0);
#endif
            exit(0);

        }

        if (wall[y][x]) {

            maze[y][x] = 'X';
            render();
            puts("You dead :(");
            exit(-1);

        } else {

            maze[y][x] = 'O';
            wall[y][x] = 1; // can't go back

        } 

#ifndef KLEE
        usleep(500 * 1000);
#endif
        render();

    }  while(++step < MOVE_MAX);

    return 0;

}
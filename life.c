#include <stdio.h>
#include <unistd.h> 

enum {BWIDTH = 79, BHEIGHT = 24}; /* Board Height and Width */
enum {LIVE = '#', DEAD = '-'}; /* Cell State */

void
clearboard(int b[][BHEIGHT]) {
    int i, j;
    for (i = 0; i < BWIDTH; ++i)
        for (j = 0; j < BHEIGHT; ++j)
            b[i][j] = DEAD;
}

int
xadd(int x, int inc) {
    x += inc;
    while (x < 0)
        x += BWIDTH;
    while (x >= BWIDTH)
        x -= BWIDTH;
    return x;
}

int
yadd(int y, int inc) {
    y += inc;
    while (y < 0)
        y += BHEIGHT;
    while (y >= BHEIGHT)
        y -= BHEIGHT;
    return y;
} 


int
countlive(int b[][BHEIGHT], int x, int y) {
    int i, j;
    int nlive = 0;
    /* Count around the cell */
    for (i = -1; i <= 1; ++i)
        for (j = -1; j <= 1; ++j)
            if (i|j && b[xadd(x,i)][yadd(y,j)] == LIVE)
                ++nlive;
    return nlive;
}

void
play(int b[][BHEIGHT]) {
    int nextboard[BWIDTH][BHEIGHT];
    int x, y;
    int nlive;
    for (x = 0; x < BWIDTH; ++x)
        for (y = 0; y < BHEIGHT; ++y) {
            nlive = countlive(b, x, y);
            if (nlive == 2) nextboard[x][y] = b[x][y];
            if (nlive == 3) nextboard[x][y] = LIVE;
            if (nlive < 2) nextboard[x][y] = DEAD;
            if (nlive > 3) nextboard[x][y] = DEAD;
        }
    for (x = 0; x < BWIDTH; ++x)
        for (y = 0; y < BHEIGHT; ++y)
            b[x][y] = nextboard[x][y]; 
} 

void
printboard(int b[][BHEIGHT]) {
    int x, y;
    for (y = 0; y < BHEIGHT; ++y) {
        for (x = 0; x < BWIDTH; ++x) 
            putchar(b[x][y] == LIVE ? LIVE : DEAD);
        putchar('\n');
    }
}

void
clearscreen(void) {
    puts("\033[H\033[J");
}

void
millisleep(unsigned msec) {
    usleep(msec * 1e3);
}

/*
void
readboard(int b[][BHEIGHT], const char *fname) {
    FILE *bfin;
    int x, y;
*/

void
set(int b[][BHEIGHT], int x, int y) {
    b[xadd(x,5)][yadd(y,5)] = LIVE;
}

int
main(int argc, const char *argv[]) {
    int b[BWIDTH][BHEIGHT];
    int i;
    clearboard(b);
    set(b, 1, 0);
    set(b, 0,2 );
    set(b, 1,2 );
    set(b, 3,1);
    set(b,  4,2);
    set(b,  5,2);
    set(b,  6,2);
    for (i = 0; i < 10000; ++i) {
        printboard(b);
        play(b);
        millisleep(10);
        b[i][20] = LIVE;
        clearscreen();
    }
    return 0;
}

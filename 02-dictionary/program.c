#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX 0x100

char input[MAX];


void BUG() {

    strtok("BOOOOM", "O"); // Segmentation fault

}


int main() {

    if (read(0, input, MAX) < 4)
        return -1;

#ifndef SPLIT

    if (!strcmp(input, "ABC")) {

        BUG();

#else

    if (input[0] == 'A') {
        if (input[1] == 'B')
             if (input[2] == 'C')
                BUG();

#endif
    }

    return 0;
}

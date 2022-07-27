#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX 0x200

char input[MAX];


void BUG() {

    puts("reach the bug.");
    printf(input);

}


int main() {

    if (read(0, input, MAX) < 4)
        return -1;

    if (input[0] == 'A') {

        BUG();

    }

    return 0;
}

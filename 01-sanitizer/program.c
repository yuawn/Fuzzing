#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX 0x100

char input[MAX];


void SILENT_BUG() {

    puts("reach the bug.");
    input[MAX + 2] = 0; // silent bug

}


int main() {

    if (read(0, input, MAX) < 4)
        return -1;

    if (input[0] == 'A') {

        SILENT_BUG();

    }

    return 0;
}

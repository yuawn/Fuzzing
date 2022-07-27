#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX 0x100

char input[MAX];


void BUG() {

    strtok("BOOOOM", "O"); // Segmentation fault

}


int main(int argc, char **argv) {

#if FILE_INPUT
    // read input from file
    if (argc < 2)
        return -1;

    FILE *f;
    if (!(f = fopen(argv[1], "rb")))
        return -1;

    fread(input, MAX, 1, f);
    fclose(f);
#else
    // read input from stdin
    if (read(0, input, MAX) < 4)
        return -1;
#endif

    if (input[0] == 'A') {

        BUG();

    }

    return 0;
}

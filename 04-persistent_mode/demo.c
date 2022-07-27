#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void BUG() {

    strtok("BOOOOM", "O"); // Segmentation fault

}


void demo_vuln_api(char *data) {

    if (data[0] == 'A') {
        
        BUG();

    }

}

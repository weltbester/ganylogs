#include <stdio.h>
#include <stdlib.h>

void showHostNames(FILE *fp) {
    char hostname[12]; // check length at createHostlist
    fseek(fp, 0, SEEK_SET);
    printf("Router list: [");
    while ( (fscanf(fp, "%s", hostname) != EOF)) {
        printf("%s ", hostname);
    }
    printf("]\n\n");    
    return;
}
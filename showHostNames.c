#include <stdio.h>
#include <stdlib.h>

void showHostNames(FILE *fp) {
    if (NULL == fp) {
        printf("Create a hostlist first!\n");
        return;
    } else {
        char hostname[10];
        fseek(fp, 0, SEEK_SET);
        printf("Router list: [");
        while ( (fscanf(fp, "%s", hostname) != EOF)) {
            printf("%s ", hostname);
        }
        printf("]\n\n");    
        return;
    }
}
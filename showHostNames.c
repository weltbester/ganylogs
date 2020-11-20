#include <stdio.h>
#include <stdlib.h>

void showHostNames(FILE *fp) {
    int n = 0;
    if (NULL == fp) {
        printf("Enter routers first!\n");
        return;
    } else {
        char hostname[10];
        fseek(fp, 0, SEEK_SET);
        printf("Router list: [ ");
        while ( (fscanf(fp, "%s", hostname) != EOF)) {
            n++;
            if (n == 1) {
                printf("%s", hostname);
            } else {
                printf(", %s", hostname);
            }
        }
        printf(" ]\n\n");    
        return;
    }
}
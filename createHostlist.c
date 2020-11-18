#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void createHostlist(FILE *fp) {
    char hostname[10];
    int groesse = 0;

    printf("How many routers to enter? ");
    if ( (scanf("%d", &groesse) != 1)) {
        printf("Input Error!\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < groesse; ++i) {
        printf("%d. Router: ", i+1);
        scanf("%s", hostname);
        fprintf(fp, "%s\n", hostname);
    }
    return;
}
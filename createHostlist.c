#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void createHostlist(char *user) {
    FILE *fpHostlist;
    char listName[31], hostname[10];
    int groesse = 0;

    strcpy(listName, user);
    strcat(listName, "_hosts.txt");
    fpHostlist = fopen(listName, "a");
    if (fpHostlist == NULL) {
        printf("Cannot open file!\n");
        exit(EXIT_FAILURE);
    }
    printf("How many routers to enter? ");
    if ( (scanf("%d", &groesse) != 1)) {
        printf("Input Error!\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < groesse; ++i) {
        printf("%d. Router: ", i+1);
        scanf("%s", hostname);
        fprintf(fpHostlist, "%s\n", hostname);
    }
    fclose(fpHostlist);
    return;
}
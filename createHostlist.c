#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void createHostlist(char *user) {
    FILE *fpHostlist;
    char listName[31];

    strcpy(listName, user);
    strcat(listName, "_hosts.txt");
    fpHostlist = fopen(listName, "a");
    if (fpHostlist == NULL) {
        printf("Cannot open file!\n");
        exit(EXIT_FAILURE);
    }



    fclose(fpHostlist);
}
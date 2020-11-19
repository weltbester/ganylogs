#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void createHostlist(FILE *fp, char *file) {
    char hostname[10];
    int groesse = 0;

    if (NULL == fp) {
        fp = fopen(file, "a+");
        if (NULL == fp) {
            printf("Cannot open file '%s'.\n", file);
            exit(EXIT_FAILURE);
        }
    } else {
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
}   
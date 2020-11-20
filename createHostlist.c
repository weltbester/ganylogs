#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DS 11

void createHostlist(FILE *fp) {
    char hostname[10];
    int groesse = 0, offset = 0;
    /* !TODO: Check if list contains already entries,
        count entries and proceed with ongoing number
        when entering addtional routers on a second call

        Try to solve it with FSEEK_END and ftell and Data-size (DS)
    */
    fseek(fp, 0, SEEK_END);
    offset = (int)ftell(fp) / DS;

    printf("How many routers to enter? ");
    if ( (scanf("%d", &groesse) != 1)) {
        printf("Input Error!\n");
        exit(EXIT_FAILURE);
    }
    groesse += offset;
    for (int i = offset; i < groesse; ++i) {
        printf("%d. Router: ", i+1);
        scanf("%s", hostname);
        fprintf(fp, "%-10s\n", hostname); // '%-10s' to be conform with DS
    }
    return;
}   
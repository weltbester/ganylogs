#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char **enterRouters(int *groesse) {
    char **result;
    printf("How many routers to enter? ");
    if ( (scanf("%d", groesse) != 1)) {
        printf("Input Error!\n");
        return NULL;
    }
    result = (char **)malloc(*groesse * sizeof(char *));
    if ( NULL == result ) {
        fprintf(stderr, "Memory Allocation Failure\n");
        return NULL;
    }
    char hostName[20];
    for (int i=0; i < *groesse; ++i) {
        printf("%d. Hostname: ", i+1);
        if ( (scanf("%s[^\n]", hostName) != 1) ) {
            printf("Input Error!\n");
            return NULL;
        }
        result[i] = (char *)malloc((strlen(hostName)+ 1) * sizeof(char));
        if ( NULL == result[i]) {
            fprintf(stderr, "Memory Allocation Failure\n");
            return NULL;
        }
        strcpy(result[i], hostName);
    }
    return result;
}
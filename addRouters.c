#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void addRouters(char *devices[], int n, int more) {
    char hostName[20];
    int i = 0;
    
    for (i=n-more; i < n; ++i) {
        printf("%d. Hostname: ", i+1);
        if ( (scanf("%s[^\n]", hostName) != 1) ) {
            printf("Input Error!\n");
            exit(EXIT_FAILURE);
        }
        devices[i] = (char *)malloc((strlen(hostName)+ 1) * sizeof(char));
        if ( NULL == devices[i]) {
            fprintf(stderr, "Memory Allocation Failure\n");
            break;
        }
        strcpy(devices[i], hostName);
    }
    return;
}


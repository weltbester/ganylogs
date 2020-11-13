#include <stdio.h>
#include <stdlib.h>

char **deleteRouters(char *devices[], int *n) {
    int i = 0;
    if ( NULL != devices) {
        for (i = 0; i < *n; ++i) {
            free(devices[i]);
        }
        free(devices);        
        devices = NULL;
    }
    return devices;
}


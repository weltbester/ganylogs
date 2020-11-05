#include <stdio.h>
#include <stdlib.h>

char **deleteRouters(char *devices[], int *n) {
    //int m = *n;
    if ( NULL != devices) {
        for (int i = 0; i < *n; ++i) {
            free(devices[i]);
            //*n -= 1;
            //devices[i] = NULL;
        }
        free(devices);        
        devices = NULL;
    }
    return devices;
}
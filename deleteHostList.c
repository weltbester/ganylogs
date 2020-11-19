#include <stdio.h>
#include <stdlib.h>

int deleteHostList(FILE *fp, char *file) {
    if (NULL != fp) {
        fclose(fp);
        remove(file);
        printf("Hostlist %s deleted!\n", file);
    } else {
        printf("Nothing to delete!\n");
    }
    return EXIT_SUCCESS;
}
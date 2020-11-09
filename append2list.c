#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void append2list(void) {
    FILE *fpList;
    char signature[20];
    char listtype[14];
    unsigned char input = ' ';
    
    /* !TODO: Empty buffer before 'scanf()' [" %c"] */
    printf("Enter to blacklist (b) or whitelist (w)? ");
    if ( scanf(" %c", &input) != 1 ) {
        printf("Input Error");
        exit(EXIT_FAILURE);
    }                                                           /* Delete warnings */
    while ( input != 'w' && input != 'b') {
        printf("Only 'w' or 'b is allowed: ");
        if ( scanf(" %c", &input) != 1 ) {
            printf("Input Error");
            exit(EXIT_FAILURE);
        }                                                         /* dito */
    }

    /* Make file backup before opening to the file */
    char mkcpybl[63] = "cp blacklist.txt blacklist.txt.bak";
    char mkcpywl[63] = "cp whitelist.txt whitelist.txt.bak";
    if (input == 'w') {
        system(mkcpywl);
        strcpy(listtype, "whitelist.txt");
    } else {
        system(mkcpybl);
        strcpy(listtype, "blacklist.txt");
    }
    listtype[13] = '\0';
    fpList = fopen(listtype, "a");
    if (fpList == NULL) {
        printf("Cannot open %s!\n", listtype);
        return;
    }

    /* Enter syslog signature(s) and close file */
    unsigned char jn = ' ';
    do {
        printf("\nPlease enter signature [Format: $BLABLABLA$]: ");
        if ( scanf("%s20", signature) != 1 ) {
            printf("Input error!\n");
        return;  
        } 
        fprintf(fpList, "%s\n", signature);
        printf("\nAdded '%s' to %s.\n", signature, listtype);
        /* !TODO: dump buffer and delete whitespace in " %c"!!! */
        printf("\nMore signatures? (y/n, Y/N) ");
        if (scanf(" %c", &jn) != 1) {
            printf("Input Error!\n");
            exit(EXIT_FAILURE);
        }
    } while ( jn == 'y' || jn == 'Y');
    fclose(fpList);
    system("clear");
    return;
}

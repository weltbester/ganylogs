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

    /* !TODO: make backup before writing to the file!!! */
    if (input == 'w') {
        strcpy(listtype, "whitelist.txt");
    } else {
        strcpy(listtype, "blacklist.txt");
    }
    listtype[13] = '\0';
    fpList = fopen(listtype, "a");
    
    // hint to signature format, e.g.: %BLABLABLA%
    if (fpList == NULL) {
        printf("Cannot open %s!\n", listtype);
        return;
    }
    printf("Please enter signature: ");
    if ( scanf("%s20", signature) != 1 ) {
      printf("Input error!\n");
      return;  
    } 
    fprintf(fpList, "%s\n", signature);
    printf("\nAdded '%s' to %s.\n", signature, listtype);
    /* !TODO: add more messages-Loop */

    fclose(fpList);
    return;
}
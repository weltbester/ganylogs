/**
 * Copyright November 2020: Georg Pohl, 70174 Stuttgart
 * File: createHostlist.C
 * ----------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// Data size of one hostname entry in hostlist.
#define DS 11

/**
 * Implementation notes: createHostlist(void)
 * ------------------------------------------
 * @brief Create a list with (Router) hostnames.
 * @param *fp File pointer to the hostfile filestream
 * @return (void)
 *
 * Here a filestream to the hostlist file is given by
 * the referenced parameter '*fp'. The user will enter
 * the amount of routers he wants to be monitored.
 * Because the filestream varible is a reference, this
 * entry are returned to the main function.
 * 
 * Every hostname must not be longer then 10 characters.
 * Characters behnind this border are cut off.
 * The string termination character ('\0') will be added
 * automatically, which makes strings with a maximum
 * length of 11 characters possible.
 *
 * You will be prompted with a counter index, indicating
 * which number of router you are going to enter at the
 * moment. This is also true, if you use this function
 * for adding more routers to an existing hostlist.
 *
 *  The filestream will be closed by the caller and error
 * handling is done in main().
 */

void createHostlist(FILE *fp) {
    char hostname[10];
    int groesse = 0, offset = 0;
    
    fseek(fp, 0, SEEK_END);
    offset = (int)ftell(fp) / DS;

    printf("How many routers to enter? ");
    if ( (scanf("%d", &groesse) != 1)) {
      printf("Input Error, expected integer number!\n");
      exit(EXIT_FAILURE);
    }
    groesse += offset;
    for (int i = offset; i < groesse; ++i) {
        printf("%d. Router: ", i+1);
        scanf("%s", hostname);
        fprintf(fp, "%-10s\n", hostname); // '%-10s' to be conform with DS 11 (ten characters + '\0')
    }
    return;
}
   

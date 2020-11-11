/*! @brief Tool to identify new syslog messages */
/**
 * 
 * File: ganysyslogs.c
 *
 * Author: Georg Pohl, 70174 Stuttgart
 *
 * Create date: 8th of November 2020
 *
 * Version: 1.0
 *
 * Last Change: 8th of November 2020
 *
 * -----------------------------------
 * This program can be used to identify unknown syslog
 * messages, when you introduce a new router software. It is
 * meant to be used durch den Product Validation (PV) time only.
 * Therefore you feed the program with the involved router
 * hostnames, so that it can browse through the recent logfile
 * and grep out every syslog message of the before defined hosts.
 *
 * Every message is then compared with the 'blacklist'- and
 * a 'whitelist' file.
 *
 * 1. If it is found in 'blacklist', the message is known but
 *    regarded as not-remarkable and the original message is
 *    skipped.
 * 2. If it is found in the 'whitelist' it is already know and
 *    declared as remarkable and therfore under control. So no
 *    further processing needed and therefore also skipped.
 * 3. The message is neither known in the 'blacklist' nor the
 *    'whitelist' means we are dealing with an unknown message
 *    here.
 *    This message is send to the initiator of the script via
 *    e-Mail for further investigation. Depending on the
 *    importance of the syslog message, it then copied either
 *    to the 'black-' or 'whitelist'.
 *
 * 'blacklist': contains log messages which are not transferred
 * to the "MONITORING SYSTEM".
 *
 * 'whitelist': contains log messages which are importand and have
 * to be transferred to the "MONITORING SYSTEM".
 *
 * Copyright (C) 2020 CAN Georg Pohl
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Routine to clear the screen */
#ifdef __unix__
    #define clrscr() printf("\x1B[2J")
#elif __APPLE__
    #define clrscr() printf("\x1B[2J")
#elif __BORLANDC__ && __MSDOS__
    #include <conio.h>
#elif __WIN32__ || _MSC_VER
    #define clrscr() system("cls") 
#else
    #define clrscr() printf("clrscr() - Fehler!!\n") 
#endif

#define SENTINEL 8      // Determines which option can quit the program

/* CONSTANTS */

/* STRUCTS */

/* PROTOTYPES */
extern char **enterRouters(int *groesse);
extern void addRouters(char *devices[], int n, int more);
extern char **deleteRouters(char *devices[], int *n);
extern void append2list(void);
int createCronJob();

void showRouters(char *arr[], int n);


int main(int argc, const char **argv) {
    char **routers = NULL;
    int choice = 0, nHosts = 0, more = 0;

    clrscr();
    // system("clear");
    printf("\n\tGANYSYSLOGS: TOOL TO IDENTIFY NEW SYSLOG MESSAGES\n");
    printf("\t-------------------------------------------------\n");

    do {
        putchar('\n');
        printf("\t-1- Enter routers\n");
        printf("\t-2- Add more routers\n");
        printf("\t-3- Delete all routers\n");
        printf("\t-4- Show routers\n");
        printf("\t-5- Create cronjob\n");
        printf("\t-6- Enter syslog signature to 'black-' or 'whitelist'\n");
        printf("\t-7- vakant\n");
        printf("\t-8- Quit\n\n");

        printf("Your choice: ");
        if ( (scanf("%d", &choice) != 1) ) {
            printf("Fehler bei der Eingabe!\n");
            return 1;
        }
        // !TODO: Delete clrscr() and definitions
	clrscr();
    // system("clear");

        // Switch Anweisung
        switch (choice) {
            // Enter routers
            case 1: routers = enterRouters(&nHosts);
                    if (NULL == routers) {
                        return 1;
                    }
            break;
            // Add more routers: !TODO: NOCH RICHTIG IMPLEMENTIEREN
            case 2:if (NULL == routers) {
                        printf("Function is only for adding routers\n"
                        "to existing routers. - Use option '1' first.\n");
                        break;
                    } else {
                        printf("How many routers to add? ");
                        if ( (scanf("%d", &more) != 1)) {
                            printf("Input Error!\n");
                            exit(EXIT_FAILURE);
                        }
                        nHosts += more;
                        routers = (char **)realloc(routers, nHosts * sizeof(char *));
                        addRouters(routers, nHosts, more); // Create cronjob
                    }
            break;
            case 3: routers = deleteRouters(routers, &nHosts);
                    printf("%d router(s) deleted.\n", nHosts);
            break;
            // Display entered routers
            case 4: showRouters(routers, nHosts);
            break;
            // Create cronjob
            case 5: createCronJob();
            break;
            // Enter syslog signature to 'blacklist'
            case 6: append2list();
            break;
            // Enter syslog signature to 'whitelist'
            case 7: printf("Vakant!\n");
            break;
            case SENTINEL:  printf("Bye!\n");
                            if (NULL != routers) {
                                free(routers);
                                routers = NULL;
                            }
            break;
            default: printf("Gültige Auswahl 1 - %d\n\n", SENTINEL);
            break;
        }
    } while (choice != SENTINEL);
    // Free memory and avoid dangling pointers
    
  return EXIT_SUCCESS;
}
void showRouters(char *arr[], int n) {
    int i = 0;
    if (NULL == arr) {
        printf("No routers entered\n");
    } else {
        printf("\nAdded routers: ");
        printf("[");
        for (i=0; i < n; ++i) {
            if (i == 0) {
                printf("%s", arr[i]);
            } else {
                printf(", %s", arr[i]);
            } 
        }
        printf("]\n\n");
    }    
    return;
}
/*
 * A C program is not a script; it is source code that must be compiled before use. You can compile the program and then invoke it from cron with its (fully qualified) name. For example, if you compile "test.c" to the executable "test", and place it in /usr/local/bin, your cron entry would be:
 * 52 1 * * * /usr/local/bin/test
 * You should not place executables in the /etc directory; that is not where they belong. The /etc directory is for configuration parameters. Executables should be placed in a bin directory. Locally created executables that are available system-wide should be in /usr/local/bin/.
 */

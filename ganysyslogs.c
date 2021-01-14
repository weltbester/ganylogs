/// Brief ganysyslog description.
///
/// Here comes more...
/*! @brief Tool to identify new syslog messages */
/**
 * 
 * File: ganysyslogs.c
 *
 * Author: Manfred Jaede & Georg Pohl, 70174 Stuttgart
 *
 * Create date: 8th of November 2020
 *
 * Version: 1.0
 *
 * Last Change: 27th of November 2020
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
 * Copyright (C) 2020 Manfred Jaede, CAN Georg Pohl
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>     //!< for getlogin()

/* Conditional compiling options for clear screen command*/
#ifdef __unix__
    #define clrscr() printf("\x1B[2J")
#elif __APPLE__ || _AIX			// Obsolete, was necessary for AIX UNIX
    #define clrscr() printf("\x1B[2J")
#elif __BORLANDC__ && __MSDOS__
    #include <conio.h>
#elif __WIN32__ || _MSC_VER
    #define clrscr() system("cls") 
#else
    #define clrscr() printf("clrscr() - Fehler!!\n") 
#endif

#define POSIX_SOURCE    //!< for getlogin()
#define SENTINEL 7      // Determines which option can quit the program

/* CONSTANTS */

/* STRUCTS */

/* PROTOTYPES */
extern void createHostlist(FILE *fp);
extern void showHostNames(FILE *fp) ;
extern int deleteHostList(FILE *fp, char *file);
int createCronJob();
extern int deleteCronJob();
extern void append2list(void);

int main(int argc, const char **argv) {
    FILE *fp = NULL;
    int choice = 0; //!< Option-Switch, number of monitored devices, number of additional devices
    char *user, listName[63];

    /* Get username */
    if ((user = getlogin()) == NULL) {
        perror("__getlogin() error");
    }
    if (strlen(user) < 3) {
      printf("Program works on 'ispnmc' only!\n");
      return  EXIT_FAILURE;
    }

    /*!< Open user-specific hostfile */
    /* !TODO: provide user-related pathname to home directory, gp 2021-01-13 */
    strcpy(listName, "/home/");
    strcat(listName, user);
    strcat(listName, "/");
    strcat(listName, user);
    strcat(listName, "_hosts.txt");
    fp = fopen(listName, "a+");
    if (NULL == fp) {
      printf("Can not open file '%s'!\n", listName);
      return EXIT_FAILURE;
    }
    
    /*!< Menue */
    clrscr();
    printf("\n\tGANYSYSLOGS: TOOL TO IDENTIFY NEW SYSLOG MESSAGES\n");
    printf("\t-------------------------------------------------\n");

    do {
        putchar('\n');
        printf("\t-1- Enter/add routers\n\n");
        printf("\t-2- Show routers\n\n");
        printf("\t-3- Delete hostlist\n\n");
        printf("\t-4- Create cronjob\n\n");
	printf("\t-5- Delete cronjob\n\n");
        printf("\t-6- Enter syslog signature to 'black-' or 'whitelist'\n\n");
        printf("\t-7- Quit\n\n\n");

        printf("Your choice: ");
        if ( (scanf("%d", &choice) != 1) ) {
            printf("Fehler bei der Eingabe!\n");
            return 1;
        }
	    clrscr();

        // Switch Anweisung
        switch (choice) {
            // Enter routers
            case 1: if (fp == NULL) {
                        fp = fopen(listName, "a+");
                        if (NULL == fp) {
                            printf("Cannot open file '%s'.\n", listName);
                            exit(EXIT_FAILURE);
                        }
                    }
                    createHostlist(fp);
		    fclose(fp);
            break;
            // Display entered routers
            case 2: showHostNames(fp);
            break;
            // Delete hostfile
            case 3: deleteHostList(fp, listName); fp = NULL;
            break;
            // Create cronjob
            case 4: createCronJob();
            break;
	    case 5: deleteCronJob();
	    break;
            // Enter syslog signature to 'blacklist'
            case 6: append2list();
                    clrscr();
            break;
            // Quit program
            case SENTINEL:  printf("Wirsing!\n");
            break;
            default: printf("Valid options: 1 - %d\n\n", SENTINEL);
            break;
        }
    } while (choice != SENTINEL);
    if (fp != NULL) {
        fclose(fp);
    }   
  return EXIT_SUCCESS;
}

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
 * Last Change: 13th of November 2020
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
#elif __APPLE__ || _AIX
    #define clrscr() printf("\x1B[2J")
#elif __BORLANDC__ && __MSDOS__
    #include <conio.h>
#elif __WIN32__ || _MSC_VER
    #define clrscr() system("cls") 
#else
    #define clrscr() printf("clrscr() - Fehler!!\n") 
#endif

#define POSIX_SOURCE    //!< for getlogin()
#define SENTINEL 6      // Determines which option can quit the program

/* CONSTANTS */

/* STRUCTS */

/* PROTOTYPES */
extern void createHostlist(FILE *fp);
extern void showHostNames(FILE *fp) ;
extern int deleteHostList(FILE *fp, char *file);
int createCronJob();
extern void append2list(void);


int main(int argc, const char **argv) {
    FILE *fp = NULL;
    int choice = 0; //!< Option-Switch, number of monitored devices, number of additional devices
    char user[7] = "gp", listName[31];

    /*!< Open user-specific hostfile */
    /*
    if ((user = getlogin()) == NULL) {
        perror("__getlogin() error");
    } */

    // strcpy(listName, "/home/mj/router_liste.txt");
    strcpy(listName, user);
    strcat(listName, "_hosts.txt");
    fp = fopen(listName, "a+");



    strcpy(listName, user);
    strcat(listName, "_hosts.txt");
    
    /*!< Menue */
    clrscr();
    printf("\n\tGANYSYSLOGS: TOOL TO IDENTIFY NEW SYSLOG MESSAGES\n");
    printf("\t-------------------------------------------------\n");

    do {
        putchar('\n');
        printf("\t-1- Enter/add routers\n");
        printf("\t-2- Show routers\n");
        printf("\t-3- Delete hostlist\n");
        printf("\t-4- Create cronjob\n");
        printf("\t-5- Enter syslog signature to 'black-' or 'whitelist'\n");
          printf("\t-6- Quit\n\n");

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
            break;
            // Display entered routers
            case 2: showHostNames(fp);
            break;
            // Delete hostfile
            case 3: deleteHostList(fp, listName); fp = NULL;
            break;
            // Create cronjob
            case 4: printf("Open crontab at terminal with 'crontab -e' and add ('i') the following command:\n\n\t"
                          "0   7  *   *  * /home/gp/skripte/dsr_sh_module\n\n"
                          "Then close crontab file with 'ESC', 'wq', ENTER\n\n");
                          
                          // createCronJob();
            break;
            // Enter syslog signature to 'blacklist'
            case 5: append2list();
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
    /*!TODO: eventually close 'fp' here */
    
  return EXIT_SUCCESS;
}
/*
 * A C program is not a script; it is source code that must be compiled before use.
 * You can compile the program and then invoke it from cron with its (fully qualified) name.
 * For example, if you compile "test.c" to the executable "test", and place it in /usr/local/bin,
 * your cron entry would be:
 * 52 1 * * * /usr/local/bin/test
 * You should not place executables in the /etc directory; that is not where they belong.
 * The /etc directory is for configuration parameters. Executables should be placed in a bin directory.
 * Locally created executables that are available system-wide should be in /usr/local/bin/.
 */

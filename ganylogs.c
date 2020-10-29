/** 
 * Copyright October 2020: Georg Pohl, 70174 Stuttgart
 * File: ganylogs.c
 * ----------------
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
 */

#include <stdio.h>
#include <stdlib.h>

/* CONSTANTS */

/* STRUCTS */

/* PROTOTYPES */
void enterHostnames();

int main(int argc, const char **argv) {
    int choice = 0;
    // char hosts[5][9]; // noch Implementierung prüfen!!
    printf("\n\tGANYLOGS: FILTERING TOOL FOR NEW SYSLOG MESSAGES\n");
    printf("\t-------------------------------------------------\n\n");

    do {
        printf("\t-1- Enter hostname\n");
        printf("\t-2- Create cronjob\n");
        printf("\t-3- Enter syslog signature to 'blacklist'\n");
        printf("\t-4- Enter syslog signature to 'whitelist'\n");
        printf("\t-5- Quit\n\n");

        printf("Your choice: ");
        if ( (scanf("%d", &choice) != 1) ) {
            printf("Fehler bei der Eingabe");
            return 1;
        }

        // Switch Anweisung
        switch (choice) {
            case 1: enterHostnames();   // Enter hostname
            break;
            case 2: // Create cronjob
            break;
            case 3: // Enter syslog signature to 'blacklist'
            break;
            case 4: // Enter syslog signature to 'whitelist'
            break;
            case 5: printf("Bye!\n");
            break;
            default:
            break;
        }
    }while (choice != 5);

  return EXIT_SUCCESS;
}

/* FUNCTIONS */
void enterHostnames() {
    char hosts[5][9];
    int nHosts = 0;
    printf("Enter the number of routers (<=5): ");
    if ( (scanf("%d", &nHosts) == 0)) {
        printf("Input Error!\n");
        exit(1);
    }
    for (int i=0; i < nHosts; ++i) {
        printf("%d. Routername: ", i+1);
        if ( (scanf("%s[^\n]", hosts[i]) == 0)) {
            printf("Input Error!\n");
            exit(1);
        }
    }
    printf("\nAdded routers: ");
    printf("[");
    for (int i=0; i < nHosts; ++i) {
        if (i == 0) {
            printf("%s", hosts[i]);
        } else {
            printf(", %s", hosts[i]);
        }
    }
    printf("]\n\n");
}
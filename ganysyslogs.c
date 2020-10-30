/** 
 * Copyright October 2020: Georg Pohl, 70174 Stuttgart
 * File: ganysyslogs.c
 * -------------------
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
#define SENTINEL 7

/* CONSTANTS */

/* STRUCTS */

/* PROTOTYPES */
void enterHostnames(char *hosts[], int *n);
void showHostnames(char *arr[], int n);

int main(int argc, const char **argv) {
    char *routers = NULL;
    int choice = 0, nHosts = 0;
    // char *hosts[9]; // noch Implementierung prüfen!!
    printf("\n\tGANYSYSLOGS: TOOL TO IDENTIFY NEW SYSLOG MESSAGES\n");
    printf("\t-------------------------------------------------\n");

    do {
        putchar('\n');
        printf("\t-1- Enter hostnames\n");
        printf("\t-2- Add hostnames\n");
        printf("\t-3- Show hostnames\n");
        printf("\t-4- Create cronjob\n");
        printf("\t-5- Enter syslog signature to 'blacklist'\n");
        printf("\t-6- Enter syslog signature to 'whitelist'\n");
        printf("\t-7- Quit\n\n");

        printf("Your choice: ");
        if ( (scanf("%d", &choice) != 1) ) {
            printf("Fehler bei der Eingabe");
            return 1;
        }
        // putchar('\n');

        // Switch Anweisung
        switch (choice) {
            case 1: enterHostnames(&routers, &nHosts);   // Enter hostname
            break;
            case 2: // Create cronjob
            break;
            case 3: showHostnames(&routers, nHosts);// showHostnames(char **arr, int n) // Enter syslog signature to 'blacklist'
            break;
            case 4: // Enter syslog signature to 'whitelist'
            break;
            case 5: // do something
            break;
            case SENTINEL: printf("Bye!\n");
            break;
            default: printf("Gültige Auswahl 1 - %d\n\n", SENTINEL);
            break;
        }
    } while (choice != SENTINEL);
    // Free memory and avoid dangling pointers
    
    
  return EXIT_SUCCESS;
}

void enterHostnames(char *hosts[], int *n) {
    *n = 0;
    printf("Enter the number of routers (<=5): ");
    if ( (scanf("%d", n) == 0)) {
        printf("Input Error!\n");
        exit(1);
    }
    // Allocate memory for a Char-Array with 'nHosts' Elementf of size 9
    for (int j=0; j < *n; ++j) {
        hosts[j] = (char *)malloc(9 * sizeof(char));
        printf("%d. Hostname: ", j+1);
        if ( (scanf("%s[^\n]", hosts[j]) != 1)) {
            printf("Input Error!\n");
            exit(1);
        }   
    }
}

void showHostnames(char *arr[], int n) {
    printf("\nAdded routers: ");
    printf("[");
    for (int i=0; i < n; ++i) {
        if (i == 0) {
            printf("%s", arr[i]);
        } else {
            printf(", %s", arr[i]);
        }
    }
    printf("]\n\n");
}
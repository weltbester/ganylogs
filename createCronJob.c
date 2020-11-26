/**
 * Copyright November 2020: Georg Pohl, 70174 Stuttgart
 * File: createCronJob.c
 * ---------------------
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * Implementation notes: int createCronJob(void)
 * ---------------------------------------------
 * @brief Creates a cronjob entry for AIX Unix
 * @param (void)
 * @return EXIT_SUCCESS, when call was successful
 * @return EXIT_FAILURE, when call was unsuccessful
 *
 * This function call creates a string for a crontab
 * entry. The  users has the to copy this string and put
 * it in its own crontab file manually (Will be improved).
 * 
 * The string is always the same and will setup a call to
 * Manfreds script at a certain, but fixed time (07:00 GMT).
 *  
 */

int createCronJob() {
    char addCronEntry[128] = "(crontab -l 2>/dev/null; echo \"*/5 * * * * /ganysyslogs/path/to/job -with args\") | crontab -";
    if (system(addCronEntry)) {
        printf("Could not create crontab entry\n");
        return EXIT_FAILURE;
    }
    printf("Check Cronjobs at terminal prompt with 'crontab -e'; quit with ':q!'\n");
    return EXIT_SUCCESS;
}

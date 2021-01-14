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
 * This function call creates an entry in the users
 *  crontab file. This is done by a system call.
 * 'system' commands issue a given string at the prompt
 * and are always critical. It should be avoided to let
 * the user create this string; therefore this string
 * should be fixed and unchangeable.
 * 
 * The function  will setup a cronjob entry that starts
 * Manfreds script at a certain, but fixed time (07:00 GMT).
 *  
 */

int createCronJob() {
    // char addCronEntry[128] = "(crontab -l 2>/dev/null; echo \"*/7 * * * * /ganysyslogs/path/to/manfreds_script -with args\") | crontab -";
    char addCronEntry[128] = "(crontab -l 2>/dev/null; echo \"0 10 * * * /home/jaede.manfred/diff.py\") | sort -u | crontab -";
    if (system(addCronEntry)) {
        printf("Could not create crontab entry\n");
        return EXIT_FAILURE;
    }
    printf("Check Cronjobs at terminal prompt with 'crontab -l'\n");
    return EXIT_SUCCESS;
}

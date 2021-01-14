/**
 * Copyright November 2020: Georg Pohl, 70174 Stuttgart
 * File: deleteCronJob.c
 * ---------------------
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * Implementation notes: int deleteCronJob(void)
 * ---------------------------------------------
 * @brief deletes a cronjob entry from AIX Unix crontab
 * @param (void)
 * @return EXIT_SUCCESS, when call was successful
 * @return EXIT_FAILURE, when call was unsuccessful
 *
 * This function deletes a before created cronjob entry.
 *  
 */

int deleteCronJob() {
    char deleteCronEntry[128] = "crontab -l 2>&1 | grep -v diff.py |  sort | uniq | crontab -";
    if (system(deleteCronEntry)) {
        printf("Could not create crontab entry\n");
        return EXIT_FAILURE;
    }
    printf("Check Cronjobs at terminal prompt with 'crontab -l'\n");
    return EXIT_SUCCESS;
}
/*
(crontab -l ; echo "0 * * * * hupChannel.sh") 2>&1 | grep -v "no crontab" | grep -v hupChannel.sh |  sort | uniq | crontab -
(crontab -l ; echo "0 * * * * hupChannel.sh") 2>&1 | grep -v diff.py |  sort | uniq | crontab -
*/

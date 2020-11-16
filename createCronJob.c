#include <stdio.h>
#include <stdlib.h>

int createCronJob() {
    char addCronEntry[128] = "(crontab -l 2>/dev/null; echo \"*/5 * * * * /ganysyslogs/path/to/job -with args\") | crontab -";
    if (system(addCronEntry)) {
        return EXIT_FAILURE;
    }
    printf("Check Cronjobs at terminal prompt with 'crontab -e'; quit with ':q!'\n");
    return EXIT_SUCCESS;
}


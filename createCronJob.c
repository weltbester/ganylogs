#include <stdio.h>
#include <stdlib.h>

int createCronJob() {
    char addCronEntry[128] = "(crontab -l 2>/dev/null; echo \"*/5 * * * * /ganysyslogs/path/to/job -with args\") | crontab -";
    if (system(addCronEntry)) {
        printf("Could not create crontab entry\n");
        return EXIT_FAILURE;
    }
    printf("Check Cronjobs at terminal prompt with 'crontab -e'; quit with ':q!'\n");
    return EXIT_SUCCESS;
}
/* more information
-e UserName	Edits a copy of the user's crontab file or creates an empty file to edit if the crontab file does not exist for a valid UserName. When editing is complete, the file is copied into the crontab directory as the user's crontab file.
-l UserName	Lists the user's crontab file.
-r UserName	Removes the user's crontab file from the crontab directory.
-v UserName	Lists the status of the user's cron jobs.

OP's solution has a bug, it might allow entries to be added twice, use below to fix.

(crontab -l ; echo "0 * * * * your_command") | sort - | uniq - | crontab -
###
To Add something to cron

(crontab -l ; echo "0 * * * * hupChannel.sh") 2>&1 | grep -v "no crontab" | sort | uniq | crontab -
To remove this from cron

(crontab -l ; echo "0 * * * * hupChannel.sh") 2>&1 | grep -v "no crontab" | grep -v hupChannel.sh |  sort | uniq | crontab -
hope would help someone
###
(crontab -u USERNAME -l ; echo "line to be added") | crontab -u USERNAME -
...or (although directly editing crontab files is not recommended):

echo "line to be added" >> /var/spool/cron/crontabs/USERNAME
###
*/


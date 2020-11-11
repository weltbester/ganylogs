#include <stdlib.h>

int createCronJob() {
    char addCronEntry[128] = "(crontab -l 2>/dev/null; echo \"*/5 * * * * /path/to/job -with args\") | crontab -";
    if (system(addCronEntry)) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
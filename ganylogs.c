/** 
 * Copyright October 2020: Georg Pohl, 70174 Stuttgart
 * File: ganylogs.c
 * ----------------
 * This program can be used to find unknown syslog messages,
 * when you introduce a new router software. It is meant to
 * be used durch den Product Validation (PV) time only.
 * Therefore you feed the program with the router hostnames,
 * so that it can browse through the recent logfile and grep
 * out every syslog message of the before defined hosts.
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


int main(int argc, const char **argv) {

  return EXIT_SUCCESS;
}

/* FUNCTIONS */

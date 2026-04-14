/**
* @file chipper_common.c
*/

#include "chipper_common.h"
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void chipper_die(const char *msg) {
    fprintf(stderr, "chipper error: %s: %s\n", msg, strerror(errno));
    exit(EXIT_FAILURE);
}

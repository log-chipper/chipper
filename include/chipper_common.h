/**
* @file chipper_common.h
* @brief Common definitions and small helpers
*/

#ifndef CHIPPER_COMMON_H
#define CHIPPER_COMMON_H

#include <stdio.h>

#define CHIPPER_BUFFER_SIZE 4096

typedef struct {
    const char *socket_path;
    const char *log_path;
} ChipperOptions;

void chipper_die(const char *msg);

#endif // CHIPPER_COMMON_H

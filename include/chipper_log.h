/**
* @file chipper_log.h
* @brief Low-level log output
*/

#ifndef CHIPPER_LOG_H
#define CHIPPER_LOG_H

#include <stdio.h>

typedef struct {
    const char *path;
    FILE *file;
} ChipperLog;

int chipper_log_open(ChipperLog *log, const char *path);
void chipper_log_close(ChipperLog *log);
int chipper_log_write(ChipperLog *log, const char *timestamp, const char *line);

#endif // CHIPPER_LOG_H

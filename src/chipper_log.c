/**
* @file chipper_log.c
*/

#include "chipper_log.h"
#include "chipper_common.h"
#include <string.h>

/**
 * @brief Opens a chipper log file
*/
int chipper_log_open(ChipperLog *log, const char *path) {
    memset(log, 0, sizeof(*log));
    log->path = path;
    log->file = fopen(path, "a");
    if (!log->file) return -1;

    return 0;
}

/**
 * @brief Closes a chipper log file
 * @param log Pointer to ChipperLog
*/
void chipper_log_close(ChipperLog *log) {
    if (log->file) {
        fclose(log->file);
        log->file = NULL;
    }
}

/**
* @brief Writes to a chipper log
*/
int chipper_log_write(ChipperLog *log, const char *timestamp, const char *line) {
    if (!log->file) return -1;
    if (fprintf(log->file, "[%s] %s\n", timestamp, line) < 0) return -1;

    fflush(log->file);
    return 0;
}

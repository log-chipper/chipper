/**
 * @file main.c
 * @author Darwin Cereska (darwin@darwincereska.dev)
 */

#include "chipper_daemon.h"
#include "chipper_common.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <socket_path> <log_file>\n", argv[0]);
        return 1;
    }

    ChipperOptions opts = {
        .socket_path = argv[1],
        .log_path = argv[2],
    };

    return chipper_run_daemon(&opts);
}

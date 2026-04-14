/**
 * @file chipper_daemon.c
 * @author Darwin Cereska (darwin@darwincereska.dev)
 */

#include "chipper_daemon.h"
#include "chipper_log.h"
#include "chipper_common.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

typedef struct {
    const char *socket_path;
    int sock_fd;
    ChipperLog log;
} ChipperDaemon;

static void get_iso8601_utc(char *buf, size_t len) {
    time_t now = time(NULL);
    struct tm t;
    gmtime_r(&now, &t);
    strftime(buf, len, "%Y-%m-%dT%H:%M:%SZ", &t);
}

static void daemon_cleanup(ChipperDaemon *d) {
    if (d->sock_fd >= 0) {
        close(d->sock_fd);
        d->sock_fd = -1;
    }

    if (d->socket_path) {
        unlink(d->socket_path);
    }

    chipper_log_close(&d->log);
}

int chipper_run_daemon(const ChipperOptions *opts) {
    ChipperDaemon d;
    memset(&d, 0, sizeof(d));
    d.socket_path = opts->socket_path;
    d.sock_fd = -1;

    // Open the log
    if (chipper_log_open(&d.log, opts->log_path) != 0) {
        chipper_die("open log file");
    }

    // Open the socket
    d.sock_fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (d.sock_fd == -1) {
        chipper_die("socket");
    }

    unlink(d.socket_path);

    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, d.socket_path, sizeof(addr.sun_path) - 1);

    if (bind(d.sock_fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        daemon_cleanup(&d);
        chipper_die("bind");
    }

    fprintf(stderr, "Chipper listening on %s, writing to %s\n", d.socket_path, d.log.path);

    char buf[CHIPPER_BUFFER_SIZE];
    char ts[64];

    for (;;) {
        ssize_t n = recvfrom(d.sock_fd, buf, sizeof(buf) - 1, 0, NULL, NULL);
        if (n == -1) {
            if (errno == EINTR) {
                continue;
            }
            perror("recvfrom");
            break;
        }

        buf[n] = '\0';

        size_t len = strlen(buf);
        if (len > 0 && buf[len - 1] == '\n') {
            buf[len - 1] = '\0';
        }

        get_iso8601_utc(ts, sizeof(ts));

        if (chipper_log_write(&d.log, ts, buf) != 0) {
            fprintf(stderr, "failed to write log line\n");
        }
    }

    daemon_cleanup(&d);
    return 0;
}

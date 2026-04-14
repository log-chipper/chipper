/**
* @file chipper_client.c
* @brief The C client sdk for connecting to the Chipper Socket
*/

#include "chipper_client.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define CHIPPER_CLIENT_BUFFER 2048

static int chipper_fd = -1;
static struct sockaddr_un chipper_addr;
static char chipper_service[64];
static char chipper_source[64];

int chipper_client_init(const char *socket_path, const char *service, const char *source) {
    if (chipper_fd != -1) return 0; // Already initialized

    chipper_fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (chipper_fd == -1) {
        perror("chipper_client socket");
        return -1;
    }

    memset(&chipper_addr, 0, sizeof(chipper_addr));
    chipper_addr.sun_family = AF_UNIX;
    strncpy(chipper_addr.sun_path, socket_path, sizeof(chipper_addr.sun_path) - 1);
    strncpy(chipper_service, service, sizeof(chipper_service) -1);
    chipper_service[sizeof(chipper_service) - 1] = '\0';

    strncpy(chipper_source, source, sizeof(chipper_source) - 1);
    chipper_source[sizeof(chipper_source) - 1] = '\0';

    return 0;
}

void chipper_client_close(void) {
    if (chipper_fd != -1) {
        close(chipper_fd);
        chipper_fd = -1;
    }
}

int chipper_client_log(const char *level, const char *fmt, ...) {
    if (chipper_fd == -1) {
        errno = EBADF;
        return -1;
    }

    char msg_buf[CHIPPER_CLIENT_BUFFER];
    char final_buf[CHIPPER_CLIENT_BUFFER];

    va_list args;
    va_start(args, fmt);
    vsnprintf(msg_buf, sizeof(msg_buf), fmt, args);
    va_end(args);

    snprintf(final_buf, sizeof(final_buf), 
        "level=%s service=%s source=%s msg=\"%s\"",
        level, chipper_service, chipper_source, msg_buf
    );

    ssize_t n = sendto(chipper_fd, final_buf, strlen(final_buf), 0, (struct sockaddr *)&chipper_addr, sizeof(chipper_addr));
    if (n == -1) {
        perror("chipper_client sendto");
        return -1;
    }

    return 0;
}

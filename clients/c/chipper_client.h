/**
* @file chipper_client.h
* @brief The C client sdk for connecting to the Chipper Socket
*/

#ifndef CHIPPER_CLIENT_H
#define CHIPPER_CLIENT_H

int chipper_client_init(const char *socket_path, const char *service, const char *source);

void chipper_client_close(void);

int chipper_client_log(const char *level, const char *fmt, ...);

#endif // CHIPPER_CLIENT_H

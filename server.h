#ifndef SERVER_H
#define SERVER_H

#define SERVER_PORT 1234

#include <netinet/in.h>

struct Server
{
    int fd_socket;
    struct sockaddr_in saddr_in;
    int max_clients;
};

int server_init(struct Server* server);

int server_add_endpoint(struct Server* server, const char* endpoint_name);

int server_start(struct Server* server);

#endif
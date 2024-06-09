#include "server.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <unistd.h>

int server_init(struct Server* server)
{
    server->fd_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server->fd_socket == -1)
    {
        printf("%s\n", strerror(errno));
        return -1;
    }

    server->saddr_in.sin_family = AF_INET;
    server->saddr_in.sin_addr.s_addr = htonl(INADDR_ANY);
    server->saddr_in.sin_port = htons(SERVER_PORT);

    if (bind(server->fd_socket, (struct sockaddr*)&server->saddr_in, sizeof(server->saddr_in)) == -1)
    {
        printf("%s\n", strerror(errno));
        return -1;
    }

    return 0;
}

// TODO
int server_add_endpoint(struct Server* server, const char* endpoint_name)
{
    return 0;
}

int server_start(struct Server* server)
{
    if (listen(server->fd_socket, 5) == -1)
    {
        printf("%s\n", strerror(errno));
        return -1;
    }

    int client = accept(server->fd_socket, (struct sockaddr*)NULL, NULL);
    if (client == -1)
    {
        printf("%s\n", strerror(errno));
        return -1;
    }

    int sent_bytes = send(client, "Hello world\n", sizeof("Hello world\n"), 0);
    if (sent_bytes == -1)
    {
        printf("%s\n", strerror(errno));
        return -1;
    }
    else if (sent_bytes < sizeof("Hello world\n"))
    {
        printf("All bytes %ld\n", sizeof("Hello world\n"));
        printf("Sent bytes %d\n", sent_bytes);
        return -1;
    }

    close(server->fd_socket);
    
    return 0;
}

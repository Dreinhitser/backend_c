#include "server.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>

int clients_number = 0;
pthread_mutex_t m;

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

void handle_client(int fd_client)
{
    char buffer[1024];
    int recv_bytes = recv(fd_client, buffer, sizeof(buffer), NULL);
    if (recv_bytes == -1)
    {
        printf("Error(handle_client): %s\n", strerror(errno));
        pthread_mutex_lock(&m);
        if (clients_number > 0)
        {
            clients_number--;
        }
        pthread_mutex_unlock(&m);
        return;
    }

    int send_bytes = send(fd_client, "Hello world\n", sizeof("Hello world\n"), NULL);
    if (send_bytes == -1)
    {
        printf("Error(handle_client): %s\n", strerror(errno));
        pthread_mutex_lock(&m);
        if (clients_number > 0)
        {
            clients_number--;
        }
        pthread_mutex_unlock(&m);
        return;
    }

    printf("Successfully closing function handle_client\n");
    pthread_mutex_lock(&m);
    if (clients_number > 0)
    {
        clients_number--;
    }
    pthread_mutex_unlock(&m);
}

int server_start(struct Server* server)
{
    pthread_mutex_init(&m, NULL);
    while (1)
    {
        if (listen(server->fd_socket, 5) == -1)
        {
            printf("%s\n", strerror(errno));
            return -1;
        }

        int fd_client = accept(server->fd_socket, (struct sockaddr*)NULL, NULL);
        if (fd_client == -1)
        {
            printf("%s\n", strerror(errno));
            return -1;
        }
        pthread_t thread;
        pthread_create(&thread, NULL, handle_client, fd_client);
        pthread_detach(thread);
    }

    pthread_mutex_destroy(&m);
    close(server->fd_socket);
    
    return 0;
}

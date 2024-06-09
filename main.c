#include <stdio.h>
#include <stdlib.h>

#include "server.h"

int main(int argc, char* argv[])
{
    struct Server server;
    server.max_clients = 5;

    if (server_init(&server) == -1)
    {
        printf("Error: server_init\n");
        return EXIT_FAILURE;
    }
    
    if (server_start(&server) == -1)
    {
        printf("Error: server_start\n");
        return EXIT_FAILURE;
    }

    printf("Server finished\n");
    return EXIT_SUCCESS;
}
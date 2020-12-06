#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#define LOCATION "/tmp/uds.ipc"
#define BUFFSIZE 1024

static int server_socket = -1;
static int client_socket = -1;
static int res = -1;
static int bytes_read = -1;

int main(int argc, char const *argv[])
{
    server_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (-1 == server_socket)
    {
        perror("Socket formation failed");
        exit(1);
    }

    if (!access(LOCATION, F_OK))
    {
        res = unlink(LOCATION);
        if (-1 == res)
        {
            perror("Unlinking failed");
            exit(1);
        }
    }

    const struct sockaddr addr = {AF_UNIX, LOCATION};
    res = bind(server_socket, &addr, sizeof addr);
    if (-1 == res)
    {
        perror("Bind failed");
        exit(1);
    }

    res = listen(server_socket, 1);
    if (-1 == res)
    {
        perror("Listen failed");
        exit(1);
    }

    struct sockaddr client_addr;
    int client_addr_len = sizeof client_addr;
    char buffer[BUFFSIZE] = {};
    client_socket = accept(server_socket, &client_addr, &client_addr_len);
    if (-1 == client_socket)
    {
        perror("Accept failed");
        exit(1);
    }
    while (client_socket)
    {
        while (read(client_socket, buffer, BUFFSIZE))
        {
            u_int8_t len = (u_int8_t)buffer[0];
            printf("%u", len);
        }
        printf("\n");
        client_socket = accept(server_socket, &client_addr, &client_addr_len);
        if (-1 == client_socket)
        {
            perror("Accept failed");
            exit(1);
        }
    }

    return 0;
}

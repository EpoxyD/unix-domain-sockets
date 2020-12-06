#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define LOCATION "/tmp/uds.ipc"

static int client_socket = -1;
static int res = -1;

int main(int argc, char const *argv[])
{
    client_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (-1 == client_socket)
        perror("Socket formation failed");

    const struct sockaddr addr = {AF_UNIX, LOCATION};
    res = connect(client_socket, &addr, sizeof addr);
    if (-1 == client_socket)
        perror("Connection failed");

    u_int8_t len = 12;
    char *output = calloc(1, sizeof len);
    memcpy(output, &len, sizeof len);
    write(client_socket, output, sizeof len);

    return 0;
}

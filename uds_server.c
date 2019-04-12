#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/un.h>

#define SOCK_PATH "/tmp/uds"

int main(void) {
    int server_socket, client_socket;
    struct sockaddr_un addr, client_addr;

    size_t addr_size = sizeof(client_addr);

    if ((server_socket = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, SOCK_PATH);

    if (bind(server_socket, (struct sockaddr *) &addr, strlen(addr.sun_path) + sizeof(addr.sun_family)) == -1) {
        perror("bind");
        exit(1);
    }

    if (listen(server_socket, 5) == -1) {
        perror("listen");
        exit(1);
    }

    for (;;) {
        int done, n;
        printf("Waiting for a connection...\n");

        if ((client_socket = accept(server_socket,
                                    (struct sockaddr *) &client_addr, (socklen_t *) &addr_size)) == -1) {
            perror("accept");
            exit(1);
        }

        printf("Connected.\n");

        char str[100];
        done = 0;
        do {
            n = recv(client_socket, str, 100, 0);
            if (n <= 0) {
                if (n < 0) perror("recv");
                done = 1;
            }

            if (!done)
                if (send(client_socket, str, n, 0) < 0) {
                    perror("send");
                    done = 1;
                }
        } while (!done);

        close(client_socket);
    }

    return 0;
}
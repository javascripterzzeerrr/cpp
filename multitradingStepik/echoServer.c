#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char **argv) {
    int dSocket = socket(
        AF_INET,
        SOCK_STREAM,
        0
    );

    struct sockaddr_in SockAddr;
    SockAddr.sin_family = AF_INET;
    SockAddr.sin_port = htons(12345);
    SockAddr.sin_addr.s_addr = htonl(INADDR_ANY); // IP-adress, INADDR_ANY - 0.0.0.0

    bind(dSocket, (struct sockaddr *)&SockAddr, sizeof(SockAddr)); // привязка сокета к определенному ip и порту

    listen(dSocket, SOMAXCONN);

    while(1) {
        int SlaveSocket = accept(dSocket, 0, 0);

        int Buffer[5] = { 0, 0, 0, 0, 0 };
        recv(SlaveSocket, Buffer, 4, MSG_NOSIGNAL);
        send(SlaveSocket, Buffer, 4, MSG_NOSIGNAL);
        shutdown(SlaveSocket, SHUT_RDWR);
        close(SlaveSocket);
        printf("%s\n", Buffer);
    }

    return 0;
}

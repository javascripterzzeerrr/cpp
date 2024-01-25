#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char **argv) {
    int Socket = socket(
        AF_INET,
        SOCK_STREAM,
        0
    );

    struct sockaddr_in SockAddr;
    SockAddr.sin_family = AF_INET;
    SockAddr.sin_port = htons(12345);
    SockAddr.sin_addr.s_addr = htonl(INADDR_ANY); // IP-adress, INADDR_ANY - 0.0.0.0

    connect(Socket, (struct sockaddr *)&SockAddr, sizeof(SockAddr));

    char buffer[] = "PING";
    send(Socket, buffer, 4, MSG_NOSIGNAL);
    recv(Socket, buffer, 4, MSG_NOSIGNAL);

    shutdown(Socket, SHUT_RDWR);
    close(Socket);

    printf("%s\n", buffer);

    return 0;
}

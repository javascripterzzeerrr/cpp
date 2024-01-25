#include <iostream>
#include <sys/socket.h>
#include <winsocket.h>

/*

socket(domain, type, protocol)

domain:
    AF_INET - IPv4
    AF_INET6 - IPv6
    AF_UNIX - создание файла, клиенты присоединяются к файлу (серверу)

type:
    sock_STREAM - TCP
    sock_DGRAM - UDP

protocol:
    0 - протокол по умолчанию
*/

/*
    После того как мы создали сокет мы должны привязать его
    к определенному IP адресу и порту

    Привязка ip к сокету
    bind(s, (struct sockaddr *)sa, sizeof(&a));

    IPv4:
        struct sockaddr_in sa;
        sa.sin_family = AF_INET;
        // so.sin_port = 12345; // port - bad
        sa.sin_port = htnos(12345); - good
        sa.sin_addr.s_addr = INADDR_LOOPBACK (127.0.0.1)
        INARRD_ANY (0.0.0.0)

    UNIX:
        struct sockaddr_un sa;
        sa.sin_family = AF_UNIX;
        strcpy(sa.sun_path, "tmp/a.sock"); // путь к файлу

*/

/*
    listen(s, SOMAXCONN); //listen socket - второй параметр длина очереди (128)
    // принимает пользователей
    // s1 - socket, 0,0 - данные пользователя (ip адрес)
    while (s1 = accept(s, 0, 0)) {

    }

*/

/*
    После того, как соединение установлено, 
    начинаем принимать и отправлять данные
    
    site_t read(int fd, void *buf, size_t count);

    size_t write(int fd, void *buf, size_t count);

    // если прочитать или записать в соединии, 
    // которое порвано, то получим сигнал - SIGPIPE

    // игнорирование SIGPIPE
    signal(SIGPIPE, SIG_IGN);


    // правильно:
    size_t recv(int fd, void * buf, size_t count, int flags);
    size_t send(int fd, void * buf, size_t count, int flags);

*/

#define DOMAIN AF_INET

void serverRun() {
    int mySocket = socket(DOMAIN, SOCK_STREAM, 0);


}

int main() {
    // TCP echo server IPv4

    int dSocket = socket(DOMAIN, SOCK_STREAM, 0);

    struct sockaddr_in sa;
    sa.sin_family = AF_INET;
    sa.sin_port = ntohs(12345);

    int client = 




    return 0;
}
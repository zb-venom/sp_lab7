#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <stdio.h>

void error(const char* msg);

int main(int argc, char* argv[]) {
    int sock, length, n;
    socklen_t fromlen;
    struct sockaddr_in server;
    struct sockaddr_in from;
    char buf[1024];
    if (argc < 2) { fprintf(stderr, "ERROR, no port provided\n"); exit(0); }
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) error("Opening socket");
    length = sizeof(server);
    bzero(&server, length);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(atoi(argv[1]));
    if (bind(sock, (struct sockaddr*)&server, length) < 0) error("binding");
    fromlen = sizeof(struct sockaddr_in);
    while (1) {
		bzero(buf, 1024);
        n = recvfrom(sock, buf, 1024, 0, (struct sockaddr*)&from, &fromlen);
        if (n < 0) error("recvfrom");
        write(1, "> ", 2);
        write(1, buf, n);
        n = sendto(sock, "message reached\n", 16, 0, (struct sockaddr*)&from, fromlen);
        if (n < 0) error("sendto");
    }
    return 0;
}

void error(const char* msg)
{
    perror(msg);
    exit(0);
}

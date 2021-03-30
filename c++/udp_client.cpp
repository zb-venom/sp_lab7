#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <netdb.h> 
#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h>
#include <time.h>

void error(const char*);

int main(int argc, char* argv[]) {
    int sock, n;
    unsigned int length;
    struct sockaddr_in server, from;
    struct hostent* hp;
    char buffer[256];
    if (argc != 3) { printf("Usage: server port\n"); exit(1); }
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) error("socket");
    server.sin_family = AF_INET;
    hp = gethostbyname(argv[1]);
    if (hp == 0) error("Unknown host");
    bcopy((char*)hp->h_addr, (char*)&server.sin_addr, hp->h_length);
    server.sin_port = htons(atoi(argv[2]));
    length = sizeof(struct sockaddr_in);
    while(1) {
    	srand(time(0));
		float data1 = (float) rand() / 100000;
		float data2 = (float) rand() / 100000;
		float data3 = (float) rand() / 100000;
		printf("you > x: %f, y: %f, z: %f\n", data1, data2, data3);
		sprintf(buffer, "x: %f, y: %f, z: %f\n", data1, data2, data3);
		n = sendto(sock, buffer, strlen(buffer), 0, (const struct sockaddr*)&server, length);
		if (n < 0) error("Sendto");
		if (n < 0) error("recvfrom");
		//n = recvfrom(sock, buffer, 256, 0, (struct sockaddr*)&from, &length);
		//write(1, "server > ", 9);
		//write(1, buffer, n);
		sleep(1);
	}
    close(sock);
    return 0;
}

void error(const char* msg)
{
    perror(msg);
    exit(0);
}

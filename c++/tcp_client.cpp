#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <time.h>

void error(const char*);

int main(int argc, char* argv[]) {
    int sockfd, servlen, n;
    struct sockaddr_un serv_addr;
    char buffer[100];
    bzero((char*)&serv_addr, sizeof(serv_addr));
    serv_addr.sun_family = AF_UNIX;
    strcpy(serv_addr.sun_path, argv[1]);
    servlen = strlen(serv_addr.sun_path) + sizeof(serv_addr.sun_family);
    if ((sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) error("Creating socket");
    if (connect(sockfd, (struct sockaddr*)&serv_addr, servlen) < 0) error("Connecting");
    printf("Connecting to the server...\n");
    while(1) {
    	srand(time(0));
    	//int data = rand() % 89000 + 10;
		//printf("you > %d\n", data);
		//sprintf(buffer, "%d\n", data);
		printf("you > ");
		bzero(buffer, 82);
		fgets(buffer, 80, stdin);
		write(sockfd, buffer, strlen(buffer)); 		
		write(1, "server > ", 9);
    	n = read(sockfd,buffer,100);
		write(1, buffer, n); 
		//sleep(1);
	}
    close(sockfd);
    return 0;
}

void error(const char* msg)
{
    perror(msg);
    exit(0);
}


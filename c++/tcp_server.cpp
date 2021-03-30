#include <iostream>
#include <sys/types.h> 
#include <sys/socket.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <sys/un.h> 
#include <stdio.h>
#include <ctime>
#include <cstring>

using namespace std;

void error(const char *);

int main(int argc, char *argv[]) {
	int sockfd, newsockfd, servlen, n; 
	socklen_t clilen;
	struct sockaddr_un cli_addr, serv_addr; 
	char buf[80];	
	if ((sockfd = socket(AF_UNIX,SOCK_STREAM,0)) < 0)  error("creating socket");
	bzero((char *) &serv_addr, sizeof(serv_addr)); 
	serv_addr.sun_family = AF_UNIX;
	strcpy(serv_addr.sun_path, argv[1]); 
	servlen=strlen(serv_addr.sun_path) + sizeof(serv_addr.sun_family); 
	if(bind(sockfd,(struct sockaddr *)&serv_addr,servlen)<0) error("binding socket");
	listen(sockfd, 5);
	clilen = sizeof(cli_addr); 
	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen); 
	if (newsockfd < 0) error("accepting"); 
	cout << "Client connected\n";
	while(1) {
		bzero(buf, 80);
		n = read(newsockfd, buf, 80);
		cout << "> " << buf;
		write(newsockfd, "message reached\n", 16); 
	}
	close(newsockfd);
	close(sockfd); 
	return 0;
}

void error(const char *msg) {
	perror(msg); 
	exit(0);
}



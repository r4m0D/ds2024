#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define BUF_SIZE 1024

int main() {
	// Define IP address and port - server
	char *ip = "127.0.0.1";
	int port = 8080;
	int e; // connection status returned

	int sockfd;
	struct sockaddr_in server_addr, new_addr;
	socklen_t addr_size;
	char buffer[BUF_SIZE];

	// Create socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		perror("[-]Error in socket!");
		exit(1);
	}
	printf("[+]Server socket created successfully!\n");

	// Define server address
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = port;
	server_addr.sin_addr.s_addr = inet_addr(ip);

	// Bind the socket
	e = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
	if (e < 0) {
		perror("[-]Error in bind!");
		exit(1);
	}
	printf("[+]Binding successfull.\n");

	// Listen for connections
	if (listen(sockfd, 10) == 0) { // 10 is the maximum size of queue - connections -> serve 10 people at a time 
		printf("[+]Listening....\n");
	} else {
		perror("[-]Error in listening!");
		exit(1);
	}

	// Accept a connection
	addr_size = sizeof(new_addr);
	int new_sock = accept(sockfd, (struct sockaddr*)&new_addr, &addr_size);
	printf("[+]Connection accepted from %s:%d\n", inet_ntoa(new_addr.sin_addr), ntohs(new_addr.sin_port));

	return 0;
	}
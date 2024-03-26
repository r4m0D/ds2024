#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define BUF_SIZE 1024

int main() {
	// Define IP address and port - server
	char *ip = "127.0.0.1";
	int port = 8080;
	int e; // connection status returned

	int sockfd; // Socket file descriptor
	struct sockaddr_in server_addr; // Server address structure

	// Create socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	// AF_INET - IPv4 (address family), SOCK_STREAM - TCP (type of socket), 0 - IP (protocol)
	if (sockfd < 0) {
		perror("[-]Error in socket!");
		exit(1);
	}
	printf("[+]Server socket created successfully!\n");

	// Socket address cpnfiguration        
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = port;
	server_addr.sin_addr.s_addr = inet_addr(ip);

	// Connect to the server
	e = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
	if (e) { // e -> != 0 -> error
		perror("[-]Error in socket!");
		exit(1);
	}
	printf("[+]Connected to Server.\n");

	return 0;
}
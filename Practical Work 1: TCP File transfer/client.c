#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define BUF_SIZE 1024

void send_file(FILE *fp, int sockfd) {
  int n;
  char data[BUF_SIZE] = {0};
 
  while(fgets(data, BUF_SIZE, fp) != NULL) {
    if (send(sockfd, data, sizeof(data), 0) == -1) {
      perror("[-]Error in sending file.");
      exit(1);
    }
    bzero(data, BUF_SIZE);
  }
}

int main() {
	// Define IP address and port - server
	char *ip = "127.0.0.1";
	int port = 8080;
	int e; // connection status returned

	int sockfd; // Socket file descriptor
	struct sockaddr_in server_addr; // Server address structure
	FILE *fp; // File pointer
	char *filename = "send.txt"; // File name

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

	// Open file
	fp = fopen(filename, "r");
	if (fp == NULL) {
		perror("[-]Error in reading file.");
		exit(1);
	}
	printf("[+]File opened successfully.\n");

	// Send file
	send_file(fp, sockfd);
	printf("[+]File data sent successfully.\n");

	// Close the connection
	printf("[+]Closing the connection.\n");
	close(sockfd);

	return 0;
}
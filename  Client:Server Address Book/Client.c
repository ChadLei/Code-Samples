#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h> // system call data types
#include <sys/socket.h> // socket structures definition
#include <netinet/in.h> // consts and structs for internet domain addresses 
#include <netdb.h> // hostent structure
#include <arpa/inet.h>

#define h_addr h_addr_list[0]

int main( int argc, char* argv[]){

	// gcc Lab4_client.c -o client
	// or
	// gcc Lab4_client.c -std=c99 -o client
	// ./client localhost 30000

	// create a socket.
	int sockfd, port;
	struct sockaddr_in serv_addr;
	struct hostent *server; // diff from server
	char buffer[256];
     
    //unsigned char formattedMsg[256];
    char *formattedMsg = (char*) malloc(256 * sizeof(char));


	while (strcmp(buffer,"+++\n")){
		// bind to an address
		port = atoi(argv[2]);
		sockfd = socket(AF_INET, SOCK_STREAM,0);
		server = gethostbyname(argv[1]); // diff from server
		bzero((char*) &serv_addr, sizeof(serv_addr));
		serv_addr.sin_family = AF_INET;
		bcopy ((char*) server->h_addr, 
			   (char*) &serv_addr.sin_addr.s_addr, 
			   server->h_length);
		serv_addr.sin_port = htons(port);

		// check errno for cause of error 
		if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    		return -1; 

		// connect to a server.
		connect(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr));

		// send/recv - repeat until we have or receive data
		// printf("> ");
		// bzero(buffer, 256);
		// fgets(buffer, 255, stdin);
		// write(sockfd, buffer, strlen(buffer));
		// printf("%s\n", buffer );
	
		printf("> ");
		bzero(buffer, 256);
		fgets(buffer, 255, stdin);

		// formatting (packing) the message:
		// 1st byte: size of message
		// 2nd byte: the message
		formattedMsg[0] = strlen(buffer)-1;
		for (int i = 0; i < strlen(buffer)-1; i++){ // -1 gets rid of \n character
			formattedMsg[i+1] = buffer[i];
		}

		//write(sockfd, buffer, strlen(buffer));
		write(sockfd, formattedMsg, formattedMsg[0]+1);
		if (strcmp(buffer, "+++\n")== 0)
		{
			close(sockfd);
			break;
		} else {
			read(sockfd, buffer, 256);
			printf("%s\n", buffer );
		}
	}

	// close to releases data.
	close(sockfd);


	// MY OWN









	return 0;

}
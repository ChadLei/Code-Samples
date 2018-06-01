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

// PURPOSE:
// A networked client/server application which allows a client program to
// query a simple database which is managed by a server program. The client program
// sends a query message containing an email address to the server, and the server
// responds by sending back a message containing the name of the user who has that
// email address. For example, if the client sends a message containing the email
// address “harris@ics.uci.edu” then the server should return the name “Ian G. Harris”.


// USER INTERFACE:
// Once running, the server will only accept requests sent from a client over the
// network. When the server receives a request from a client, the server will print the
// email address in the message on the screen on a new line. 
// The server will continue responding to requests and printing the associated email
// addresses until its process is killed externally, for instance by a ctrl-c typed at the
// keyboard. An example of the printed
// output of the server when communicating with the client is shown below.

// Address server started
// harris@ics.uci.edu
// joe@cnn.com


// HOW TO RUN:
// 1. gcc server.c -o server
// or (whichever works)
// 2. gcc server.c -std=c99 -o server
// 3. ./server 3000 & (any number is sufficient)


// TO DELETE BACKGROUND PROCESS(ES):
// 1. fg - brings to foreground
// 2. ctrl+c - ends process


// Address Database
struct personInfo {
	char name[50];
	char email[100];
};


int main( int argc, char* argv[]){
	

	// hardcoding address database
	struct personInfo arrayOfInfo[50]; // array that holds all the info of people
	struct personInfo Ian;
	strcpy(Ian.name, "Ian G. Harris");
	strcpy(Ian.email, "harris@ics.uci.edu");
	arrayOfInfo[0] = Ian;

	struct personInfo Joe;
	strcpy(Joe.name, "Joe Smith");
	strcpy(Joe.email, "joe@cnn.com");
	arrayOfInfo[1] = Joe;

	struct personInfo Jane;
	strcpy(Jane.name, "Jane Smith");
	strcpy(Jane.email, "jane@slashdot.org");
	arrayOfInfo[2] = Jane;

	// create a socket
	int sockfd, newsockfd, portno;
	socklen_t clilen;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	int n;

	// AF_INET is an address family that is used to designate 
	// the type of addresses that your socket can communicate with 
	// (in this case, Internet Protocol v4 addresses).
	
	// bind to an address
	sockfd = socket(AF_INET, SOCK_STREAM, 0); // 
	bzero((char*) &serv_addr, sizeof(serv_addr));
	portno = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;  
	serv_addr.sin_port = htons(portno);
	bind(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr));

	printf("%s\n", "Address server started" );

	// listen on a port, and wait for a connection to be established.
	listen(sockfd, 5);

	while (1){
		// accept the connection from a client.
		clilen = sizeof(cli_addr);
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

		if (newsockfd < 0) {
			perror("ERROR on accept");
    		exit(1);
		}

		// send/recv - the same way we read and write for a file.
		bzero(buffer, 256);
		n = read(newsockfd, buffer, 256);
		if (n < 0) {
			perror("ERROR reading from socket");
    		exit(1);
		}

		// unpacks the message
		char receivedMsg[buffer[0]+1];
		bzero(receivedMsg, buffer[0]);
		for (int i = 0; i <= buffer[0]; i++){
			//if (i == buffer[0]) receivedMsg[i] = '\0';
			receivedMsg[i] = buffer[i+1];
		}
		

		int printed = 0;
		for (int i = 0; i < 3; i++){
			if (strcmp(arrayOfInfo[i].email, receivedMsg) == 0) {
				n = write(newsockfd, arrayOfInfo[i].name, 30);
				if (n < 0) {
					perror("ERROR writing to socket");
		    		exit(1);
				}
				printf("%s\n", receivedMsg );
				//printf("%s\n", arrayOfInfo[i].name);
				printed++;
				break;
			}
		}
		if (strcmp("+++", receivedMsg) == 0){
			continue;
		} else if (printed == 0){
			printf("%s\n", receivedMsg );
			n = write(newsockfd, "Unknown", 10);
			//printf("%s\n", "Unknown");
		}

		//n = write(newsockfd, "I got your message", 10);

		sleep(1);
	}

	// close to releases data.
	close(newsockfd);
	close(sockfd);

	return 0;
}

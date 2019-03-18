// Server side C/C++ program to demonstrate Socket programming 

#include <bits/stdc++.h>

#include <string>
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#define PORT 8080 

using namespace std;

void clear(char buf[], int n)
{
	for(int i=0;i<n;i++)
		buf[i] = '\0';
}

int main(int argc, char const *argv[]) 
{ 
	int server_fd, new_socket, valread; 
	struct sockaddr_in address; 
	int opt = 1; 
	int addrlen = sizeof(address); 
	char buffer[1024] = {0}; 
	char *hello = "Hello form Server"; 
	
	// Creating socket file descriptor 
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
	{ 
		perror("socket failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	// Forcefully attaching socket to the port 8080 
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
												&opt, sizeof(opt))) 
	{ 
		perror("setsockopt"); 
		exit(EXIT_FAILURE); 
	} 
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port = htons( PORT ); 
	
	// Forcefully attaching socket to the port 8080 
	if (bind(server_fd, (struct sockaddr *)&address, 
								sizeof(address))<0) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	// listening from the client = server becomes passive until the client connects to the server
	if (listen(server_fd, 3) < 0) 
	{ 
		perror("listen"); 
		exit(EXIT_FAILURE); 
	} 
	
	// actual connection between the server and the client is established
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
					(socklen_t*)&addrlen))<0) 
	{ 
		perror("accept"); 
		exit(EXIT_FAILURE); 
	} 
	printf("Connection established !!\n");
	
	
	// communication ... 	
	while(1)
	{		
		// get the message from the client here
		valread = read( new_socket , buffer, 1024); 
		printf("\t\t\tYour Client has sent :\n\t\t\t%s of size = %d\n", buffer, strlen(buffer)); 
		
		if(strcmp(buffer, "Bye") == 0)
			break;
		
		// get message of server
		string oo;		
		printf("Your reply ? \n");
		std::getline(std::cin, oo);		
		
		//scanf("%[^\n]s",sms);		// ---> oops, doesn't work
		//fflush(stdin);
		char sms[oo.size()+1];
		strcpy(sms, oo.c_str());	// string to char *
		hello = sms;
		
		// send a message to the client here
		send(new_socket , hello , strlen(hello) , 0 ); 	// sending to client
		printf("Message sent\n");
		
		clear(buffer, 1024);
		//cout << "------------ The cleared buffer is : "  << buffer << "\n";		
	}
	return 0; 
} 


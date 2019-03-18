// Client side C/C++ program to demonstrate Socket programming 

#include <bits/stdc++.h>

#include <string.h>
#include <string>
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <arpa/inet.h>
#include <sys/types.h>
#define PORT 8080 

using namespace std;

// To clear the buffer, to make space for next message
void clear(char buf[], int n)
{
	for(int i=0;i<n;i++)
		buf[i] = '\0';	
}


int main(int argc, char const *argv[]) 
{ 
	struct sockaddr_in address; 		// to access the server sock
	int sock = 0, valread; 				// to create the client sock
	struct sockaddr_in serv_addr; 
	char *hello = "Hello from client"; 
	char buffer[1024] = {0}; 
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{ 
		printf("\n Socket creation error \n"); 
		return -1; 
	} 

	memset(&serv_addr, '0', sizeof(serv_addr)); 

	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_port = htons(PORT); 
	
	
	// can take input of the IP from the user as well !!
	char *x, ip[20];
	cout << "enter the IP: ";
	scanf("%s",ip);	
	x = ip;
	
	// Convert IPv4 and IPv6 addresses from text to binary form 
	if(inet_pton(AF_INET, x, &serv_addr.sin_addr)<=0) 
	{ 
		printf("\nInvalid address/ Address not supported \n"); 
		return -1; 
	} 

	// client cnnects to the server from here; (the address is as specified in serv_addr.sin_addr)
	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
	{ 
		// only if not connected
		printf("\nConnection Failed \n"); 
		return -1; 
	} 
	else
		printf("Connection established !!\n\n");
		
	// To get rid of the `\n` obtained after IP is entered
	string dummy;
	getline(cin, dummy);	
		
	// Once connection has been established, you can send any message from the connected socket, `sock` here	
	while(1)
	{		
		
		printf("What's your message ?\n");
		string oo;		
		std::getline(std::cin, oo);

		char sms[oo.size()+1];	
		strcpy(sms, oo.c_str());
		hello = sms;

		// send a message to the server
		send(sock , hello , strlen(hello) , 0 ); 
		printf("Message sent\n"); 
	
		// receive message from the server
		valread = recv( sock , buffer, 1024, 0); 
		printf("\t\t\tYour Server has sent:\n\t\t\t%s of size = %d\n", buffer, strlen(buffer)); 
		
		if(strcmp("Stop", buffer)==0)	// If server sends `Stop`, then quit
			break;
			
		clear(buffer, 1024);
		//cout << "------------ The cleared buffer is : "  << buffer << "\n";			
	}	
	return 0; 
} 


#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include "Cipher.h"

#pragma comment(lib, "Ws2_32")
using namespace std;

int main(int argc, char *argv[]) {
	WSADATA wsa;
	SOCKET s;
	struct sockaddr_in server;
	char *message, server_reply[500];
	int recv_size;
	int return_value;

	cout << "Initialising Winsock...." << endl;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		printf("Failed. Error Code : %d", WSAGetLastError());		
		return 1;
	}

	cout << "Initialised" << endl;

	//Create a socket	
	if ((s = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
		printf("Could not create socket : %d", WSAGetLastError());
	}

	//cout << "socket created" << endl;
	struct addrinfo server_struct, *servinfo, *p;

	memset(&server_struct, 0, sizeof server_struct);
	server_struct.ai_family = AF_UNSPEC;
	server_struct.ai_socktype = SOCK_STREAM;

	if ((return_value = getaddrinfo("204.76.188.23", "23456", &server_struct, &servinfo)) != 0) {
		printf("getaddrinfo: %s\n");
		return 1;

	}

	//set SO_RESESADDR on a socket s to true	
	int optval = 1;
	setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (const char*)&optval, sizeof optval);

	//Send some data	
	//message = "Hello world";
	//if (sendto(s, message, strlen(message), 0, (struct sockaddr*)&server, sizeof(server)) < 0) {
	//	cout << "Send Failed" << endl;
	//	return 1;
	//}

	cout << "Data Sent" << endl;

	//Receive a reply from the server	
	if ((recv_size = recvfrom(s, server_reply, 500, 0, NULL, NULL)) == SOCKET_ERROR) {
		cout << "recv failed" << endl;
		return 1;
	}

	cout << "reply Received" << endl;

	//Add \0 at the end of received string string before printing	
	server_reply[recv_size] = '\0';	//puts(server_reply);	
	cout << server_reply << endl;

	//Program end
	closesocket(s);
	WSACleanup();
	return 0;
}
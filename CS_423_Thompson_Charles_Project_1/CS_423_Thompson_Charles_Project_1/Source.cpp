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
	char server_reply[500], userSelection;
	char userName;
	char userBuddy = NULL;
	char msgToSend = NULL;
	int recv_size, return_value, msgNum;
	string msg;
	const char* message = " ";

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

	cout << "Our target server is at address 204.76.188.23 \n Our starting message number is 23456\n Enter your IM name... ";
	cin >> userName;
	userName += '\n';
	msgNum = msgNumber();
	cout << "ACK NUM: " << msgNum << endl;
	//Send some data	
	cout << "Encrypted Name: " << encrypt(userName) << endl;

	msg = msgNum + ";1;" + encrypt(userName); //problem here
	cout << "MSG: " << message << endl;
	message = msg.c_str(); //problem here
	cout << "Message Converted: " << message << endl;
	msgNum += 2;
	cout << "New ACK NUM: " << msgNum << endl;
	if (sendto(s, message, strlen(message), 0, (struct sockaddr*)&server, sizeof(server)) < 0) {
		cout << "Send Failed" << endl;
		return 1;
	}

	cout << "Data Sent" << endl;

	do {
		//Receive a reply from the server	
		if ((recv_size = recvfrom(s, server_reply, 500, 0, NULL, NULL)) == SOCKET_ERROR) {
			cout << "recv failed" << endl;
			return 1;
		}

		cout << "reply Received" << endl;
		server_reply[recv_size] = '\0';	//puts(server_reply);	
		//cout << decrypt(server_reply) << endl;
		cout << "Enter q (for quit), s (send msg), or c (check for msgs)c\n";
		cin >> userSelection;
		switch(tolower(userSelection)){
			case 's':
				msg = msgNum + ";2;" + encrypt(userName);
				cout << "Enter Buddy Name: ";
				cin >> userBuddy;
				userBuddy += '\n';
				msg += encrypt(userBuddy);
				cout << "Enter Your Message: ";
				cin >> msgToSend;
				msgToSend += '\n';
				msg += encrypt(msgToSend);
				message = msg.c_str();
				if (sendto(s, message, strlen(message), 0, (struct sockaddr*)&server, sizeof(server)) < 0) {
					cout << "Send Failed" << endl;
					return 1;
				}
				msgNum += 2;
				break;
			case 'c':
				cout << "";
				break;
			case 'q':
				msg = msgNum + ";3;" + encrypt(userName);
				cout << "Good Bye\n";
				break;
		}
	} while (userSelection != 'q');


	//Receive a reply from the server	
	if ((recv_size = recvfrom(s, server_reply, 500, 0, NULL, NULL)) == SOCKET_ERROR) {
		cout << "recv failed" << endl;
		return 1;
	}

	cout << "reply Received" << endl;

	//Add \0 at the end of received string string before printing	
	server_reply[recv_size] = '\0';	//puts(server_reply);	
	//cout << decrypt(server_reply) << endl;

	//Program end
	closesocket(s);
	WSACleanup();
	return 0;
}


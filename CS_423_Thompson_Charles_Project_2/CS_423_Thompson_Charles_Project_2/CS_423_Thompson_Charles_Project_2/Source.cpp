
/****************************************************
*
*	Charles Thompson
*	CS 423 - Client Server Programming
*	University of Missouri - Kansas City
*	School of Computing and Engineering
*	03/15/2016
*
*	This program is a simple client application for a IM 
*	(Instant Messaging) service that uses a server as an 
*	itermediate between users. This program uses the a UDP
*	connectionless service using the getaddrinfo() method
*	from the winsock2 library. The program also uses 
*	multi-threading to listen for server responses for 
*	messages from other users. This is achieved using the
*	_beginthread() function from the process.h library.
*
*	When the user starts this program they will be 
*	prompted for a server and port number or the can 
*	enter 0 for the default server	information. They 
*	will then be asked to enter a user	name. The program 
*	will then establish connection to the server and 
*	indicate the other users that are connected to the IM 
*	service. The user can the enter s to send a message to 
*	another user, c to check for messages from other users, 
*	or q to quit the IM service.	
*
****************************************************/

#include "Cipher.h"
using namespace std;
#define PORT "23456"

//Global Variables
int l = 0;
int sockfd;
void Listen(void * temp);

int main(int argc, char *argv[]) {

	//Variable decelerations
	char client_relpy[500], userSelection;
	string userName, userBuddy, msgToSend, msgNum, msg, temp = "";
	int recv_size, return_value, new_fd;

	const char* message;
	map<int, string> users;
	queue<int> messages;

	//Creating addinfo variables
	struct addrinfo server_struct, *servinfo, *p;
	struct sockaddr_storage client_addr;

	memset(&server_struct, 0, sizeof server_struct);
	server_struct.ai_family = AF_INET;
	server_struct.ai_socktype = SOCK_DGRAM;
	server_struct.ai_flags = AI_PASSIVE;

	//Getting server address info
	if ((return_value = getaddrinfo(NULL, PORT, &server_struct, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", errno);
		return 1;
	}

	cout << "Address Resolved" << endl << servinfo->ai_family << endl << servinfo->ai_socktype << endl << servinfo->ai_protocol
		<< endl << servinfo->ai_socktype << endl << servinfo->ai_socktype << endl;

	//Create a socket	
	if ((sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol)) == -1) {
		fprintf(stderr, "Could not create socket : %d", errno);
	}

	if (bind(sockfd, servinfo->ai_addr, servinfo->ai_addrlen) == -1) {
            close(sockfd);
            perror("listener: bind");
        }

	cout << "Socket Created & Bound" << endl;

	//set SO_RESESADDR on a socket s to true	
	int optval = 1;
	setsockopt(return_value, SOL_SOCKET, SO_REUSEADDR, (const char*)&optval, sizeof optval);

	cout << "Listing for clients" << endl;

	while (true) {
		//Receive a reply from the server	
		if ((recv_size = recvfrom(sockfd, client_relpy, 500, 0, (struct sockaddr*) &client_addr, NULL) == -1)) {
			cout << "recv failed" << errno << endl;
            cin.ignore().get();
            return 1;
		}

        //Add \0 at the end of received string string before printing	
        client_relpy[recv_size] = '\0';	//puts(client_relpy);	
		for(int i = 0; i < 5; i++) {
			msgNum += client_relpy[i];
		}
		
        cout << decrypt(client_relpy, 8) << endl;
		userName = decrypt(client_relpy, 8);
        switch (client_relpy[6]) {
			cout << "Message Recieved" << endl;
            case '1':
				//Create a socket	
				if ((new_fd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol)) == -1) {
					fprintf(stderr, "Could not create socket : %d", errno);
				}
				users[new_fd] = userName;
                msg = createMessage(userName, "", "", msgNum, 1);
                message = msg.c_str();
                //Sending message to server
				if (sendto(new_fd, message, strlen(message), 0, servinfo->ai_addr, servinfo->ai_addrlen) < 0) {
                    cout << "Send Failed " << errno << endl;
                    cin.ignore().get();
                    return 1;
                }
                break;
            case '2':
                //Creating child thread to listen for server reply
                //_beginthread(Listen, 0, (void*)l);
                break;
            case '3':
                //Format the message to be sent 
                msg = createMessage(userName, "", "", msgNum, 3);
                //Convert the msg string to const char*
                message = msg.c_str();
                //Send message to the server
                if (sendto(sockfd, message, strlen(message), 0, servinfo->ai_addr, servinfo->ai_addrlen) < 0) {
                    cout << "Send Failed " << errno << endl;
					cin.ignore().get();
                    return 1;
                }
                break;
		}
	}

	//Program end
	close(sockfd);
	cin.ignore().get();
	return 0;
}

/*
void Listen(void * temp){
	int recv_size;
	char client_relpy[500];
	if ((recv_size = recvfrom(sockfd, client_relpy, 500, 0, NULL, NULL)) == SOCKET_ERROR) {
		cout << "recv failed" << errno << endl;
		cin.ignore().get();
	}
	//Add \0 at the end of received string string before printing	
	client_relpy[recv_size] = '\0';	//puts(client_relpy);	
	cout << decrypt(client_relpy, 10) << endl;
} */
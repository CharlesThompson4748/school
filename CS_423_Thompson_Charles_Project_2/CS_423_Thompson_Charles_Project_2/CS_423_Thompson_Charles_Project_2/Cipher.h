
/****************************************************
*   File Name:  cipher_sp14.h
*   Author:     Bob Cotter
*   Date:       2/20/2014
*
*   This file provides the data arrays that provide
*   character substitution information needed to support
*   the substitution cipher used in the CS423 enhanced
*   IM project.
*
*	EDIT: This file also contains functions that we written
*	to be used for the windows UDP client side IM service.
*	These functions include encrypt() which will take a 
*	string and create and encrypted string that will be
*	returned. The decrypt() function  which takes a string 
*	and decrpypts it using the decr character array. The 
*	msgNumber() function which get a random 5 digit number 
*	to be used for the ACK number for communications between
*	the client application and the server. The createMessage()
*	function which will take information about the user, the 
*	im recipient, the message, the current ACK number, and
*	the type of message and it will then create and message 
*	according to the type of message to be sent to the server.
*
****************************************************/
#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <cstring>
#include <ctime>
#include <map>
#include <queue>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

using namespace std;

//Encryption character array
char encr[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 'b', '.', 0, 'c', '[', 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
'R', 'u', ',', 'q', '\t', 'Y', '\n', '\'', 'n', 's', 'v', 'e', 'H', 'o', 'N', 'M',
'r', '=', '0', ';', 'z', '/', '`', 'E', '\"', 'k', '&', '5', '>', 'i', 'p', ')',
'$', '!', '2', 'O', '(', 'I', 'J', '%', 'Z', 'g', '\\', '{', 'h', '7', 'S', 'P',
'a', ' ', 'W', 'x', 'y', 'T', '+', '8', '-', 'L', '9', 'f', '#', 'F', '\r', 'B',
'3', 'D', ']', 'V', '?', '*', 'G', '6', 'w', '@', '}', '|', 'C', 'l', '_', 'j',
'K', '^', '1', 't', 'Q', '<', 'U', 'd', 'm', ':', 'A', 'X', '\f', '4', '~', 0,
0, 0 };

//Decryption character array
char decr[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, '$', '&', 0, '|', '^', 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
'Q', 'A', '8', '\\', '@', 'G', ':', '\'', 'D', '?', 'e', 'V', '\"', 'X', '\n', '5',
'2', 'r', 'B', '`', '}', ';', 'g', 'M', 'W', 'Z', 'y', '3', 'u', '1', '<', 'd',
'i', 'z', '_', 'l', 'a', '7', ']', 'f', ',', 'E', 'F', 'p', 'Y', '/', '.', 'C',
'O', 't', ' ', 'N', 'U', 'v', 'c', 'R', '{', '%', 'H', '\r', 'J', 'b', 'q', 'n',
'6', 'P', '\t', '\f', 'w', '+', '[', 'I', 'L', '=', 'o', '9', 'm', 'x', '(', '-',
'>', '#', '0', ')', 's', '!', '*', 'h', 'S', 'T', '4', 'K', 'k', 'j', '~', 0,
0, 0 };

/*
*	This function takes a string a computes the 
*	equivalent encryption from the encr character
*	array.
*	Input: String that will be encrypted
*	Output: String that has been encrypted
*/
string encrypt(string message) {
	string encryptedMsg;
	try {
		for (int i = 0; i < message.size(); i++) {
			encryptedMsg += encr[(int)message[i]];
		}
	}
	catch (exception &e) {
		cout << "Exception thrown: " << e.what() << endl;
		exit(0);
	}
	return encryptedMsg; 
}

/*
*	This function takes a string that has been
*	encrypted and decrypts the string using the 
*	decr character array.
*	Input: String that will be decrypted
*	Output: String that has been decrypted
*/
string decrypt(string message, int length) {
	string decryptedMsg;
	try {
		for (int i = length; i < message.size(); i++) {
			decryptedMsg += decr[(int)message[i]];
		}
	}
	catch (exception &e) {
		cout << "Exception thrown: " << e.what() << endl;
		exit(0);
	}
	return decryptedMsg;
}

/*
*	This function takes the usernames and message as well as the message number
*	and message type and formats them for the client to recieve
*	Input: Strings for the usernames and message, integers for the message
*	number and message type
*	Output: String formatted for the client to recieve
*/
string createMessage(string userName, string buddyName, string message, string ACK, int messageType) {
	string msg = " ";
	//Signon Message
	if (messageType == 1) {
		msg = "ack;";
		msg += ACK;
		msg += encrypt(";\nWelcome to the group,");
		msg += encrypt(userName);
		msg += encrypt("\nMembers already logged in are: A list (possibly empty) of logged in users");
	}
	//Sendto Message
	else if (messageType == 2) {
		msg = "ack;";
		msg += ACK;
		msg += ";";
	}
	//Signoff Message
	else if (messageType == 3) {
		msg = "ack;";
		msg += ACK;
		msg += ";Goodbye, ";
		msg += encrypt(userName);
		msg += "\n";
	}
	//Keep-Alive Message
	else if (messageType = 4) {
		msg = "tst;";
		msg += "4;keep-alive";
	}
	//Signon Alert
	else if(messageType = 5) {
		msg = "users;1;"; //this will need to be updated to take send to all users
		msg += encrypt(userName);
		msg += " just joined the group\n";
	}
	//Forward Message
	else if(messageType = 6) {
		msg = "Message;2;";
		msg += encrypt("\nFrom: ");
		msg += encrypt(userName);
		msg += encrypt(" To: ");
		msg += encrypt(buddyName);
		msg += message;
	}
	//Signoff/Dropped Alert
	else if(messageType = 7) {
		time_t t = time(0);
		struct tm* localtm = localtime(&t);
		msg = "users;3;";
		msg += encrypt(userName);
		msg += encrypt(" is leaving the group at ");
		msg += encrypt(asctime(localtm));
		msg += "\n";
	}
	//Error Alert
	else if(messageType = 8) {
		msg = "Error;";
		msg += ACK;
		msg += encrypt(message);
	}
	//Error
	else {
		cout << "Error: Message type dosn't exist" << endl;
	}
	return msg;
}
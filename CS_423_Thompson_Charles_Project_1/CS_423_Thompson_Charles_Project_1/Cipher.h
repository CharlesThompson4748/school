#include <time.h>
#include <iostream>
#include <string>
using namespace std;
/**************************************
*   File Name:  cipher_sp14.h
*   Author:     Bob Cotter
*   Date:       2/20/2014
*
*   This file provides the data arrays that provide
*   character substitution information needed to support
*   the substitution cipher used in the CS423 enhanced
*   IM project.
********************************************/


char encr[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 'b', '.', 0, 'c', '[', 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
'R', 'u', ',', 'q', '\t', 'Y', '\n', '\'', 'n', 's', 'v', 'e', 'H', 'o', 'N', 'M',
'r', '=', '0', ';', 'z', '/', '`', 'E', '\"', 'k', '&', '5', '>', 'i', 'p', ')',
'$', '!', '2', 'O', '(', 'I', 'J', '%', 'Z', 'g', '\\', '{', 'h', '7', 'S', 'P',
'a', ' ', 'W', 'x', 'y', 'T', '+', '8', '-', 'L', '9', 'f', '#', 'F', '\r', 'B',
'3', 'D', ']', 'V', '?', '*', 'G', '6', 'w', '@', '}', '|', 'C', 'l', '_', 'j',
'K', '^', '1', 't', 'Q', '<', 'U', 'd', 'm', ':', 'A', 'X', '\f', '4', '~', 0,
0, 0 };

char decr[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, '$', '&', 0, '|', '^', 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
'Q', 'A', '8', '\\', '@', 'G', ':', '\'', 'D', '?', 'e', 'V', '\"', 'X', '\n', '5',
'2', 'r', 'B', '`', '}', ';', 'g', 'M', 'W', 'Z', 'y', '3', 'u', '1', '<', 'd',
'i', 'z', '_', 'l', 'a', '7', ']', 'f', ',', 'E', 'F', 'p', 'Y', '/', '.', 'C',
'O', 't', ' ', 'N', 'U', 'v', 'c', 'R', '{', '%', 'H', '\r', 'J', 'b', 'q', 'n',
'6', 'P', '\t', '\f', 'w', '+', '[', 'I', 'L', '=', 'o', '9', 'm', 'x', '(', '-',
'>', '#', '0', ')', 's', '!', '*', 'h', 'S', 'T', '4', 'K', 'k', 'j', '~', 0,
0, 0 };


string encrypt(string message) {
	string encryptedMsg;
	for (int i = 0; i < message.size(); i++) {
		encryptedMsg += encr[(int)message[i]];
	}
	return encryptedMsg; 
}

string decrypt(string message) {
	string decryptedMsg;
	for (int i = 0; i < message.size(); i++) {
		decryptedMsg += encr[(int)message[i]];
	}
	return decryptedMsg;
}

int msgNumber () {
	int x;
	srand(time(NULL));
	x = rand() % 50000 + 10000;
	return x;
}
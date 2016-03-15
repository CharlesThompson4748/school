README

CS423 Project #1

Developer Information:
Charles Thompson
Email: cct8v6@mail.umkc.edu
University of Missouri - Kansas City
School of Computing and Engineering

Developement Platform:
Windows 10
Visual Studio Ultimate 2012
C++

Included:
Source file(.cpp)
Cipher file(.h)
README
Console Screen Shot

Program Description:
This program is a simple client application for a IM (Instant Messaging) 
service that uses a server as an itermediate between users. This program uses the a UDP
connectionless service using the getaddrinfo() method from the winsock2 library. 
The program also uses multi-threading to listen for server responses for 
messages from other users. This is achieved using the _beginthread() function 
from the process.h library.

When the user starts this program they will be prompted for a server and port 
number or the can enter 0 for the default server information. They will then 
be asked to enter a user name. The program will then establish connection to 
the server and indicate the other users that are connected to the IM service. 
The user can the enter s to send a message to another user, c to check for 
messages from other users, or q to quit the IM service.	

Running the Program: TODO
1. Download Source file and Cipher file and save in a desired location
2. Run Visual Studio
3. Once Visual Studio is open click on FILE in upper lefthand corner
4. Navigate to and click on Open then click on File
5. Navigate to saved location of the saved files in the files explorer
6. Open the both files
7. Once the files are open click on BUILD in Visual Studio
8. Once the Source file has finished building click on Local Windows Debugger to run the program

Using the Program:

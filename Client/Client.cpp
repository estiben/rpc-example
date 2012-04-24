/* 
 * File:   Client.cpp
 * Author: Steven Douglas
 *
 * Created on March 2, 2011, 7:48 PM
 */

#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

using namespace std;

int main(int argc, char *argv[])
{
    int sockfd, portNum, n;
    struct sockaddr_in serverAddress;
    struct hostent *server;

    char buffer[256];

    portNum = 2115;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        printf("ERROR opening socket\n");

    //get pointer to a hostent object containing information about the server
    server = gethostbyname("lab04.cs.ndsu.nodak.edu");
    if (server == NULL)
    {
        printf("ERROR, no such host\n");
        exit(0);
    }

    //set values in serverAddress
    bzero((char *) &serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serverAddress.sin_addr.s_addr, server->h_length);
    serverAddress.sin_port = htons(portNum);

    //establish a connection to the server
    if (connect(sockfd, (struct sockaddr*)&serverAddress,sizeof(serverAddress)) < 0)
        printf("ERROR connecting\n");
    else
    {
        printf("Connected to %s\n",server->h_name);
        while (1)
        {
            //read from socket
            bzero(buffer,256);
            n = read(sockfd,buffer,255);
            if (n < 0)
                 printf("ERROR reading from socket\n");
            printf("%s\n",buffer);
            if (!strcmp(buffer, "Goodbye"))
                return 0;

            //write to socket
            bzero(buffer,256);
            fgets(buffer,255,stdin);
            n = write(sockfd,buffer,strlen(buffer));
            if (n < 0)
                printf("ERROR writing to socket\n");
        }
    }
    return 0;
}
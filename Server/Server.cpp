/*
 * File:   Server.cpp
 * Author: Steven Douglas
 *
 */
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <Server.h>

using namespace std;

Server::Server()
{
    //create semaphore to protect linked list
    sem_init(&listSemaphore, 0, 1);

    //add some values to the list
    llist.append(4);
    llist.append(5);
    llist.append(6);
    llist.append(7);

    //create new socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        printf("server error opening socket\n");
    }

    //set values in serverAddress
    bzero((char *) &serverAddress, sizeof (serverAddress));
    portNum = 2115;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(portNum);

    //bind socket to address
    if (bind(sockfd, (struct sockaddr *) &serverAddress, sizeof (serverAddress)) < 0)
    {
        printf("server error on binding\n");
    }

    //listen on the socket for connections
    listen(sockfd, 5);

    clientAddressLen = sizeof (clientAddress);

    printf("Waiting for connections...\n");

    while (true)
    {
        //block until a client connects
        newsockfd = accept(sockfd, (struct sockaddr *) &clientAddress, (socklen_t*) &clientAddressLen);
        if (newsockfd < 0)
        {
            printf("server error on accept\n");
        }

        printf("Client connected. Creating new thread...\n");

        //create a Session to manage a new thread
        Session *t = new Session(&llist, &listSemaphore, newsockfd);
    }
}
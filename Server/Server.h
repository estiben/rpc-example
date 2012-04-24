/* 
 * File:   Server.h
 * Author: steven
 *
 * Created on March 8, 2011, 4:13 PM
 */
/*
 * File:   Server.h
 * Author: Steven Douglas
 */

#include <Session.h>

#ifndef SERVER_H
#define	SERVER_H

class Server
{
    public:
        Server();
        LinkedList llist;
        sem_t listSemaphore;

    private:
        int sockfd, newsockfd, portNum, clientAddressLen;
        struct sockaddr_in serverAddress, clientAddress;
};

#endif	/* SERVER_H */


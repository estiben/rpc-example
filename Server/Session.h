/* 
 * File:   Session.h
 * Author: Steven Douglas
 *
 * Created on March 10, 2011, 6:32 PM
 */

#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include "LinkedList.h"

using namespace std;

#ifndef SESSION_H
#define	SESSION_H

class Session
{
public:
    Session(LinkedList* l, sem_t* s,  int fd);
    LinkedList* llist;
    int sockfd;
    sem_t* sem;
    bool parseCommand(char* cmd, int* p, char* str);

private:
    pthread_t sThread;
};

#endif	/* SESSION_H */
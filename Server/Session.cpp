/**
 * File:   Session.cpp
 * Author: Steven Douglas
 *
 * Created on March 10, 2011, 6:30 PM
 */

#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "Session.h"

using namespace std;

/**
 * Function that runs when a client connects
 */
void* sessionThread(void* session)
{
    printf("Thread created.\n");

    //define local variables
    Session* s = (Session*) session;
    char buffer[256], command[256];
    int param;
    string result;
    int n;

    n = write(s->sockfd, "Available commands:\nappend(n)\nremove(n)\ncount()\nfirst()\nlast()\nexit()\n\nPlease type a command:", 93);
    if (n < 0)
        printf("ERROR writing to socket\n");

    //loop until exit command is received
    do
    {
        bzero(buffer, 256);
        n = read(s->sockfd, buffer, 255);
        if (n < 0)
            printf("ERROR reading from socket\n");
        printf("Client sent: %s\n", buffer);

        //separate the command from the parameter
        s->parseCommand(command, &param, buffer);
        printf("Command: %s\n", command);
        printf("Param: %d\n", param);

        if (!strcmp(command, "append"))
        {
            //append an integer to the linked list
            sem_wait(s->sem);
            result = s->llist->append(param);
            sem_post(s->sem);
        }
        else if (!strcmp(command, "remove"))
        {
            //remove an integer from the linked list
            sem_wait(s->sem);
            result = s->llist->remove(param);
            sem_post(s->sem);
        }
        else if (!strcmp(command, "count"))
        {
            //display the number of integers in the linked list
            sem_wait(s->sem);
            bzero(buffer, 256);
            sprintf(buffer, "Linked list contains: %d nodes", s->llist->count());
            result = buffer;
            sem_post(s->sem);
        }
        else if (!strcmp(command, "first"))
        {
            //display the first integer in the linked list
            sem_wait(s->sem);
            result = s->llist->first();
            sem_post(s->sem);
        }
        else if (!strcmp(command, "last"))
        {
            //display the last integer in the linked list
            sem_wait(s->sem);
            result = s->llist->last();
            sem_post(s->sem);
        }
        else if (!strcmp(command, "exit"))
        {
            //exit command received
            break;
        }
        else
        {
            //command was invalid
            result = "Invalid command\nAvailable commands:\nappend(n)\nremove(n)\ncount()\nfirst()\nlast()\nexit()";
        }

        s->llist->display();

        result += "\n\nPlease type a command:";
        n = write(s->sockfd, result.c_str(), result.length());
        if (n < 0)
            printf("ERROR writing to socket\n");
    } while (strcmp(command, "exit") != 0);

    n = write(s->sockfd, "Goodbye", 7);
    if (n < 0)
        printf("ERROR writing to socket\n");

    //close the socket
    close(s->sockfd);

    printf("Connection closed\n");
    
    pthread_exit(NULL);
}

Session::Session(LinkedList* l, sem_t* s, int fd)
{
    printf("New session started.\n");
    llist = l;
    sockfd = fd;
    sem = s;

    //create a new thread
    pthread_create(&sThread, NULL, sessionThread, (void*)this);
}

/**
 * separate the command from the parameter
 * returns true if successful
 */
bool Session::parseCommand(char* cmd, int* p, char* str)
{
    bzero(cmd, 256);
    int pLeft, pRight;

    pLeft = strcspn(str, "(");
    pRight = strcspn(str, ")");
    
    if (pRight == strlen(str) - 2 && pLeft < pRight)
    {
        char pStr[pRight - pLeft - 1];

        strncpy(cmd, str, pLeft);
        strncpy(pStr, str + pLeft + 1, pRight - pLeft - 1);
        *p = atoi(pStr);

        return true;
    }
    return false;
}
/* 
 * File:   LinkedList.cpp
 * Author: Steven Douglas
 * 
 * Created on March 3, 2011, 11:56 PM
 */

#include "LinkedList.h"
#include <stdio.h>
#include <iostream>

LinkedList::LinkedList()
{
    p = NULL;
}

string LinkedList::append(int num)
{
    char result[256];
    node *q, *t;

    if (p == NULL)
    {
        p = new node;
        p->value = num;
        p->link = NULL;
    }
    else
    {
        q = p;
        while (q->link != NULL)
            q = q->link;

        t = new node;
        t->value = num;
        t->link = NULL;
        q->link = t;
    }
    sprintf(result, "append(%d) successful", num);
    return result;
}

string LinkedList::remove( int num )
{
    char result[256];

    if (p != NULL)
    {
        node *q,*r;
        q = p;

        if (q->value == num)
        {
            p = q->link;
            delete q;
            sprintf(result, "remove(%d) successful", num);
            return result;
        }

        r = q;
        while (q != NULL)
        {
            if (q->value == num)
            {
                r->link = q->link;
                delete q;
                sprintf(result, "remove(%d) successful", num);
                return result;
            }
            r = q;
            q = q->link;
        }
    }
    
    sprintf(result, "Element: %d not found", num);
    return result;
}

string LinkedList::first()
{
    char result[256];
    if (p == NULL)
        sprintf(result, "The list is empty");
    else
    {
        node *q;
        q = p;
        sprintf(result, "The first element is: %d", q->value);
    }
    return result;
}

string LinkedList::last()
{
    char result[256];
    if (p == NULL)
        sprintf(result, "The list is empty");
    else
    {
        node *q;
        for (q = p; q->link != NULL; q = q->link)
        {}
        sprintf(result, "The last element is: %d", q->value);
    }
    return result;
}

void LinkedList::display()
{
    node *q;
    printf("Linked List:\n");
    for (q = p; q != NULL; q = q->link)
        printf("%d\n", q->value);
}

int LinkedList::count()
{
    node *q;
    int c = 0;
    for (q = p; q != NULL; q = q->link)
        c++;
    return c;
}



LinkedList::~LinkedList()
{
    node *q;
    if (p == NULL)
        return;

    while (p != NULL)
    {
        q = p->link;
        delete p;
        p = q;
    }
}


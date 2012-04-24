/* 
 * File:   LinkedList.h
 * Author: Steven Douglas
 *
 * Created on March 3, 2011, 11:56 PM
 */

#include <string>

using namespace std;

#ifndef LINKEDLIST_H
#define	LINKEDLIST_H

class LinkedList
{
    private:
        struct node
        {
            int value;
            node *link;
        }*p;

    public:
        LinkedList();
        string append(int num);
        string remove(int num);
        void display();
        string first();
        string last();
        int count();
        ~LinkedList();

};

#endif	/* LINKEDLIST_H */


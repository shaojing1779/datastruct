#ifndef LIST_H
#define LIST_H
#include <stdio.h>
#include <pthread.h>

class List
{
public:
    List();
    void push(int i);
    void pop();
    void print_list();
private:
    class Node{

    public:
        Node()
        {
            _i = 0;
            _next = nullptr;
        }
        Node(int i)
        {
            _i = i ;
            _next = nullptr;
        }
        int _i;
        Node* _next;
    };
    Node *_head = nullptr;
    pthread_mutex_t mylock = PTHREAD_MUTEX_INITIALIZER;
};

#endif // LIST_H

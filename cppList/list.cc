#include "list.h"
#include<stdlib.h>

List::List()
{
    _head = new Node(0);
    _head->_i = 0;
    _head->_next = nullptr;
}

void List::push(const int i)
{
    pthread_mutex_lock(&mylock);

    Node *p = _head;
    Node *n = new Node(i);
    n->_i = i;
    n->_next = nullptr;

    while (p) {
        if(!p->_next)
        {
            p->_next = n;
            break;
        }
        else
        {
            p = p->_next;
        }
    }
    pthread_mutex_unlock(&mylock);

}

void List::pop()
{
    pthread_mutex_lock(&mylock);
    Node *p = _head;
    if(!p){
        printf("List Error!\n");
        exit(0);
    }
    if(!p->_next){
        printf("ERROR No Node!\n");
        return;
        //exit(-1);
    }

    while (p) {
        if(!(p->_next->_next)){
            printf("%d\n", p->_next->_i);
            delete p->_next;
            p->_next = nullptr;
            break;
        }else
            p = p->_next;
    }
    pthread_mutex_unlock(&mylock);
}

void List::print_list()
{
    Node *p = _head;
    while (p) {
        p = p->_next;
        if(p)
            printf("%d\t", p->_i);
    }
    printf("\n");
}



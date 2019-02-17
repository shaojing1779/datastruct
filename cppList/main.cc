#include <iostream>
#include"list.h"
#include<pthread.h>
#include<unistd.h>
using namespace std;

void* thread_func(void* arg)
{
    List *li = static_cast<List*>(arg);

    li->pop();

    return static_cast<void*>(nullptr);
}

int main()
{
    List *li = new List();
    li->push(1);
    li->push(2);
    li->push(3);
    li->push(4);
    li->push(5);
    li->push(6);
    li->push(7);
    li->print_list();

    int i;
    pthread_t tid[3];
    void *tret;
    for(i = 0; i < 3; i++)
    {
        pthread_create(&tid[i], nullptr, thread_func, static_cast<void*>(li));
    }

    for(i = 0; i < 3; i++)
        pthread_join(tid[i], &tret);

    li->print_list();
    return 0;
}

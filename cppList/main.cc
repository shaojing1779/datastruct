#include <iostream>
#include"list.h"
#include<pthread.h>
#include<unistd.h>
#include<sstream>
using namespace std;

void* del_func(void* arg)
{
    List<string> *li = static_cast<List<string>*>(arg);

    string del_data = li->pop();
    if(del_data != "")
	    cout << "Del_data=[" << del_data << "],size=" << li->size() << endl;
    sleep(0.2);

    return static_cast<void*>(nullptr);
}

void* add_func(void* arg)
{
    List<string> *li = static_cast<List<string>*>(arg);

    static int i = 0;
    i++;

    cout << "ADD_data=" << i << endl;

    stringstream ss("");
    ss << i;

    li->push_back(ss.str());

    sleep(0.2);
    return static_cast<void*>(nullptr);
}

int main()
{
    List<string> *li = new List<string>();

    int i;
    pthread_t tid[4];
    void *tret;

    while(1)
    {
	    if(i++ > 10) break;
	    pthread_create(&tid[0], nullptr, add_func, static_cast<void*>(li));
	    pthread_join(tid[0], &tret);
	    pthread_create(&tid[2], nullptr, add_func, static_cast<void*>(li));
	    pthread_join(tid[2], &tret);
	    pthread_create(&tid[3], nullptr, add_func, static_cast<void*>(li));
	    pthread_join(tid[3], &tret);
	    pthread_create(&tid[1], nullptr, del_func, static_cast<void*>(li));
	    pthread_join(tid[1], &tret);
    }

    while(1)
    {
	    if(li->size() == 0) break;
	    pthread_create(&tid[0], nullptr, del_func, static_cast<void*>(li));
	    pthread_join(tid[0], &tret);
    }

    return 0;
}

#include <iostream>
#include"list.h"
#include<pthread.h>
#include<unistd.h>
#include<sstream>
#include <sys/types.h>

using namespace std;

List<int> *li = new List<int>();

void* del_func_num(void *)
{
	int j = 0;
	while(1)
	{
		if(j >= 100) break;

		if(li->size() > 0)
		{
			int del_data = li->pop();
			cout << "ttid=[" << pthread_self() << "]" << "DEL_NUM_data=[" << del_data << "],size=" << li->size() << endl;
			j++;
		}
	}
    return static_cast<void*>(nullptr);
}

void* del_func_all(void *)
{
	while(1)
	{
			int del_data = li->pop();
			if(li->size() > 0)
					cout << "ttid=[" << pthread_self() << "]" << "DEL_ALL_data=[" << del_data << "],size=" << li->size() << endl;
	}
    return static_cast<void*>(nullptr);
}

void* add_func(void *)
{
	int j = 0;
	while(1)
	{
		if(j >= 100) break;
		j++;

		static int i = 1;

		li->push_back(i++);

		cout << "ttid=[" << pthread_self() << "]" << "ADD_data=" << i << ",size=" << li->size() << endl;

	}
    return static_cast<void*>(nullptr);
}

int main()
{
    pthread_t tid[5];

	pthread_create(&tid[0], nullptr, add_func, nullptr);
	pthread_create(&tid[1], nullptr, add_func, nullptr);
	usleep(1);
	pthread_create(&tid[2], nullptr, del_func_num, nullptr);

	pthread_join(tid[0], nullptr);
	pthread_join(tid[1], nullptr);
	pthread_join(tid[2], nullptr);

	pthread_create(&tid[4], nullptr, del_func_all, nullptr);
	pthread_join(tid[4], nullptr);

    return 0;
}

#ifndef LIST_H
#define LIST_H
#include <pthread.h>

template<typename T>
class List
{
public:
    List()
    {
        _head = new Node();
        _head->_next = nullptr;
    }
    void push_back(T t)
    {
        pthread_mutex_lock(&_mlock);

        Node* p = _head;
        Node* n = new Node(t);
        n->_t = t;
        n->_next = nullptr;

        while (p)
        {
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
        pthread_mutex_unlock(&_mlock);
    }

    T pop()
    {
	pthread_mutex_lock(&_mlock);
	Node* p = _head;
	T t_tmp;
	do
	{
	        if(!p){
	            break;
	        }
	        if(!p->_next){
	            break;
	        }
	
	        while (p) {
	            if(!(p->_next->_next)){
			t_tmp = p->_next->_t;
	                delete p->_next;
	                p->_next = nullptr;
	                break;
	            }else
	                p = p->_next;
		}
	} while(0);
        pthread_mutex_unlock(&_mlock);
	return t_tmp;

    }

private:
    class Node{

    public:
        Node()
        {
            _next = nullptr;
        }
        Node(T t)
        {
            _t = t ;
            _next = nullptr;
        }
        T _t;
        Node* _next;
    };

    Node* _head = nullptr;
    pthread_mutex_t _mlock = PTHREAD_MUTEX_INITIALIZER;
};

#endif // LIST_H

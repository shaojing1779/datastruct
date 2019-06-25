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
    void push_back(const T& t)
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
				_size++;
                break;
            }
            else
            {
                p = p->_next;
            }
        }
        pthread_mutex_unlock(&_mlock);
    }
    size_t size()
    {
        return _size;
    }

    T pop()
    {
		pthread_mutex_lock(&_mlock);
		T t_tmp;
		do  
		{   
			if(!_head) break;
			if(!_head->_next) break;
			Node* p = _head->_next->_next;
			t_tmp = _head->_next->_t;
			delete _head->_next;
			_head->_next = p;
			_size--;

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
        Node(const T& t)
        {
            _t = t ;
            _next = nullptr;
        }
        T _t;
        Node* _next;
    };

    Node* _head = nullptr;
    size_t _size = 0;
    pthread_mutex_t _mlock = PTHREAD_MUTEX_INITIALIZER;
};

#endif // LIST_H

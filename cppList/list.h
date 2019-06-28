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

template<typename T>
class DList
{
public:
    DList()
    {
        _head = new Node();
        _tail = new Node();
        _head->_prev = nullptr;
        _head->_next = _tail;
        _tail->_prev = _head;
        _tail->_next = nullptr;
    }
    void push_back(const T& t)
    {
        pthread_mutex_lock(&_mlock);

        Node* n = new Node(t);

        n->_t = t;
        n->_prev = _head;
		n->_next = _head->_next;

		_head->_next->_prev = n;
		_head->_next = n;

		_size++;

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
			if(!_tail->_prev->_prev) break;
			Node* p = _tail->_prev->_prev;
			t_tmp = _tail->_prev->_t;
			delete _tail->_prev;

			p->_next = _tail;
			_tail->_prev = p;
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
            _prev = nullptr;
        }
        Node(const T& t)
        {
            _t = t;
            _prev = nullptr;
            _next = nullptr;
        }
        T _t;
        Node* _next;
        Node* _prev;
    };

    Node* _head = nullptr;
    Node* _tail = nullptr;
    size_t _size = 0;
    pthread_mutex_t _mlock = PTHREAD_MUTEX_INITIALIZER;
};

#endif // LIST_H

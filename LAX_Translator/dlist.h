#pragma once
#include <iostream>
namespace dlst
{
	

	template <class T>
	struct node
	{
		node* m_next;
		node* m_prev;
		T m_data;
	};

	template <class T>
	class iterator
	{
		node<T>* m_ptr;
	public:
		
		
		iterator() :m_ptr(NULL){}
		iterator(node<T>* ptr) :m_ptr(ptr){}
		iterator(const iterator& _iterator) :m_ptr(_iterator.m_ptr){}
		~iterator(){}


		iterator operator++(){ m_ptr = m_ptr->m_next; return *this; }
		iterator operator--(){ m_ptr = m_ptr->m_prev; return *this; }
		bool operator!=(const iterator _iterator){ return m_ptr != _iterator.m_ptr; }
		bool operator==(const iterator _iterator){ return m_ptr == _iterator.m_ptr; }
		friend iterator operator+(const iterator& _iterator, int index)
		{
			iterator temp(_iterator);
			for (int i = 0; i < index && temp.m_ptr; i++)
			{
				temp.m_ptr = temp.m_ptr->m_next;
			}
			return temp;
		}
		T& operator*() { return m_ptr->m_data; }

	};

	

	template <class T>
	class dlist
	{
		node<T>* m_head;
		node<T>* m_tail;
		node<T>* m_end;
		node<T>* m_rend;
		int m_size;
	public:

		iterator<T> begin()const { return iterator<T>(m_head); }
		iterator<T> end()const { return iterator<T>(m_end); }
		iterator<T> rend()const { return iterator<T>(m_rend); }
		iterator<T> rbegin()const { return iterator<T>(m_tail); }
		int size()const{ return m_size; }
		void push_back(const T& data);
		void push_front(const T& data);
		void pop_back();
		void pop_front();

		int range(const iterator<T> left, const iterator<T> right)const;

		dlist();
		dlist(const dlist& _dlist);
		~dlist();

		dlist& clear();

		dlist operator=(const dlist& _dlist);
		T& operator[](int index)const{ return *(begin() + index); }
		friend std::ostream& operator<<(std::ostream& out, const dlist& _dlist)
		{
			for (iterator<T> it = _dlist.begin(); it != _dlist.end(); it++)
			{
				out << int(*it);
			}
			return out;
		}


	};

	template <class T>
	dlist<T>::~dlist()
	{
		clear();
		delete m_rend;
		delete m_end;
	}

	template <class T>
	dlist<T>& dlist<T>::clear()
	{
		if (m_head == m_rend)
		{
			return *this;
		}
		node<T>* prev = m_head;
		node<T>* cur = m_head;
		while (cur!=m_end)
		{
			prev = cur;
			cur = cur->m_next;
			delete prev;
		}
		m_head = m_rend;
		m_tail = m_end;
		m_size = 0;
		return *this;
	}

	template <class T>
	void dlist<T>::push_back(const T& data)
	{
		node<T>* node_temp = new node<T>;
		node_temp->m_next = m_end;
		node_temp->m_data = data;
		if (m_tail==m_end)
		{
			node_temp->m_prev = m_rend;
			m_rend->m_next = node_temp;
			m_end->m_prev = node_temp;
			m_head = m_tail = node_temp;
		}
		else
		{
			m_tail->m_next = node_temp;
			node_temp->m_prev = m_tail;
			m_end->m_prev = node_temp;
			m_tail = node_temp;
		}
		m_size++;
		return;
		
	}

	template <class T>
	void dlist<T>::push_front( const T& data)
	{
		node<T>* node_temp = new node<T>;
		node_temp->m_prev = m_rend;
		node_temp->m_data = data;
		if (m_head == m_rend)
		{
			node_temp->m_next = m_end;
			m_end->m_prev = node_temp;
			m_rend->m_next = node_temp;
			m_head = m_tail = node_temp;
		}
		else
		{
			m_head->m_prev = node_temp;
			node_temp->m_next = m_head;
			m_rend->m_next = node_temp;
			m_head = node_temp;
		}
		m_size++;
		return;
	}

	template <class T>
	void dlist<T>::pop_back()
	{
		node<T>* todel = m_tail;
		m_tail = m_tail->m_prev;
		m_tail->m_next = m_end;
		m_end->m_prev = m_tail;
		delete todel;
		m_size--;
	}

	template <class T>
	void dlist<T>::pop_front()
	{
		node<T>* todel = m_head;
		m_head = m_head->m_next;
		m_head->m_prev = m_rend;
		m_rend->m_next = m_head;
		delete todel;
		m_size--;
	}

	template<class T>
	int dlist<T>::range(const iterator<T> left, const iterator<T> right) const
	{
		int res = 0;
		for (iterator<T> it = left; it != right; it++)
		{
			res++;
		}
		return res;
	}

	template<class T>
	dlist<T>::dlist()
	{
		m_rend = new node<T>;
		m_rend->m_prev = NULL;
		m_end = new node<T>;
		m_end->m_next = NULL;
		m_head = m_rend;
		m_tail = m_end;
		m_size = 0;
	}

	template<class T>
	dlist<T>::dlist(const dlist& _dlist)
	{
		m_rend = new node<T>;
		m_rend->m_prev = NULL;
		m_end = new node<T>;
		m_end->m_next = NULL;
		m_head = m_rend;
		m_tail = m_end;
		m_size = 0;

		for (iterator<T> it = _dlist.begin(); it != _dlist.end(); it++)
		{
			push_back(*it);
		}

	}

	template<class T>
	dlist<T> dlist<T>::operator=(const dlist& _dlist)
	{

		clear();
		for (iterator<T> it = _dlist.begin(); it != _dlist.end(); it++)
		{
			push_back(*it);
		}
		return *this;
	}
}






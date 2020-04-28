#pragma once

#ifndef NODE_H_
#define NODE_H_

//½Úµã
template<class Type>
class Node
{
	Type m_data;
	Node<Type>* m_next;
	Node<Type>* m_pre;
	int m_index;
	
public:
	Node() :m_next(NULL), m_pre(NULL), m_data((Type)0),m_index(-1) {};

	Type data()const { return m_data; };
	Node<Type>* next()const { return m_next; };
	Node<Type>* pre()const { return m_pre; };
	int index()const { return m_index; };

	void set_data(Type d) { m_data = d; };
	void set_next(Node<Type>* n) { m_next = n; };
	void set_pre(Node<Type>* p) { m_pre = p; };
	void set_index(int idx) { m_index = idx; };
};

#endif
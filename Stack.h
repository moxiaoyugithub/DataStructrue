#pragma once
#include "Vessel.h"

#ifndef STACK_H_
#define STACK_H_

//ջ
template<class Type>
class Stack: Vessel<Type>
{

public:

	//���캯��
	Stack() :Vessel<Type>() {};
	Stack(const int ms) :Vessel<Type>(ms) {};
	Stack(const Stack<Type>& s) :Vessel<Type>(*((Vessel<Type>*)(&s))) {};
	Stack(const Vessel<Type>& v) :Vessel<Type>(v) {};
	Stack(const Vessel<Type>* v) :Vessel<Type>(v) {};
	Stack(const Stack<Type>* s) :Vessel<Type>((Vessel<Type>*)s) {};

	//��Ա����
	using Vessel<Type>::end;
	using Vessel<Type>::begin;
	using Vessel<Type>::maxsize;
	virtual bool push(Type);
	virtual bool pop(Type&);
	virtual Type top_data()const { return Vessel<Type>::end()->data(); };

	//������
	virtual bool operator=(const Stack<Type>);
	virtual bool operator=(const Stack<Type>*);
	friend const Stack<Type>* operator+(const Stack<Type>& s1, const Stack<Type>& s2)
	{
		const Vessel<Type>* s1_v = &s1;
		const Vessel<Type>* s2_v = &s2;

		return new Stack<Type>((*s1_v + *s2_v));
	}
	friend std::istream& operator>> (std::istream& is, Stack<Type>& s)
	{
		if (!s.Vessel<Type>::is_empty())
			s.empty();

		Type d;
		while (is >> d)
		{
			s.append(d);
			if (is.peek() == '\n')
				break;
		}
		return is;
	};
	friend std::ostream& operator<< (std::ostream& os, const Stack<Type>& s)
	{
		os << (Vessel<Type>)s;
		return os;
	};
};

//���ڲ�����
template<class Type>
bool Stack<Type>::operator=(const Stack<Type> s)
{
	return (*((Vessel<Type>*)(this)) = *((Vessel<Type>*)(&s)));
}

//���ڲ�����(*)
template<class Type>
bool Stack<Type>::operator=(const Stack<Type>* s)
{
	//�ж��Ƿ�Խ��
	const Vessel<Type>* s_v = s;
	Vessel<Type>* s_t = this;

	if (!(*s_t = s_v))
		return false;

	return true;
}

//ѹջ
template<class Type>
bool Stack<Type>::push(Type d)
{
	return Vessel<Type>::append(d);
}

//��ջ
template<class Type>
bool Stack<Type>::pop(Type& d)
{
	if (Vessel<Type>::is_empty())
		return false;

	//����λ��ѡ��ɾ����ʽ
	if (Vessel<Type>::size() == 1)		//ɾͷ
	{
		Vessel<Type>::begin(NULL);
		d = Vessel<Type>::end()->data();
		delete(*(Vessel<Type>::end()));
	}
	else
	{
		//ɾβ
		Vessel<Type>::end(Vessel<Type>::end()->pre());
		d = Vessel<Type>::end()->next()->data();
		delete(Node<Type>*)(Vessel<Type>::end()->next());
		Vessel<Type>::end()->set_next(NULL);
	}


	//����1��ά�����
	Vessel<Type>::m_size -= 1;
	if (Vessel<Type>::m_size == 0)
		Vessel<Type>::m_empty_flag = true;
	Vessel<Type>::m_full_flag = false;

	//ά��index�����õ�����
	Vessel<Type>::iter_reset();

	return true;
}

#endif
#pragma once
#include "Vessel.h"

#ifndef Queue_H_
#define Queue_H_

//ջ
template<class Type>
class Queue : Vessel<Type>
{

public:

	//���캯��
	Queue() :Vessel<Type>() {};
	Queue(const int ms) :Vessel<Type>(ms) {};
	Queue(const Queue<Type>& s) :Vessel<Type>(*((Vessel<Type>*)(&s))) {};
	Queue(const Vessel<Type>& v) :Vessel<Type>(v) {};
	Queue(const Vessel<Type>* v) :Vessel<Type>(v) {};
	Queue(const Queue<Type>* s) :Vessel<Type>((Vessel<Type>*)s) {};

	//��Ա����
	using Vessel<Type>::end;
	using Vessel<Type>::begin;
	using Vessel<Type>::maxsize;
	virtual bool enqueue(Type);
	virtual bool dequeue(Type&);
	virtual Type top_data()const { return Vessel<Type>::end()->data(); };

	//������
	virtual bool operator=(const Queue<Type>);
	virtual bool operator=(const Queue<Type>*);
	friend const Queue<Type>* operator+(const Queue<Type>& s1, const Queue<Type>& s2)
	{
		const Vessel<Type>* s1_v = &s1;
		const Vessel<Type>* s2_v = &s2;

		return new Queue<Type>((*s1_v + *s2_v));
	}
	friend std::istream& operator>> (std::istream& is, Queue<Type>& s)
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
	friend std::ostream& operator<< (std::ostream& os, const Queue<Type>& s)
	{
		os << (Vessel<Type>)s;
		return os;
	};
};

//���ڲ�����
template<class Type>
bool Queue<Type>::operator=(const Queue<Type> s)
{
	return (*((Vessel<Type>*)(this)) = *((Vessel<Type>*)(&s)));
}

//���ڲ�����(*)
template<class Type>
bool Queue<Type>::operator=(const Queue<Type>* s)
{
	//�ж��Ƿ�Խ��
	const Vessel<Type>* s_v = s;
	Vessel<Type>* s_t = this;

	if (!(*s_t = s_v))
		return false;

	return true;
}

//���
template<class Type>
bool Queue<Type>::enqueue(Type d)
{
	return Vessel<Type>::append(d);
}

//����
template<class Type>
bool Queue<Type>::dequeue(Type& d)
{
	if (Vessel<Type>::is_empty())
		return false;

	//����λ��ѡ��ɾ����ʽ
	if (Vessel<Type>::size() == 1)		//ɾβ
	{
		d = Vessel<Type>::begin()->data();
		delete(*(Vessel<Type>::begin()));
		Vessel<Type>::begin(NULL);
		Vessel<Type>::end(NULL);
	}
	else
	{
		//ɾͷ
		Vessel<Type>::begin(Vessel<Type>::begin()->next());
		d = Vessel<Type>::begin()->pre()->data();
		delete(Node<Type>*)(Vessel<Type>::begin()->pre());
		Vessel<Type>::begin()->set_pre(NULL);
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
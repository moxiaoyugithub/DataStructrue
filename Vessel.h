#pragma once
#include <iostream>
#include "Node.h"
#include "Iter.h"
#include<string>

#ifndef VESSEL_H_
#define VESSEL_H_

using std::cout;
//����
template<class Type>
class Vessel
{
	//�α�
	Node<Type>* m_head;
	Node<Type>* m_rear;

protected:

	//����
	int m_maxsize;		//����С
	int m_size;			//��ǰ��С

	//���
	bool m_empty_flag;	//Ϊ�ձ��
	bool m_full_flag;	//Ϊ�����

	//������
	Iter<Node<Type>> m_iterator;
	virtual void iter_reset() { m_iterator = m_head; };
	virtual Iter<Node<Type>> begin(Iter<Node<Type>> iter) { m_head = *iter; return Iter<Node<Type>>(m_head); };
	virtual Iter<Node<Type>> end(Iter<Node<Type>> iter) { m_rear = *iter; return Iter<Node<Type>>(m_rear); };

public:
	std::string name;

	//���캯��
	Vessel();
	Vessel(const int);
	Vessel(const Vessel<Type>&);
	Vessel(const Vessel<Type>*);
	virtual ~Vessel();


	virtual Iter<Node<Type>> begin()const { return m_head; };
	virtual Iter<Node<Type>> end()const { return m_rear; };


	//��Ա����
	virtual bool append(const Type&);
	virtual bool remove(const Type);
	virtual Type max()const;
	virtual Type min()const;
	virtual void empty();
	virtual int size()const { return m_size; };
	virtual int maxsize()const { return m_maxsize; };
	virtual void set_maxsize(int ms) { m_maxsize = ms; if (m_maxsize > m_size) m_full_flag = false; };
	virtual bool is_empty()const { return m_empty_flag; };
	virtual bool is_full()const { return m_full_flag; };

	//������
	virtual bool operator=(const Vessel<Type>);
	virtual bool operator=(const Vessel<Type>*);
	friend const Vessel<Type>* operator+(const Vessel<Type>& v1,const Vessel<Type>& v2)
	{
		//Ϊ�ռ��
		if (v1.is_empty())
			return &v2;

		if (v2.is_empty())
			return &v1;

		//����������
		Vessel<Type>* v = NULL;
		if (v1.maxsize() != -1 && v2.maxsize() != -1)
			v = new Vessel<Type>(v1.maxsize() + v2.maxsize());
		else
			v = new Vessel<Type>(-1);

		//
		v->iter_reset();
		//auto p_t = v->m_iterator.iterator();
		auto p_v1 = v1.begin();
		auto p_v2 = v2.begin();

		//����v1
		for (int i = 0; i < v1.size(); i++)
		{
			v->append(p_v1->data());
			p_v1++;
			//p_v1.set(p_v1.iterator()->next());
		}

		//����v2
		for (int i = 0; i < v2.size(); i++)
		{
			v->append(p_v2->data());
			p_v2++;
			//p_v2.set(p_v2.iterator()->next());
		}

		return v;
	}
	friend std::istream& operator>> (std::istream& is, Vessel<Type>& v)
	{
		if (!v.is_empty())
			v.empty();

		Type d;
		while (is >> d)
		{
			v.append(d);
			if (is.peek() == '\n')
				break;
		}
		return is;
	};
	friend std::ostream& operator<< (std::ostream& os,const Vessel<Type>& v)
	{
		if (v.is_empty())
			return os;

		//v.iter_reset();
		auto p = v.begin();
		for (int i = 0; i < v.size(); i++)
		{
			os << p->data() << " ";
			p++;
		}

		return os;
	};
};

/*****************************************************/
/*****************����ʵ��****************************/

//���޴�С������ʼ��
template<class Type>
Vessel<Type>::Vessel()
{
	//name = "��ʱ����";
	m_head = NULL;
	m_iterator = m_head;
	m_rear = NULL;
	m_maxsize = -1;		//���޴�С
	m_size = 0;
	m_empty_flag = true;
	m_full_flag = false;
	//cout << "���޴�С�����������\n";
}

//���޴�С������ʼ��
template<class Type>
Vessel<Type>::Vessel(const int ms)
{
	//name = "��ʱ����";
	m_head = NULL;
	m_iterator = m_head;
	m_rear = NULL;
	m_maxsize = ms;		//���޴�С
	m_size = 0;
	m_empty_flag = true;
	m_full_flag = false;
	//cout << "���޴�С�����������\n";
}

//���ƹ���
template<class Type>
Vessel<Type>::Vessel(const Vessel<Type>& v)
{
	//name = v.name+"����ʱ����";
	//����ͷ���
	m_head = new Node<Type>;
	iter_reset();

	m_head->set_data(v.m_head->data());
	m_head->set_next(NULL);
	m_head->set_pre(NULL);
	m_head->set_index(0);

	m_rear = m_head;

	Node<Type>* p_v = v.m_head->next();
	for (int i = 1; i < v.m_size; i++)
	{
		m_rear->set_next(new Node<Type>); //����ָ���������½ڵ�
		Node<Type>* temp = m_rear;
		m_rear = m_rear->next();		//p_this�ƶ����½ڵ�
		m_rear->set_data(p_v->data());	//�½ڵ���������
		m_rear->set_next(NULL);			//�½ڵ�ָ�����ÿ�
		m_rear->set_pre(temp);
		m_rear->set_index(p_v->index());

		p_v = p_v->next();
	}

	//���ƴ�С��Ϣ
	m_maxsize = v.m_maxsize;
	m_size = v.m_size;

	//����״̬��
	m_empty_flag = v.m_empty_flag;
	m_full_flag = v.m_full_flag;
	//cout<<v.name << "�ĸ��ƹ������\n";
}

//ͬ��ӹ�(*)
template<class Type>
Vessel<Type>::Vessel(const Vessel<Type>* v)
{
	//ָ�븴��
	m_head = v->m_head;
	m_rear = v->m_rear;

	//���ƴ�С��Ϣ
	m_maxsize = v->m_maxsize;
	m_size = v->m_size;

	//����״̬��
	m_empty_flag = v->m_empty_flag;
	m_full_flag = v->m_full_flag;

	//cout << v->name << "��*���ƹ������\n";
	//cout << name << "�ӹ���" << v->name << "\n";
}

//��������
template<class Type>
Vessel<Type>::~Vessel()
{
	Node<Type>* p = m_head;
	while (m_head != NULL)
	{
		m_head = m_head->next();
		delete p;   //free(p);
		p = m_head;
	}
	//cout << name << "�������\n";
}

//���ڲ�����
template<class Type>
bool Vessel<Type>::operator=(const Vessel<Type> v)
{
	//cout << "���ڲ�������Ӧ\n";
	//�ж��Ƿ�Խ��
	if (m_maxsize != -1 && m_maxsize < v.m_maxsize)
		return false;

	//ɾ��ԭ��Ԫ��
	if (!is_empty())
		empty();

	//����ͷ���
	m_head = new Node<Type>;
	iter_reset();		//���õ�����
	m_head->set_data(v.m_head->data());
	m_head->set_next(NULL);
	m_head->set_pre(NULL);
	m_head->set_index(0);

	m_rear = m_head;
	Node<Type>* p_v = v.m_head->next();

	for (int i = 1; i < v.m_size; i++)
	{
		m_rear->set_next(new Node<Type>); //����ָ���������½ڵ�
		Node<Type>* temp = m_rear;
		m_rear = m_rear->next();		//p_this�ƶ����½ڵ�
		m_rear->set_data(p_v->data());	//�½ڵ���������
		m_rear->set_next(NULL);			//�½ڵ�ָ�����ÿ�
		m_rear->set_pre(temp);
		m_rear->set_index(p_v->index());

		p_v = p_v->next();
	}

	//���ƴ�С��Ϣ
	m_maxsize = v.m_maxsize;
	m_size = v.m_size;

	//����״̬��
	m_empty_flag = v.m_empty_flag;
	m_full_flag = v.m_full_flag;

	//cout << "���ڲ��������\n";
	return true;
}

//���ڲ�����(*)
template<class Type>
bool Vessel<Type>::operator=(const Vessel<Type>* v)
{
	//cout << "*���ڲ�������Ӧ\n";
	//�ж��Ƿ�Խ��
	if (m_maxsize != -1 && m_maxsize < v->m_maxsize)
		return false;

	//ɾ��ԭ��Ԫ��
	if (!is_empty())
		empty();

	//ָ�븴��
	m_head = v->m_head;
	m_rear = v->m_rear;

	//���ƴ�С��Ϣ
	m_maxsize = v->m_maxsize;
	m_size = v->m_size;

	//����״̬��
	m_empty_flag = v->m_empty_flag;
	m_full_flag = v->m_full_flag;

	//cout << "*���ڲ��������\n";
	//cout << name << "�ӹ���" << v->name<<"\n";
	return true;
}

//���ֵ
template<class Type>
Type Vessel<Type>::max()const
{
	Node<Type>* p = m_head;
	Type temp = m_head->data();
	while (p != NULL)
	{
		if (p->data() > temp)
			temp = p->data();
		p = p->next();
	}
	return temp;
}

//��Сֵ
template<class Type>
Type Vessel<Type>::min()const
{
	Node<Type>* p = m_head;
	Type temp = m_head->data();
	while (p != NULL)
	{
		if (p->data() < temp)
			temp = p->data();
		p = p->next();
	}
	return temp;
}

//�ÿ�
template<class Type>
void Vessel<Type>::empty()
{
	Node<Type>* p = m_head;
	while (m_head != NULL)
	{
		m_head = m_head->next();
		delete p;   //free(p);
		p = m_head;
	}
	m_rear = NULL;
	//���´�С��Ϣ
	m_size = 0;

	//����״̬��
	m_empty_flag = true;
	m_full_flag = false;

	//���µ�����
	m_iterator = NULL;
	//cout << "�ÿ���Ӧ\n";
}

//����µ�Ԫ��
template<class Type>
bool Vessel<Type>::append(const Type& d)
{
	if (is_full())
		return false;

	if (m_head == NULL)				//����û��Ԫ�ص����
	{
		//�����½ڵ�
		m_head = new Node<Type>;
		iter_reset();

		//����β���
		m_rear = m_head;

		//���ýڵ�����
		m_head->set_data(d);
		m_head->set_next(NULL);
		m_head->set_pre(NULL);
		//m_head->set_index(m_head->index() + 1);

		//���µ�ǰ��С
		m_size += 1;

		//�����������
		if (m_size == m_maxsize)
			m_full_flag = true;
		m_empty_flag = false;
	}
	else							//������һ��Ԫ�ص����
	{
		//�����½ڵ�
		m_rear->set_next(new Node<Type>);

		//����βָ��
		Node<Type>* temp = m_rear;

		//����βָ��
		m_rear = m_rear->next();

		//���ýڵ�����
		m_rear->set_data(d);
		m_rear->set_next(NULL);
		m_rear->set_pre(temp);
		//m_rear->set_index(m_rear->pre()->index() + 1);		//v���򣬲�ά��index

		//���µ�ǰ��С
		m_size += 1;

		//�����������
		if (m_size == m_maxsize)
			m_full_flag = true;
		m_empty_flag = false;
	}

	return true;
}

//�Ƴ�����ָ��Ԫ��
template<class Type>
bool Vessel<Type>::remove(const Type data)
{
	if (is_empty())
		return false;

	//��������
	bool search_flag = false;
	Node<Type>* p = m_head;

	while (p != NULL) //(m_iterator != NULL)
	{
		bool head_del_flag = false;
		if (p->data() == data)
		{
			search_flag = true;
			if (p == m_head)
			{
				//ɾ���Ľڵ���ͷ���
				m_head = p->next();
				if (m_head != NULL)
					m_head->set_pre(NULL);
				delete p;
				p = m_head;
				//iter_reset();
				head_del_flag = true;
			}
			else if (p == m_rear) //(m_iterator == m_rear)
			{
				//ɾ������β���
				m_rear = p->pre();
				m_rear->set_next(NULL);
				delete p;
				p = m_rear;
			}
			else
			{
				//ɾ�����ǳ���ڵ�
				Node<Type>* temp = p->pre();//Iter<Node<Type>> temp = m_iterator.pre();
				p->pre()->set_next(p->next());
				p->next()->set_pre(p->pre());
				delete p;
				p = temp;
			}
			m_size -= 1;
			m_full_flag = false;
			if (m_size == 0)
				m_empty_flag = true;
		}
		if (!head_del_flag)
			p = p->next();
	}
	iter_reset();
	return search_flag;
}

#endif
#pragma once
#include "Vessel.h"

#ifndef LIST_H_
#define LIST_H_

//��
template<class Type>
class List :public Vessel<Type>
{
	bool m_sort_flag;		//������
	bool m_reverse_flag;	//��ת���

protected:
	virtual bool is_reverse(bool rf) { m_reverse_flag = rf; return m_reverse_flag; };
	virtual bool is_sort(bool sf) { m_sort_flag = sf; return m_sort_flag; };
	virtual bool index_reset();

public:

	//���캯��
	List();
	List(const int);
	List(const List<Type>&);
	List(const Vessel<Type>&);
	List(const Vessel<Type>*);
	List(const List<Type>*);

	//��Ա����
	virtual List<Type>& reverse();
	virtual List<Type>& sort(Iter<Node<Type>>, Iter<Node<Type>>);
	virtual bool is_reverse()const { return m_reverse_flag; };
	virtual bool is_sort()const { return m_sort_flag; };
	virtual bool append(const Type&);
	virtual bool remove(const Type);
	virtual bool insert(Type, int);
	virtual bool dispose(Type&, int);

	//������
	virtual Type operator[](const int)const;
	virtual bool operator=(const List<Type>);
	virtual bool operator=(const List<Type>*);
	friend const List<Type>* operator+(const List<Type>& l1, const List<Type>& l2)
	{
		const Vessel<Type>* l1_v = &l1;
		const Vessel<Type>* l2_v = &l2;

		return new List<Type>((*l1_v + *l2_v));
	}
	friend std::istream& operator>> (std::istream& is, List<Type>& l)
	{
		is >> (Vessel<Type>&)l;
		l.is_reverse(false);
		l.is_sort(false);
		return is;
	};
	friend std::ostream& operator<< (std::ostream& os,const List<Type>& l)
	{
		os << (Vessel<Type>&)l;
		return os;
	};
};

/*****************************************************/
/*****************����ʵ��****************************/

template<class Type>
bool List<Type>::index_reset()
{
	if (Vessel<Type>::is_empty())
		return false;

	//int i = 0;
	Vessel<Type>::iter_reset();
	for (int i = 0; i<Vessel<Type>::size(); i++)		//while (Vessel<Type>::m_iterator != NULL)
	{
		Vessel<Type>::m_iterator->set_index(i);
		++Vessel<Type>::m_iterator;
	}
	Vessel<Type>::iter_reset();

	return true;
}

//���޴�С����
template<class Type>
List<Type>::List():Vessel<Type>()
{
	m_sort_flag = false;
	m_reverse_flag = false;
}

//���޴�С����
template<class Type>
List<Type>::List(const int ms) :Vessel<Type>(ms)
{
	m_sort_flag = false;
	m_reverse_flag = false;
}

//���ƹ���
template<class Type>
List<Type>::List(const List<Type>& l) :Vessel<Type>(*((Vessel<Type>*)(&l)))
{
	m_sort_flag = l.m_sort_flag;
	m_reverse_flag = l.m_reverse_flag;
}

//���๹��
template<class Type>
List<Type>::List(const Vessel<Type>& v) :Vessel<Type>(v)
{
	m_sort_flag = false;
	m_reverse_flag = false;
	index_reset();
}

//����ӹ�
template<class Type>
List<Type>::List(const Vessel<Type>* v):Vessel<Type>(v)
{
	m_sort_flag = false;
	m_reverse_flag = false;
	index_reset();
}

//ͬ��ӹ�
template<class Type>
List<Type>::List(const List<Type>* l) :Vessel<Type>((Vessel<Type>*)l)
{
	m_sort_flag = l->m_sort_flag;
	m_reverse_flag = l->m_reverse_flag;
}

//���ڲ�����
template<class Type>
bool List<Type>::operator=(const List<Type> l)
{

	if (*((Vessel<Type>*)(this)) = *((Vessel<Type>*)(&l)))
	{
		m_sort_flag = l.m_sort_flag;
		m_reverse_flag = l.m_reverse_flag;
		return true;
	}
	else
		return false;
}

//���ڲ�����(*)
template<class Type>
bool List<Type>::operator=(const List<Type>* l)
{
	//cout << "���ڲ�������Ӧ\n";
	//�ж��Ƿ�Խ��
	const Vessel<Type>* l_v = l;
	Vessel<Type>* l_t = this;

	if (!(*l_t = l_v))
		return false;

	//����״̬��
	m_sort_flag = l->m_sort_flag;
	m_reverse_flag = l->m_reverse_flag;

	//cout << "���ڲ��������\n";
	return true;
}

template<class Type>
Type List<Type>::operator[](const int n)const
{
	if (n >= Vessel<Type>::size())
		return (Type)NULL;
	auto p = Vessel<Type>::begin();
	for (int i = 0; i < n; i++)
		p = p.next();
	Type temp = p->data();
	return temp;
}

//��ת
template<class Type>
List<Type>& List<Type>::reverse()
{
	Vessel<Type>::iter_reset();
	while (Vessel<Type>::m_iterator != NULL)
	{
		//pre��next����
		Iter<Node<Type>> temp_next = Vessel<Type>::m_iterator.next();
		Vessel<Type>::m_iterator.set_next(Vessel<Type>::m_iterator.pre());
		Vessel<Type>::m_iterator.set_pre(temp_next);

		Vessel<Type>::m_iterator = temp_next;
	}
	Iter<Node<Type>> temp = Vessel<Type>::begin();
	Vessel<Type>::begin(Vessel<Type>::end());
	Vessel<Type>::end(temp);
	Vessel<Type>::iter_reset();

	index_reset();
	Vessel<Type>::iter_reset();

	if (!m_reverse_flag)
		m_reverse_flag = true;
	else
		m_reverse_flag = false;
	return *this;
}


//����
template<class Type>
List<Type>& List<Type>::sort(Iter<Node<Type>> low, Iter<Node<Type>> high)
{
	Type temp;
	auto i = low, j = high;
	if (low < high)
	{
		temp = low->data();   //ѡȡ��һ���ؼ���Ϊ����

		//�α�ѭ����j��i���м��£
		while (i < j)
		{
			//j�����ƶ����ҵ�������С�Ĺؼ���
			while (i < j && ((j->data()) >= temp)) --j;

			//��������С�Ĺؼ��ַ���ԭ���ᣨ����һ���ؼ��֣�����iǰ��
			if (i < j)
			{
				i->set_data(j->data());
				++i;
			}

			//i�����ƶ����ҵ��������Ĺؼ���
			while (i < j && ((i->data()) < temp)) ++i;

			//����������Ԫ�ط��ڸոձ��ƶ����ظ��ؼ��֣���j��ָ�ؼ��֣�����j����
			if (i < j)
			{
				j->set_data(i->data());
				--j;
			}
		}

		//������黹�����һ��i��λ��
		i->set_data(temp);

		//��ԭ���������ٴλ��ֳ��µ���������
		sort(low, i.pre());

		//��ԭ�����Ұ���ٴλ��ֳ��µ���������
		sort(i.next(), high);
	}
	m_sort_flag = true;

	Vessel<Type>::iter_reset();

	return *this;
}

//����µ�Ԫ��
template<class Type>
bool List<Type>::append(const Type& d)
{
	if (!Vessel<Type>::append(d))
		return false;

	//ά��index
	//index_reset();
	if (Vessel<Type>::end()->pre() != NULL)
		Vessel<Type>::end()->set_index(Vessel<Type>::end()->pre()->index() + 1);
	else
		Vessel<Type>::end()->set_index(0);

	return true;
}

//����µ�Ԫ��
template<class Type>
bool List<Type>::remove(const Type d)
{
	if (!Vessel<Type>::remove(d))
		return false;

	//ά��index
	index_reset();

	return true;
}

//��locλ�ú������Ԫ��
template<class Type>
bool List<Type>::insert(Type d, int loc)
{
	//�ж�λ���Ƿ�Ϸ�
	if (loc < -1 || loc > (Vessel<Type>::size() - 1) || Vessel<Type>::is_full())
		return false;

	//�½����
	Node<Type>* temp = new Node<Type>;
	temp->set_data(d);

	//�����α겢��������λ�ã���0��Ԫ��ǰΪ-1����loc��Ԫ�غ�Ϊn��
	Vessel<Type>::iter_reset();
	for (int i = 0; i < loc; i++)
		++Vessel<Type>::m_iterator;

	//����λ��ѡ����뷽ʽ
	if (loc == -1)		//��ͷǰ�����
	{
		temp->set_next((Node<Type>*)Vessel<Type>::begin());
		Vessel<Type>::begin()->set_pre(temp);
		Vessel<Type>::begin(temp);
	}
	else if (Vessel<Type>::m_iterator->next())	//�ڷ�β�������
	{
		temp->set_next((Node<Type>*)(Vessel<Type>::m_iterator->next()));
		temp->set_pre((Node<Type>*)(Vessel<Type>::m_iterator));
		temp->pre()->set_next(temp);
		temp->next()->set_pre(temp);
	}
	else		//��β������
	{
		Vessel<Type>::m_iterator->set_next(temp);
		temp->set_pre((Node<Type>*)(Vessel<Type>::m_iterator));
		Vessel<Type>::end(temp);
	}

	//����1��ά�����
	Vessel<Type>::m_size += 1;
	if (Vessel<Type>::m_maxsize != -1 && Vessel<Type>::m_size > Vessel<Type>::m_maxsize)
		Vessel<Type>::m_full_flag = true;
	Vessel<Type>::m_empty_flag = false;
	m_sort_flag = false;
	m_reverse_flag = false;

	//ά��index�����õ�����
	index_reset();
	Vessel<Type>::iter_reset();

	return true;
}

//ɾ��locλ��Ԫ��
template<class Type>
bool List<Type>::dispose(Type& d, int loc)
{
	//�ж�λ���Ƿ�Ϸ�
	if (loc < 0 || loc >(Vessel<Type>::size() - 1) || Vessel<Type>::is_empty())
		return false;

	//�����α겢��������λ�ã���0��Ԫ��ǰΪ-1����loc��Ԫ�غ�Ϊn��
	Vessel<Type>::iter_reset();
	for (int i = 0; i < loc; i++)
		++Vessel<Type>::m_iterator;

	//����λ��ѡ��ɾ����ʽ
	if (loc == 0)		//ɾͷ
	{
		Vessel<Type>::begin(Vessel<Type>::m_iterator->next());
		Vessel<Type>::begin()->set_pre(NULL);
	}
	else if (Vessel<Type>::m_iterator->next())	//ɾ����ڵ�
	{
		Vessel<Type>::m_iterator->pre()->set_next(Vessel<Type>::m_iterator->next());
		Vessel<Type>::m_iterator->next()->set_pre(Vessel<Type>::m_iterator->pre());
	}
	else		//ɾβ
	{
		Vessel<Type>::end(Vessel<Type>::m_iterator->pre());
		Vessel<Type>::end()->set_next(NULL);
	}

	//ɾ��
	d = Vessel<Type>::m_iterator->data();
	delete (*Vessel<Type>::m_iterator);

	//����1��ά�����
	Vessel<Type>::m_size -= 1;
	if (Vessel<Type>::m_size == 0)
		Vessel<Type>::m_empty_flag = true;
	Vessel<Type>::m_full_flag = false;

	//ά��index�����õ�����
	index_reset();
	Vessel<Type>::iter_reset();

	return true;
}

#endif
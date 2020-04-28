#pragma once
#include "Vessel.h"

#ifndef LIST_H_
#define LIST_H_

//表
template<class Type>
class List :public Vessel<Type>
{
	bool m_sort_flag;		//排序标记
	bool m_reverse_flag;	//反转标记

protected:
	virtual bool is_reverse(bool rf) { m_reverse_flag = rf; return m_reverse_flag; };
	virtual bool is_sort(bool sf) { m_sort_flag = sf; return m_sort_flag; };
	virtual bool index_reset();

public:

	//构造函数
	List();
	List(const int);
	List(const List<Type>&);
	List(const Vessel<Type>&);
	List(const Vessel<Type>*);
	List(const List<Type>*);

	//成员方法
	virtual List<Type>& reverse();
	virtual List<Type>& sort(Iter<Node<Type>>, Iter<Node<Type>>);
	virtual bool is_reverse()const { return m_reverse_flag; };
	virtual bool is_sort()const { return m_sort_flag; };
	virtual bool append(const Type&);
	virtual bool remove(const Type);
	virtual bool insert(Type, int);
	virtual bool dispose(Type&, int);

	//操作符
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
/*****************方法实现****************************/

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

//无限大小表构造
template<class Type>
List<Type>::List():Vessel<Type>()
{
	m_sort_flag = false;
	m_reverse_flag = false;
}

//有限大小表构造
template<class Type>
List<Type>::List(const int ms) :Vessel<Type>(ms)
{
	m_sort_flag = false;
	m_reverse_flag = false;
}

//复制构造
template<class Type>
List<Type>::List(const List<Type>& l) :Vessel<Type>(*((Vessel<Type>*)(&l)))
{
	m_sort_flag = l.m_sort_flag;
	m_reverse_flag = l.m_reverse_flag;
}

//基类构造
template<class Type>
List<Type>::List(const Vessel<Type>& v) :Vessel<Type>(v)
{
	m_sort_flag = false;
	m_reverse_flag = false;
	index_reset();
}

//基类接管
template<class Type>
List<Type>::List(const Vessel<Type>* v):Vessel<Type>(v)
{
	m_sort_flag = false;
	m_reverse_flag = false;
	index_reset();
}

//同类接管
template<class Type>
List<Type>::List(const List<Type>* l) :Vessel<Type>((Vessel<Type>*)l)
{
	m_sort_flag = l->m_sort_flag;
	m_reverse_flag = l->m_reverse_flag;
}

//等于操作符
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

//等于操作符(*)
template<class Type>
bool List<Type>::operator=(const List<Type>* l)
{
	//cout << "等于操作符响应\n";
	//判断是否越界
	const Vessel<Type>* l_v = l;
	Vessel<Type>* l_t = this;

	if (!(*l_t = l_v))
		return false;

	//复制状态符
	m_sort_flag = l->m_sort_flag;
	m_reverse_flag = l->m_reverse_flag;

	//cout << "等于操作符完成\n";
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

//反转
template<class Type>
List<Type>& List<Type>::reverse()
{
	Vessel<Type>::iter_reset();
	while (Vessel<Type>::m_iterator != NULL)
	{
		//pre和next互换
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


//排序
template<class Type>
List<Type>& List<Type>::sort(Iter<Node<Type>> low, Iter<Node<Type>> high)
{
	Type temp;
	auto i = low, j = high;
	if (low < high)
	{
		temp = low->data();   //选取第一个关键字为枢轴

		//游标循环，j、i向中间聚拢
		while (i < j)
		{
			//j向左移动，找到比枢轴小的关键字
			while (i < j && ((j->data()) >= temp)) --j;

			//将比枢轴小的关键字放在原枢轴（即第一个关键字）处，i前移
			if (i < j)
			{
				i->set_data(j->data());
				++i;
			}

			//i向右移动，找到比枢轴大的关键字
			while (i < j && ((i->data()) < temp)) ++i;

			//将比枢轴大的元素放在刚刚被移动的重复关键字（即j所指关键字）处，j后移
			if (i < j)
			{
				j->set_data(i->data());
				--j;
			}
		}

		//将枢轴归还于最后一个i的位置
		i->set_data(temp);

		//对原枢轴左半侧再次划分出新的枢轴排序
		sort(low, i.pre());

		//对原枢轴右半侧再次划分出新的枢轴排序
		sort(i.next(), high);
	}
	m_sort_flag = true;

	Vessel<Type>::iter_reset();

	return *this;
}

//添加新的元素
template<class Type>
bool List<Type>::append(const Type& d)
{
	if (!Vessel<Type>::append(d))
		return false;

	//维护index
	//index_reset();
	if (Vessel<Type>::end()->pre() != NULL)
		Vessel<Type>::end()->set_index(Vessel<Type>::end()->pre()->index() + 1);
	else
		Vessel<Type>::end()->set_index(0);

	return true;
}

//添加新的元素
template<class Type>
bool List<Type>::remove(const Type d)
{
	if (!Vessel<Type>::remove(d))
		return false;

	//维护index
	index_reset();

	return true;
}

//在loc位置后插入新元素
template<class Type>
bool List<Type>::insert(Type d, int loc)
{
	//判断位置是否合法
	if (loc < -1 || loc > (Vessel<Type>::size() - 1) || Vessel<Type>::is_full())
		return false;

	//新建结点
	Node<Type>* temp = new Node<Type>;
	temp->set_data(d);

	//建立游标并来到插入位置（第0个元素前为-1，第loc个元素后为n）
	Vessel<Type>::iter_reset();
	for (int i = 0; i < loc; i++)
		++Vessel<Type>::m_iterator;

	//根据位置选择插入方式
	if (loc == -1)		//在头前面插入
	{
		temp->set_next((Node<Type>*)Vessel<Type>::begin());
		Vessel<Type>::begin()->set_pre(temp);
		Vessel<Type>::begin(temp);
	}
	else if (Vessel<Type>::m_iterator->next())	//在非尾部面插入
	{
		temp->set_next((Node<Type>*)(Vessel<Type>::m_iterator->next()));
		temp->set_pre((Node<Type>*)(Vessel<Type>::m_iterator));
		temp->pre()->set_next(temp);
		temp->next()->set_pre(temp);
	}
	else		//在尾部插入
	{
		Vessel<Type>::m_iterator->set_next(temp);
		temp->set_pre((Node<Type>*)(Vessel<Type>::m_iterator));
		Vessel<Type>::end(temp);
	}

	//表长加1，维护标记
	Vessel<Type>::m_size += 1;
	if (Vessel<Type>::m_maxsize != -1 && Vessel<Type>::m_size > Vessel<Type>::m_maxsize)
		Vessel<Type>::m_full_flag = true;
	Vessel<Type>::m_empty_flag = false;
	m_sort_flag = false;
	m_reverse_flag = false;

	//维护index，重置迭代器
	index_reset();
	Vessel<Type>::iter_reset();

	return true;
}

//删除loc位置元素
template<class Type>
bool List<Type>::dispose(Type& d, int loc)
{
	//判断位置是否合法
	if (loc < 0 || loc >(Vessel<Type>::size() - 1) || Vessel<Type>::is_empty())
		return false;

	//建立游标并来到插入位置（第0个元素前为-1，第loc个元素后为n）
	Vessel<Type>::iter_reset();
	for (int i = 0; i < loc; i++)
		++Vessel<Type>::m_iterator;

	//根据位置选择删除方式
	if (loc == 0)		//删头
	{
		Vessel<Type>::begin(Vessel<Type>::m_iterator->next());
		Vessel<Type>::begin()->set_pre(NULL);
	}
	else if (Vessel<Type>::m_iterator->next())	//删常规节点
	{
		Vessel<Type>::m_iterator->pre()->set_next(Vessel<Type>::m_iterator->next());
		Vessel<Type>::m_iterator->next()->set_pre(Vessel<Type>::m_iterator->pre());
	}
	else		//删尾
	{
		Vessel<Type>::end(Vessel<Type>::m_iterator->pre());
		Vessel<Type>::end()->set_next(NULL);
	}

	//删除
	d = Vessel<Type>::m_iterator->data();
	delete (*Vessel<Type>::m_iterator);

	//表长减1，维护标记
	Vessel<Type>::m_size -= 1;
	if (Vessel<Type>::m_size == 0)
		Vessel<Type>::m_empty_flag = true;
	Vessel<Type>::m_full_flag = false;

	//维护index，重置迭代器
	index_reset();
	Vessel<Type>::iter_reset();

	return true;
}

#endif
#pragma once
#include <iostream>
#include "Node.h"
#include "Iter.h"
#include<string>

#ifndef VESSEL_H_
#define VESSEL_H_

using std::cout;
//容器
template<class Type>
class Vessel
{
	//游标
	Node<Type>* m_head;
	Node<Type>* m_rear;

protected:

	//属性
	int m_maxsize;		//最大大小
	int m_size;			//当前大小

	//标记
	bool m_empty_flag;	//为空标记
	bool m_full_flag;	//为满标记

	//迭代器
	Iter<Node<Type>> m_iterator;
	virtual void iter_reset() { m_iterator = m_head; };
	virtual Iter<Node<Type>> begin(Iter<Node<Type>> iter) { m_head = *iter; return Iter<Node<Type>>(m_head); };
	virtual Iter<Node<Type>> end(Iter<Node<Type>> iter) { m_rear = *iter; return Iter<Node<Type>>(m_rear); };

public:
	std::string name;

	//构造函数
	Vessel();
	Vessel(const int);
	Vessel(const Vessel<Type>&);
	Vessel(const Vessel<Type>*);
	virtual ~Vessel();


	virtual Iter<Node<Type>> begin()const { return m_head; };
	virtual Iter<Node<Type>> end()const { return m_rear; };


	//成员方法
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

	//操作符
	virtual bool operator=(const Vessel<Type>);
	virtual bool operator=(const Vessel<Type>*);
	friend const Vessel<Type>* operator+(const Vessel<Type>& v1,const Vessel<Type>& v2)
	{
		//为空检测
		if (v1.is_empty())
			return &v2;

		if (v2.is_empty())
			return &v1;

		//创建新容器
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

		//复制v1
		for (int i = 0; i < v1.size(); i++)
		{
			v->append(p_v1->data());
			p_v1++;
			//p_v1.set(p_v1.iterator()->next());
		}

		//复制v2
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
/*****************方法实现****************************/

//无限大小容器初始化
template<class Type>
Vessel<Type>::Vessel()
{
	//name = "临时对象";
	m_head = NULL;
	m_iterator = m_head;
	m_rear = NULL;
	m_maxsize = -1;		//无限大小
	m_size = 0;
	m_empty_flag = true;
	m_full_flag = false;
	//cout << "无限大小容器构造完成\n";
}

//有限大小容器初始化
template<class Type>
Vessel<Type>::Vessel(const int ms)
{
	//name = "临时对象";
	m_head = NULL;
	m_iterator = m_head;
	m_rear = NULL;
	m_maxsize = ms;		//有限大小
	m_size = 0;
	m_empty_flag = true;
	m_full_flag = false;
	//cout << "有限大小容器构造完成\n";
}

//复制构造
template<class Type>
Vessel<Type>::Vessel(const Vessel<Type>& v)
{
	//name = v.name+"的临时对象";
	//复制头结点
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
		m_rear->set_next(new Node<Type>); //设置指针域，制造新节点
		Node<Type>* temp = m_rear;
		m_rear = m_rear->next();		//p_this移动到新节点
		m_rear->set_data(p_v->data());	//新节点设置数据
		m_rear->set_next(NULL);			//新节点指针域置空
		m_rear->set_pre(temp);
		m_rear->set_index(p_v->index());

		p_v = p_v->next();
	}

	//复制大小信息
	m_maxsize = v.m_maxsize;
	m_size = v.m_size;

	//复制状态符
	m_empty_flag = v.m_empty_flag;
	m_full_flag = v.m_full_flag;
	//cout<<v.name << "的复制构造完成\n";
}

//同类接管(*)
template<class Type>
Vessel<Type>::Vessel(const Vessel<Type>* v)
{
	//指针复制
	m_head = v->m_head;
	m_rear = v->m_rear;

	//复制大小信息
	m_maxsize = v->m_maxsize;
	m_size = v->m_size;

	//复制状态符
	m_empty_flag = v->m_empty_flag;
	m_full_flag = v->m_full_flag;

	//cout << v->name << "的*复制构造完成\n";
	//cout << name << "接管了" << v->name << "\n";
}

//容器析构
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
	//cout << name << "析构完成\n";
}

//等于操作符
template<class Type>
bool Vessel<Type>::operator=(const Vessel<Type> v)
{
	//cout << "等于操作符响应\n";
	//判断是否越界
	if (m_maxsize != -1 && m_maxsize < v.m_maxsize)
		return false;

	//删除原有元素
	if (!is_empty())
		empty();

	//复制头结点
	m_head = new Node<Type>;
	iter_reset();		//设置迭代器
	m_head->set_data(v.m_head->data());
	m_head->set_next(NULL);
	m_head->set_pre(NULL);
	m_head->set_index(0);

	m_rear = m_head;
	Node<Type>* p_v = v.m_head->next();

	for (int i = 1; i < v.m_size; i++)
	{
		m_rear->set_next(new Node<Type>); //设置指针域，制造新节点
		Node<Type>* temp = m_rear;
		m_rear = m_rear->next();		//p_this移动到新节点
		m_rear->set_data(p_v->data());	//新节点设置数据
		m_rear->set_next(NULL);			//新节点指针域置空
		m_rear->set_pre(temp);
		m_rear->set_index(p_v->index());

		p_v = p_v->next();
	}

	//复制大小信息
	m_maxsize = v.m_maxsize;
	m_size = v.m_size;

	//复制状态符
	m_empty_flag = v.m_empty_flag;
	m_full_flag = v.m_full_flag;

	//cout << "等于操作符完成\n";
	return true;
}

//等于操作符(*)
template<class Type>
bool Vessel<Type>::operator=(const Vessel<Type>* v)
{
	//cout << "*等于操作符响应\n";
	//判断是否越界
	if (m_maxsize != -1 && m_maxsize < v->m_maxsize)
		return false;

	//删除原有元素
	if (!is_empty())
		empty();

	//指针复制
	m_head = v->m_head;
	m_rear = v->m_rear;

	//复制大小信息
	m_maxsize = v->m_maxsize;
	m_size = v->m_size;

	//复制状态符
	m_empty_flag = v->m_empty_flag;
	m_full_flag = v->m_full_flag;

	//cout << "*等于操作符完成\n";
	//cout << name << "接管了" << v->name<<"\n";
	return true;
}

//最大值
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

//最小值
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

//置空
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
	//更新大小信息
	m_size = 0;

	//更新状态符
	m_empty_flag = true;
	m_full_flag = false;

	//更新迭代器
	m_iterator = NULL;
	//cout << "置空响应\n";
}

//添加新的元素
template<class Type>
bool Vessel<Type>::append(const Type& d)
{
	if (is_full())
		return false;

	if (m_head == NULL)				//容器没有元素的情况
	{
		//创建新节点
		m_head = new Node<Type>;
		iter_reset();

		//更新尾结点
		m_rear = m_head;

		//设置节点内容
		m_head->set_data(d);
		m_head->set_next(NULL);
		m_head->set_pre(NULL);
		//m_head->set_index(m_head->index() + 1);

		//更新当前大小
		m_size += 1;

		//更新容器标记
		if (m_size == m_maxsize)
			m_full_flag = true;
		m_empty_flag = false;
	}
	else							//有至少一个元素的情况
	{
		//创建新节点
		m_rear->set_next(new Node<Type>);

		//保存尾指针
		Node<Type>* temp = m_rear;

		//更新尾指针
		m_rear = m_rear->next();

		//设置节点内容
		m_rear->set_data(d);
		m_rear->set_next(NULL);
		m_rear->set_pre(temp);
		//m_rear->set_index(m_rear->pre()->index() + 1);		//v无序，不维护index

		//更新当前大小
		m_size += 1;

		//更新容器标记
		if (m_size == m_maxsize)
			m_full_flag = true;
		m_empty_flag = false;
	}

	return true;
}

//移除所有指定元素
template<class Type>
bool Vessel<Type>::remove(const Type data)
{
	if (is_empty())
		return false;

	//遍历搜索
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
				//删除的节点是头结点
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
				//删除的是尾结点
				m_rear = p->pre();
				m_rear->set_next(NULL);
				delete p;
				p = m_rear;
			}
			else
			{
				//删除的是常规节点
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
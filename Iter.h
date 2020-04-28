#pragma once

#ifndef ITER_H_
#define ITER_H_

template<class Type>
class Iter
{
protected:
	Type* m_p;

public:
	//构造函数
	Iter() :m_p(NULL) {};
	Iter(Type* p) :m_p(p) {};

	virtual Iter<Type> pre() { return Iter<Type>(m_p->pre()); };
	virtual Iter<Type> next() { return Iter<Type>(m_p->next()); };

	virtual void set_next(Iter<Type> n) { m_p->set_next(n.m_p); };
	virtual void set_pre(Iter<Type> p) { m_p->set_pre(p.m_p); };

	//操作符
	virtual Type* operator++() { m_p = m_p->next(); return m_p; };
	virtual Type* operator++(int) { Type* old = m_p; m_p = m_p->next(); return old; };
	virtual Type* operator--() { m_p = m_p->pre(); return m_p; };
	virtual Type* operator--(int) { Type* old = m_p; m_p = m_p->pre(); return old; };

	virtual void operator=(const Iter<Type>& it) { m_p = it.m_p; };
	virtual void operator=(Type* it) { m_p = it; };
	explicit virtual operator Type* ()const { return m_p; };

	virtual bool operator>(const Iter<Type> it)const { if (m_p == NULL)return false; if (it.m_p == NULL)return true; return (m_p->index() > it.m_p->index()); };
	virtual bool operator<(const Iter<Type> it)const { if (it.m_p == NULL)return false; if (m_p == NULL)return true; return (m_p->index() < it.m_p->index()); };
	virtual bool operator>=(const Iter<Type> it)const { if (it.m_p == NULL)return true; if (m_p == NULL)return false; return (m_p->index() >= it.m_p->index()); };
	virtual bool operator<=(const Iter<Type> it)const { if (m_p == NULL)return true; if (it.m_p == NULL)return false; return (m_p->index() <= it.m_p->index()); };
	virtual bool operator==(const Iter<Type> it)const { return m_p == it.m_p; };
	virtual bool operator!=(const Iter<Type> it)const { return m_p != it.m_p; };

	virtual Type* operator->()const { return m_p; };
	virtual Type* operator*()const { return m_p; };
};


#endif
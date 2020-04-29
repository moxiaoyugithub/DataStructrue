#include "Vessel.h"
#include "List.h"
//#include "Stack.h"
//#include "Queue.h"

using std::cin;
using std::cout;
using std::endl;

int main()
{
	//没有参数代表无限大小
	cout << "无限大小的v1：";
	List<double> v1;
	cin >> v1;
	v1.name = "v1";
	cout << "v1 = " << v1 << endl;

	//参数3代表容器最大大小为3
	cout << "大小为3的v2：";
	List<double> v2(3);
	cin >> v2;
	v2.name = "v2";
	cout << "v2 = " << v2 << endl;
	
	//两个容器的加法
	cout << "大小为6的v3：";
	List<double> v3(6);
	v3.name = "v3";
	v3 = v1 + v2;
	cout << "v3 = v1 + v2\n   =" << v3 << endl;

	//加法带来的容器大小上限改变
	if (v3.maxsize() != -1)
		cout << "v3大小上限为" << v3.maxsize() << endl;
	else
		cout << "v3大小上限为无限" << endl;

	//访问每个元素的索引
	cout << "使用迭代器访问索引：";
	Iter<Node<double>> p = v1.end();
	cout << "v1:\n";
	while (p!=NULL)
	{
		cout << p->index() << ": " << p->data() << endl;
		--p;
	}

	//使用下标，用类似数组的方式访问容器
	cout << "3号元素为" << v3[3] << endl;

	//移除所有值为rmv的数据
	int rmv;
	cout << "移除：";
	cin >> rmv;
	v3.remove(rmv);
	cout << "移除" << rmv << "后,v3 = " << v3 << endl;

	//排序功能
	cout << "排序：";
	v3.sort(v3.begin(), v3.end());
	cout << v3 << endl;

	//反转功能
	cout << "反转：";
	v3.reverse();
	cout << v3 << endl;

	//在2号元素后插入x，编号从0开始，在0号元素前插入需要在编号参数处填入参数-1
	cout << "插入：";
	double x;
	cin >> x;
	v3.insert(x, 2);	//在2号元素后插入x
	cout << v3 << endl;

	//去除4号元素
	cout << "去除：";
	v3.dispose(x, 4);	//去掉4号元素，x用来接收去掉的元素值
	cout << x << endl;

	return 0;
}

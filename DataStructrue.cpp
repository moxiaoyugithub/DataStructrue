#include "Vessel.h"
#include "List.h"
//#include "Stack.h"
//#include "Queue.h"

using std::cin;
using std::cout;
using std::endl;

int main()
{
	//û�в����������޴�С
	cout << "���޴�С��v1��";
	List<double> v1;
	cin >> v1;
	v1.name = "v1";
	cout << "v1 = " << v1 << endl;

	//����3������������СΪ3
	cout << "��СΪ3��v2��";
	List<double> v2(3);
	cin >> v2;
	v2.name = "v2";
	cout << "v2 = " << v2 << endl;
	
	//���������ļӷ�
	cout << "��СΪ6��v3��";
	List<double> v3(6);
	v3.name = "v3";
	v3 = v1 + v2;
	cout << "v3 = v1 + v2\n   =" << v3 << endl;

	//�ӷ�������������С���޸ı�
	if (v3.maxsize() != -1)
		cout << "v3��С����Ϊ" << v3.maxsize() << endl;
	else
		cout << "v3��С����Ϊ����" << endl;

	//����ÿ��Ԫ�ص�����
	cout << "ʹ�õ���������������";
	Iter<Node<double>> p = v1.end();
	cout << "v1:\n";
	while (p!=NULL)
	{
		cout << p->index() << ": " << p->data() << endl;
		--p;
	}

	//ʹ���±꣬����������ķ�ʽ��������
	cout << "3��Ԫ��Ϊ" << v3[3] << endl;

	//�Ƴ�����ֵΪrmv������
	int rmv;
	cout << "�Ƴ���";
	cin >> rmv;
	v3.remove(rmv);
	cout << "�Ƴ�" << rmv << "��,v3 = " << v3 << endl;

	//������
	cout << "����";
	v3.sort(v3.begin(), v3.end());
	cout << v3 << endl;

	//��ת����
	cout << "��ת��";
	v3.reverse();
	cout << v3 << endl;

	//��2��Ԫ�غ����x����Ŵ�0��ʼ����0��Ԫ��ǰ������Ҫ�ڱ�Ų������������-1
	cout << "���룺";
	double x;
	cin >> x;
	v3.insert(x, 2);	//��2��Ԫ�غ����x
	cout << v3 << endl;

	//ȥ��4��Ԫ��
	cout << "ȥ����";
	v3.dispose(x, 4);	//ȥ��4��Ԫ�أ�x��������ȥ����Ԫ��ֵ
	cout << x << endl;

	return 0;
}
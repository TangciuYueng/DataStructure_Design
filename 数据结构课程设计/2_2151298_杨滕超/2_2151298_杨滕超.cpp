#include "2_2151298_������.h"

using namespace std;

/*
* ��֤��List�ǽ�������
*/

/***************************************************************************
  �������ƣ�intersection
  ��    �ܣ���������Ľ���
  ���������List<T>& l1, List<T>& l2���������������
  �� �� ֵ��List<T>�¹����һ����������
  ˵    ����
***************************************************************************/
template<class T>
List<T> intersection(List<T>& l1, List<T>& l2)
{
	List<int> ans;
	auto it1 = l1.begin(), it2 = l2.begin();
	while (it1 != l1.end() && it2 != l2.end())
	{
		if (*it1 == *it2)
		{
			ans.emplace_back(*it1);
			++it1;
			++it2;
		}
		else if(*it1 < *it2)
		{
			++it1;
		}
		else
		{
			++it2;
		}
	}
	return ans;
}
int main() {
	List<int> l1, l2, l3;
	int num = 0;
	bool cinFail = false;
	
	cout << "�������һ���ǽ�����������: " << endl;
	while (1)
	{
		l1.clear();
		while (1)
		{
			cin >> num;
			if (cinFail = cin.fail())
			{
				cout << "���벻������������������" << endl;
				cin.clear();
				cin.ignore(65536, '\n');
				break;
			}
			if (num == -1)
				break;
			else
				l1.emplace_back(num);
		}
		if (!cinFail)
			break;
	}
	
	cout << "������ڶ����ǽ�����������: " << endl;
	while (1)
	{
		l2.clear();
		while (1)
		{
			cin >> num;
			if (cinFail = cin.fail())
			{
				cout << "���벻������������������" << endl;
				cin.clear();
				cin.ignore(65536, '\n');
				break;
			}
			if (num == -1)
				break;
			else
				l2.emplace_back(num);
		}
		if (!cinFail)
			break;
	}
	//����
	l1.mergeSort2();
	l2.mergeSort2();
/*
	cout << endl << "L1" << endl;
	for (auto it = l1.begin(); it != l1.end(); ++it)
		cout << *it << ' ';

	cout << endl<< "L2" << endl;
	for (auto it = l2.begin(); it != l2.end(); ++it)
		cout << *it << ' ';
*/

	//�󽻼�
	l3 = intersection(l1, l2);
	if (l3.empty())
		cout << "NULL" << endl;
	else
	{
		cout << endl;
		for (auto it = l3.begin(); it != l3.end(); ++it)
			cout << *it << ' ';
	}
	cout << endl;


	cout << "�������������";
	cin.clear();
	cin.ignore(65536, '\n');
	cin.get();
	return 0;
}
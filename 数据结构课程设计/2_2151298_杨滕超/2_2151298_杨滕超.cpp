#include "2_2151298_杨滕超.h"

using namespace std;

/*
* 保证了List非降序排列
*/

/***************************************************************************
  函数名称：intersection
  功    能：求两链表的交集
  输入参数：List<T>& l1, List<T>& l2，两个链表的引用
  返 回 值：List<T>新构造的一个交集链表
  说    明：
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
	
	cout << "请输入第一个非降序链表序列: " << endl;
	while (1)
	{
		l1.clear();
		while (1)
		{
			cin >> num;
			if (cinFail = cin.fail())
			{
				cout << "输入不是整数，请重新输入" << endl;
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
	
	cout << "请输入第二个非降序链表序列: " << endl;
	while (1)
	{
		l2.clear();
		while (1)
		{
			cin >> num;
			if (cinFail = cin.fail())
			{
				cout << "输入不是整数，请重新输入" << endl;
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
	//排序
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

	//求交集
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


	cout << "输入任意键继续";
	cin.clear();
	cin.ignore(65536, '\n');
	cin.get();
	return 0;
} 

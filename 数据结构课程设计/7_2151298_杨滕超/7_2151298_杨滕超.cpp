#include "7_2151298_杨滕超.h"

/***************************************************************************
  函数名称：to_be_continue
  功    能：等待用户输入任意键，再关闭cmd窗口
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void to_be_continue()
{
	cout << endl << "回车键继续操作" << endl;
	cin.clear();
	cin.ignore(65536, '\n');
	cin.get();
	return;
}

int main()
{
	int N, temp;
	int cost = 0;
	//优先队列，最小的先出来
	//贪心，优先锯短的，花费更少
	Priority_queue<int, Vector<int>, Greater<int>> woods;
	while (1)
	{
		cin >> N;
		if (cin.fail() || N < 1 || N > 1e4)
		{
			cout << "输入有误，请重新输入" << endl;
			cin.clear();
			cin.ignore(65536, '\n');
		}
		else
			break;
	}
	for (int i = 0; i < N; ++i)
	{
		cin >> temp;
		if (cin.fail() || N < 1)
		{
			cout << "输入有误，请重新输入正整数" << endl;
			cin.clear();
			cin.ignore(65536, '\n');
			--i;//重新输入该数
		}
		else
			woods.emplace(temp);
	}
	if (N == 1)
		cost = 0;
	else
	{
		//逆向模拟该过程，不断从切好的集合中选取两条代价最小的拼接在一起
		while (woods.size() > 1)
		{
			int len1 = woods.top();
			woods.pop();
			int len2 = woods.top();
			woods.pop();

			cost += len1 + len2;
			woods.emplace(len1 + len2);
		}
	}

	cout << cost;
	//回车结束
	to_be_continue();
	return 0;
}
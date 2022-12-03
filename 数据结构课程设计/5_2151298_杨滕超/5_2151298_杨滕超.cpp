#include "5_2151298_杨滕超.h"

using namespace std;

/***************************************************************************
  函数名称：to_be_continue
  功    能：程序结束后等到用户输入任意字符再关闭cmd窗口
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
/***************************************************************************
  函数名称：bank
  功    能：将顾客编号为奇数的放入A队列，
			偶数放入B队列，按照要求依次输出顾客编号
  输入参数：Vector<int>& nums，用户输入的银行顾客序列
  返 回 值：
  说    明：
***************************************************************************/
void bank(Vector<int>& nums)
{
	int Size = nums.size();
	bool isA = false;
	Queue<int> A, B;

	for (int i = 0; i < Size; ++i)
	{
		if (nums[i] % 2)
			A.emplace(nums[i]);
		else
			B.emplace(nums[i]);
	}
	cout << endl << "业务完成顺序为" << endl;
	while (Size)
	{
		//每一轮A出两个B出一个
		if (!A.empty())
		{
			if (Size == nums.size())
				cout << A.front();
			else
				cout << ' ' << A.front();
			A.pop();
			--Size;
		}
		if (!A.empty())
		{

			cout << ' ' << A.front();
			A.pop();
			--Size;

		}
		if (!B.empty())
		{
			if (Size == nums.size())
				cout << B.front();
			else
				cout << ' ' << B.front();
			B.pop();
			--Size;
		}
	}
	cout << endl;
}
int main() {
	int size;
	cout << "input number" << endl;
	while (1)
	{
		cin >> size;
		if (cin.fail() || size < 1)
		{
			cout << "输入人数有误，请重新输入" << endl;
			cin.clear();
			cin.ignore(65536, '\n');
		}
		else
			break;
	}
	Vector<int> nums(size, 0);
	cout << endl << "请输入顾客编号" << endl;
	for (int i = 0; i < size; ++i)
	{
		cin >> nums[i];
		if (cin.fail())
		{
			cout << "输入有误，请重新输入!" << endl;
			cin.clear();
			cin.ignore(65536, '\n');
			--i;//重新输入该项
		}
	}

	bank(nums);

	to_be_continue();
	return 0;
}

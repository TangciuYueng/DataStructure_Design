#include "5_2151298_������.h"

using namespace std;


/***************************************************************************
  �������ƣ�to_be_continue
  ��    �ܣ����������ȵ��û����������ַ��ٹر�cmd����
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void to_be_continue()
{
	cout << endl << "�س�����������" << endl;
	cin.clear();
	cin.ignore(65536, '\n');
	cin.get();
	return;
}
/***************************************************************************
  �������ƣ�bank
  ��    �ܣ����˿ͱ��Ϊ�����ķ���A���У�
			ż������B���У�����Ҫ����������˿ͱ��
  ���������Vector<int>& nums���û���������й˿�����
  �� �� ֵ��
  ˵    ����
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
	cout << endl << "ҵ�����˳��Ϊ" << endl;
	while (Size)
	{
		//ÿһ��A������B��һ��
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
			cout << "����������������������" << endl;
			cin.clear();
			cin.ignore(65536, '\n');
		}
		else
			break;
	}
	Vector<int> nums(size, 0);
	cout << endl << "������˿ͱ��" << endl;
	for (int i = 0; i < size; ++i)
	{
		cin >> nums[i];
		if (cin.fail())
		{
			cout << "������������������!" << endl;
			cin.clear();
			cin.ignore(65536, '\n');
			--i;//�����������
		}
	}

	bank(nums);

	to_be_continue();
	return 0;
}
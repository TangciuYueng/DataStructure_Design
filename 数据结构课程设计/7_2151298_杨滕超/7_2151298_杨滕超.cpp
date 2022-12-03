#include "7_2151298_������.h"

/***************************************************************************
  �������ƣ�to_be_continue
  ��    �ܣ��ȴ��û�������������ٹر�cmd����
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

int main()
{
	int N, temp;
	int cost = 0;
	//���ȶ��У���С���ȳ���
	//̰�ģ����Ⱦ�̵ģ����Ѹ���
	Priority_queue<int, Vector<int>, Greater<int>> woods;
	while (1)
	{
		cin >> N;
		if (cin.fail() || N < 1 || N > 1e4)
		{
			cout << "������������������" << endl;
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
			cout << "������������������������" << endl;
			cin.clear();
			cin.ignore(65536, '\n');
			--i;//�����������
		}
		else
			woods.emplace(temp);
	}
	if (N == 1)
		cost = 0;
	else
	{
		//����ģ��ù��̣����ϴ��кõļ�����ѡȡ����������С��ƴ����һ��
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
	//�س�����
	to_be_continue();
	return 0;
}
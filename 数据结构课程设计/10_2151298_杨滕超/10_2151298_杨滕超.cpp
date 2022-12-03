#include "10_2151298_������.h"

int NUM;
int* nums = NULL;

/***************************************************************************
  �������ƣ�show
  ��    �ܣ�չʾ��ѡ��������㷨��ʱ�䡢�����������ƶ�����
  ���������const char* sortName, void(*func)(int*, int, accord&)
			�������ƣ������㷨����ָ��
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void show(const char* sortName, void(*func)(int*, int, accord&))
{
	int* temp = new(nothrow) int[NUM];
	if (temp == NULL)
		return;
	//��ֵ��temp����
	for (int i = 0; i < NUM; ++i)
		temp[i] = nums[i];

	accord data;

	//��¼��ʼʱ��
	auto begin = chrono::steady_clock::now();

	func(temp, NUM, data);
	//��¼����ʱ��
	auto end = chrono::steady_clock::now();
	//����ʱ���
	auto Duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
	//����ʱ��̫�٣�ms�޷���¼���æ�s��¼
	bool isMs = true;
	if (Duration == 0)
	{
		isMs = false;
		Duration = chrono::duration_cast<chrono::microseconds>(end - begin).count();
	}

	cout << sortName << "����ʱ��: " << "\t\t" << Duration;
	if (isMs)
		cout << "����" << endl;
	else
		cout << "΢��" << endl;
	cout << sortName << "��������: " << "\t\t" << data.move << endl;
	cout << sortName << "�Ƚϴ���: " << "\t\t" << data.cmp << endl;


	delete[] temp;
}


int main() {
	cout << "**\t\t�����㷨�Ƚ�    \t\t**" << endl;
	cout << "==================================================" << endl;
	cout << "**\t\t1 --- ð������    \t\t**" << endl;
	cout << "**\t\t2 --- ѡ������    \t\t**" << endl;
	cout << "**\t\t3 --- ֱ�Ӳ�������\t\t**" << endl;
	cout << "**\t\t4 --- ϣ������    \t\t**" << endl;
	cout << "**\t\t5 --- ����(����)    \t\t**" << endl;
	cout << "**\t\t6 --- ����(�ݹ�)    \t\t**" << endl;
	cout << "**\t\t7 --- ������(����)    \t\t**" << endl;
	cout << "**\t\t8 --- ������(�ݹ�)    \t\t**" << endl;
	cout << "**\t\t9 --- �鲢����    \t\t**" << endl;
	cout << "**\t\t10 --- ��������    \t\t**" << endl;
	cout << "**\t\t11 --- ����LSD����\t\t**" << endl;
	cout << "**\t\t12 --- ����MSD����\t\t**" << endl;
	cout << "**\t\t13 --- �˳�����    \t\t**" << endl;
	cout << "==================================================" << endl;

	cout << "�������������1e5ʱ����ʹ��ѡ��1��2��3" << endl;
	cout << "������Ҫ������������ĸ���(������1e8): ";
	while (1) {
		cin >> NUM;
		if (cin.fail() || NUM <= 0 || NUM > 1e8)
		{
			cout << "����������������������" << endl;
			cin.clear();
			cin.ignore(65536, '\n');
		}
		else
			break;
	}

	//����ռ�
	nums = new(nothrow) int[NUM];
	if (nums == NULL)
		return -1;
	//���������
	randomArray(nums, NUM);
	bool loop = true;
	String op;
	while (loop)
	{
		cout << endl << "��ѡ�������㷨:\t\t\t";
		cin >> op;
		if (op == "1" && NUM < 1e5)
			show("ð������", bubbleSort);
		else if (op == "2" && NUM < 1e5)
			show("ѡ������", selectSort);
		else if (op == "3" && NUM < 1e5)
			show("ֱ�Ӳ�������", insertSort);
		else if (op == "4")
			show("ϣ������", shellSort);
		else if (op == "5")
			show("����(����)", quickSort2);
		else if (op == "6")
			show("����(�ݹ�)", quickSort1);
		else if (op == "7")
			show("������(����)", heapSort1);
		else if (op == "8")
			show("������(�ݹ�)", heapSort2);
		else if (op == "9")
			show("�鲢����", mergeSort);
		else if (op == "10")
			show("��������", countingSort);
		else if (op == "11")
			show("����LSD����", radixSortLSD);
		else if (op == "12")
			show("����MSD����", radixSortMSD);
		else if (op == "13")
			loop = 0;
		else
		{
			cout << "������������������" << endl;
			cin.clear();
			cin.ignore(65536, '\n');
		}
	}
	//�ͷſռ�
	delete[] nums;
	return 0;
}
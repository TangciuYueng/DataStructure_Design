#include "10_2151298_杨滕超.h"

int NUM;
int* nums = NULL;

/***************************************************************************
  函数名称：show
  功    能：展示所选择的排序算法的时间、交换次数和移动次数
  输入参数：const char* sortName, void(*func)(int*, int, accord&)
			排序名称，排序算法函数指针
  返 回 值：
  说    明：
***************************************************************************/
void show(const char* sortName, void(*func)(int*, int, accord&))
{
	int* temp = new(nothrow) int[NUM];
	if (temp == NULL)
		return;
	//赋值给temp数组
	for (int i = 0; i < NUM; ++i)
		temp[i] = nums[i];

	accord data;

	//记录开始时间
	auto begin = chrono::steady_clock::now();

	func(temp, NUM, data);
	//记录结束时间
	auto end = chrono::steady_clock::now();
	//计算时间差
	auto Duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
	//花费时间太少，ms无法记录，用μs记录
	bool isMs = true;
	if (Duration == 0)
	{
		isMs = false;
		Duration = chrono::duration_cast<chrono::microseconds>(end - begin).count();
	}

	cout << sortName << "所用时间: " << "\t\t" << Duration;
	if (isMs)
		cout << "毫秒" << endl;
	else
		cout << "微秒" << endl;
	cout << sortName << "交换次数: " << "\t\t" << data.move << endl;
	cout << sortName << "比较次数: " << "\t\t" << data.cmp << endl;


	delete[] temp;
}


int main() {
	cout << "**\t\t排序算法比较    \t\t**" << endl;
	cout << "==================================================" << endl;
	cout << "**\t\t1 --- 冒泡排序    \t\t**" << endl;
	cout << "**\t\t2 --- 选择排序    \t\t**" << endl;
	cout << "**\t\t3 --- 直接插入排序\t\t**" << endl;
	cout << "**\t\t4 --- 希尔排序    \t\t**" << endl;
	cout << "**\t\t5 --- 快排(迭代)    \t\t**" << endl;
	cout << "**\t\t6 --- 快排(递归)    \t\t**" << endl;
	cout << "**\t\t7 --- 堆排序(迭代)    \t\t**" << endl;
	cout << "**\t\t8 --- 堆排序(递归)    \t\t**" << endl;
	cout << "**\t\t9 --- 归并排序    \t\t**" << endl;
	cout << "**\t\t10 --- 计数排序    \t\t**" << endl;
	cout << "**\t\t11 --- 基数LSD排序\t\t**" << endl;
	cout << "**\t\t12 --- 基数MSD排序\t\t**" << endl;
	cout << "**\t\t13 --- 退出程序    \t\t**" << endl;
	cout << "==================================================" << endl;

	cout << "随机数个数超过1e5时不宜使用选项1、2、3" << endl;
	cout << "请输入要产生的随机数的个数(不超过1e8): ";
	while (1) {
		cin >> NUM;
		if (cin.fail() || NUM <= 0 || NUM > 1e8)
		{
			cout << "输入有误，请输入正整数！" << endl;
			cin.clear();
			cin.ignore(65536, '\n');
		}
		else
			break;
	}

	//申请空间
	nums = new(nothrow) int[NUM];
	if (nums == NULL)
		return -1;
	//生成随机数
	randomArray(nums, NUM);
	bool loop = true;
	String op;
	while (loop)
	{
		cout << endl << "请选择排序算法:\t\t\t";
		cin >> op;
		if (op == "1" && NUM < 1e5)
			show("冒泡排序", bubbleSort);
		else if (op == "2" && NUM < 1e5)
			show("选择排序", selectSort);
		else if (op == "3" && NUM < 1e5)
			show("直接插入排序", insertSort);
		else if (op == "4")
			show("希尔排序", shellSort);
		else if (op == "5")
			show("快排(迭代)", quickSort2);
		else if (op == "6")
			show("快排(递归)", quickSort1);
		else if (op == "7")
			show("堆排序(迭代)", heapSort1);
		else if (op == "8")
			show("堆排序(递归)", heapSort2);
		else if (op == "9")
			show("归并排序", mergeSort);
		else if (op == "10")
			show("计数排序", countingSort);
		else if (op == "11")
			show("基数LSD排序", radixSortLSD);
		else if (op == "12")
			show("基数MSD排序", radixSortMSD);
		else if (op == "13")
			loop = 0;
		else
		{
			cout << "输入有误，请重新输入" << endl;
			cin.clear();
			cin.ignore(65536, '\n');
		}
	}
	//释放空间
	delete[] nums;
	return 0;
}
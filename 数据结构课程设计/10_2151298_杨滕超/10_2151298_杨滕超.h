#ifndef _SORT_H
#define _SORT_H
#include <iostream>
#include <assert.h>
#include <climits>
#include <random>
#include <chrono>
using namespace std;

//记录比较次数和交换次数
struct accord {
	long long move;
	long long cmp;
	accord(long long move = 0, long long cmp = 0)
		:move(move), cmp(cmp) {}
};

/***************************************************************************
  函数名称：randomArray
  功    能：向数组中填充随机数
  输入参数：int* nums, int n, 数组首地址，数组大小
  返 回 值：
  说    明：
***************************************************************************/
void randomArray(int* nums, int n)
{
	//生成[0, n]均匀分布的随机数
	uniform_int_distribution<unsigned> u(0, n);
	default_random_engine e;
	for (int i = 0; i < n; ++i)
		nums[i] = u(e);
}


/***************************************************************************
  函数名称：bubbleSort
  功    能：冒泡排序
  输入参数：int* nums, int n, accord& data
			数组首地址，数组大小，记录比较次数与移动次数
  返 回 值：
  说    明：
***************************************************************************/
void bubbleSort(int* nums, int n, accord& data)
{
	//每一轮将原来的nums[i]换到能去的最后的位置
	for (int i = 0; i < n - 1; ++i)
	{
		//有序标记，若检查一遍仍为true说明可以结束
		bool isSorted = true;
		for (int j = 0; j < n - i - 1; ++j)
		{
			if (++data.cmp, nums[j] > nums[j + 1])
			{
				//有元素交换，后面的不是有序
				isSorted = false;
				//交换
				int t = nums[j];
				nums[j] = nums[j + 1];
				nums[j + 1] = t;
				//移动步数增加
				data.move += 3;
			}
		}
		//后面都有序提前结束
		if (isSorted)
			break;
	}
}

/***************************************************************************
  函数名称：selectSort
  功    能：选择排序
  输入参数：int* nums, int n, accord& data
			数组首地址，数组大小，记录比较次数与移动次数
  返 回 值：
  说    明：
***************************************************************************/
void selectSort(int* nums, int n, accord& data)
{
	//在没排序元素中找到最小放到最前面
	for (int i = 0; i < n - 1; ++i)
	{
		//找到最小元素的下标，换到最前面
		int minIndex = i;
		for (int j = i + 1; j < n; ++j)
			if (++data.cmp, nums[minIndex] > nums[j])
			{
				minIndex = j;
			}
		//交换
		int t = nums[minIndex];
		nums[minIndex] = nums[i];
		nums[i] = t;
		//移动步数
		data.move += 3;
	}
}

/***************************************************************************
  函数名称：insertSort
  功    能：插入排序
  输入参数：int* nums, int n, accord& data
			数组首地址，数组大小，记录比较次数与移动次数
  返 回 值：
  说    明：
***************************************************************************/
void insertSort(int* nums, int n, accord& data)
{
	//从当前位置往前扫描，插入正确位置
	for (int i = 1; i < n; ++i)
	{
		int temp = nums[i];
		++data.move;
		int j = i - 1;
		//在判断语句中记录次数
		while (j >= 0 && (++data.cmp, temp < nums[j]))
		{
			nums[j + 1] = nums[j];//元素往后移，给temp腾出位置
			++data.move;
			--j;
		}
		nums[j + 1] = temp;
		//移动步数
		++data.move;
	}
}

/***************************************************************************
  函数名称：shellSort
  功    能：希尔排序
  输入参数：int* nums, int n, accord& data
			数组首地址，数组大小，记录比较次数与移动次数
  返 回 值：
  说    明：
***************************************************************************/
void shellSort(int* nums, int n, accord& data)
{
	//有间隔的插入排序，间隔step不断缩小，大致有序->有序
	int i, temp;
	for (int step = n >> 2; step > 0; step >>= 2)
		for (int pos = step; pos < n; ++pos)
		{
			temp = nums[pos];//记录要变位置的值
			++data.move;
			//插入排序
			for (i = pos - step; i >= 0 && (++data.cmp, nums[i] > temp); i -= step)
			{
				nums[i + step] = nums[i];//前面的元素往后移，给temp腾出位置
				//记录步数
				++data.move;
			}
			nums[i + step] = temp;//找到插入位置
			//记录步数
			++data.move;
		}
}

/***************************************************************************
  函数名称：insertSort
  功    能：快排需要的插入函数
  输入参数：int* nums, int beg, int end, accord& data
			数组首地址，数组排序的范围[beg, end]，记录比较次数与移动次数
  返 回 值：
  说    明：
***************************************************************************/
void insertSort(int* nums, int beg, int end, accord& data)
{
	//计算数组大小
	int n = end - beg + 1;
	//从当前位置往前扫描，插入正确位置
	for (int i = beg + 1; i <= end; ++i)
	{
		int temp = nums[i];
		++data.move;
		int j = i - 1;
		//在判断语句中记录次数
		while (j >= beg && (++data.cmp, temp < nums[j]))
		{
			nums[j + 1] = nums[j];//元素往后移，给temp腾出位置
			++data.move;
			--j;
		}
		nums[j + 1] = temp;
		//移动步数
		++data.move;
	}
}

//beg为第一个下标，end为最后一个的下标，[beg, end]
/***************************************************************************
  函数名称：_quickSort
  功    能：快速排序的辅助函数
  输入参数：int* nums, int beg, int end, int n, accord& data
			数组首地址，排序的范围，数组大小，记录比较次数与移动次数
  返 回 值：
  说    明：数据量较小的时候采用插入排序优化
***************************************************************************/
void _quickSort1(int* nums, int beg, int end, int n, accord& data)
{
	if (beg >= end)//递归结束条件
		return;
	//数据量较小时采用插入排序
	if (end - beg + 1 <= 20)
	{
		insertSort(nums, beg, end, data);
		return;
	}
	//取左边第一个为基准
	int pivot = nums[beg];
	//两个指针左右检查比pivot小的放左边，否则右边
	int left = beg, right = end;
	while (left < right)
	{
		//不超范围，不比pivot小的一直移动右边指针
		while (left < right && (++data.cmp, nums[right] >= pivot))
			--right;
		//与左边指针交换位置值
		nums[left] = nums[right];
		//移动步数
		++data.move;
		//不超范围，不必pivot大的一直移动左边指针
		while (left < right && (++data.cmp, nums[left] <= pivot))
			++left;
		//交换位置
		nums[right] = nums[left];
		//移动步数
		++data.move;
	}
	//出循环left == right，找到最开始pivot的位置
	nums[left] = pivot;
	//移动步数
	++data.move;
	//分治为左右两边
	_quickSort1(nums, beg, left - 1, n, data);
	_quickSort1(nums, left + 1, end, n, data);
}
/***************************************************************************
  函数名称：quickSort1
  功    能：快速排序递归算法
  输入参数：int* nums, int n, accord& data
			数组首地址，数组大小，记录比较次数与移动次数
  返 回 值：
  说    明：
***************************************************************************/
void quickSort1(int* nums, int n, accord& data)
{
	//进入快排递归函数
	_quickSort1(nums, 0, n - 1, n, data);
}
//二元结构体存储数组范围信息
struct RANGE {
	int beg, end;
	//构造函数
	RANGE(const int beg = 0, const int end = 0)
		:beg(beg), end(end) {}
};

/***************************************************************************
  函数名称：quickSort2
  功    能：快速排序非递归算法
  输入参数：int* nums, int n, accord& data
			数组首地址，数组大小，记录比较次数与移动次数
  返 回 值：
  说    明：利用栈存储要排序的范围，由此进行递归展开
***************************************************************************/
void quickSort2(int* nums, int n, accord& data)
{
	//判断数组长度是否合法，申请空间时候需要
	if (n <= 0)
		return;
	RANGE* stk = new(nothrow) RANGE[n];
	//保证申请到空间了才能继续运行
	assert(stk != NULL);
	//栈顶指针
	int top = 0;
	//最大范围入栈
	stk[top++] = RANGE(0, n - 1);
	//辅助变量
	int pivot = -1, left = -1, right = -1;
	while (top)
	{
		RANGE range = stk[--top];
		//无需排序
		if (range.beg >= range.end)
			continue;

		//取左边第一个为基准
		pivot = nums[range.beg];
		//两个指针左右检查比pivot小的放左边，否则右边
		left = range.beg, right = range.end;

		while (left < right)
		{
			//不超范围，不比pivot小的一直移动右边指针
			while (left < right && (++data.cmp, nums[right] >= pivot))
				--right;
			//与左边指针交换位置值
			nums[left] = nums[right];
			//移动步数
			++data.move;
			//不超范围，不必pivot大的一直移动左边指针
			while (left < right && (++data.cmp, nums[left] <= pivot))
				++left;
			//交换位置
			nums[right] = nums[left];
			//移动步数
			++data.move;
		}
		//出循环left == right，找到最开始pivot的位置
		nums[left] = pivot;
		//移动步数
		++data.move;

		//入栈
		stk[top++] = RANGE(range.beg, left - 1);
		stk[top++] = RANGE(left + 1, range.end);

	}
	//释放空间
	delete[] stk;
}

/***************************************************************************
  函数名称：countingSort
  功    能：计数排序
  输入参数：int* nums, int n, accord& data
			数组首地址，数组大小，记录比较次数与移动次数
  返 回 值：
  说    明：
***************************************************************************/
void countingSort(int* nums, int n, accord& data)
{
	//额外开辟数组空间记录值为i的元素出现的次数
	//先找到最值两个边界
	int Max = INT_MIN, Min = INT_MAX;
	for (int i = 0; i < n; ++i)
	{
		if (Max < nums[i])
			Max = nums[i];
		if (Min > nums[i])
			Min = nums[i];
	}
	int* temp = new int[Max - Min + 1];
	assert(temp != NULL);

	//申请空间失败
	if (temp == NULL)
		return;
	//初始化
	for (int i = 0; i < Max - Min + 1; ++i)
		temp[i] = 0;
	//记录出现次数
	for (int i = 0; i < n; ++i)
		++temp[nums[i] - Min];

	for (int i = 0, j = 0; i < Max - Min + 1; )
	{
		if (temp[i])//里面还有元素
		{
			nums[j++] = i + Min;//元素的值
			++data.move;
			--temp[i];
		}
		else//没有元素了
			++i;
	}
	delete[] temp;
}

/***************************************************************************
  函数名称：mergeSort
  功    能：归并排序
  输入参数：int* nums, int n, accord& data
			数组首地址，数组大小，记录比较次数与移动次数
  返 回 值：
  说    明：
***************************************************************************/
void mergeSort(int* nums, int n, accord& data)//自下而上迭代方式实现
{
	//辅助数组，其中a是更新前的数组，b是更新后的数组
	int* a = nums;
	int* b = new int[n];
	//申请空间不成功
	assert(b != NULL);
	//从下至上，区间不断扩大
	for (int seg = 1; seg < n; seg <<= 1)
	{
		for (int start = 0; start < n; start += seg + seg)//一次比较两个seg
		{
			int start1 = start, start2 = min(start + seg, n);
			int end1 = start2, end2 = min(start + seg + seg, n);
			int index = start1;
			while (start1 < end1 && start2 < end2)//选到谁谁就指针往后移
			{
				b[index++] = a[start1] < a[start2] ? a[start1++] : a[start2++];
				++data.cmp;
				++data.move;
			}
			//比完了剩下的直接放到后面
			while (start1 < end1)
				b[index++] = a[start1++], ++data.move;
			while (start2 < end2)
				b[index++] = a[start2++], ++data.move;
		}
		//保持a是更新前的数组，b是更新后的数组
		int* t = a;
		a = b;
		b = t;
	}
	//如果没有换回来（首地址），此时a是申请空间的那个，b是nums
	if (a != nums)
	{
		for (int i = 0; i < n; ++i)//最终的答案数组赋值给nums
			b[i] = a[i];
		b = a;//申请空间的给b
	}
	//如果换回来了就不用赋值了
	//释放申请的空间
	delete[] b;
}

/***************************************************************************
  函数名称：heapify1
  功    能：堆排序辅助函数，非递归算法
  输入参数：int* nums, int start, int end, accord& data
			数组首地址，数组范围，记录比较次数与移动次数
  返 回 值：
  说    明：
***************************************************************************/
void heapify1(int* nums, int start, int end, accord& data)//[beg, end]
{
	int dad = start, son = 2 * dad + 1;
	while (son <= end)
	{
		//取大的那个儿子
		if ((son + 1) <= end && (++data.cmp, nums[son] < nums[son + 1]))
			++son;
		if (++data.cmp, nums[dad] > nums[son])//dad比son大，直接结束，因为要的是top最大
			return;
		//小的nums[dad]下沉到较大的子结点的位置
		int t = nums[dad];
		nums[dad] = nums[son];
		nums[son] = t;
		//记录步数
		data.move += 3;

		dad = son;//迭代到更大的子结点
		son = dad * 2 + 1;
	}
}
/***************************************************************************
  函数名称：heapify2
  功    能：堆排序辅助函数，递归算法
  输入参数：int* nums, int start, int end, accord& data
			数组首地址，数组范围，记录比较次数与移动次数
  返 回 值：
  说    明：
***************************************************************************/
void heapify2(int* nums, int start, int end, accord& data)
{
	int dad = start, son = 2 * dad + 1;
	if (son > end)//递归结束条件
		return;
	//取较大儿子
	if (son + 1 <= end && (++data.cmp, nums[son] < nums[son + 1]))
		++son;
	//dad已经比son大了就不用下沉了
	if (++data.cmp, nums[dad] > nums[son])
		return;
	int t = nums[dad];
	nums[dad] = nums[son];
	nums[son] = t;
	//记录步数
	data.move += 3;
	//进入递归函数，以son作为下一个的start
	heapify2(nums, son, end, data);
}
/***************************************************************************
  函数名称：heapSort1
  功    能：堆排序，非递归算法
  输入参数：int* nums, int n, accord& data
			数组首地址，数组大小，记录比较次数与移动次数
  返 回 值：
  说    明：
***************************************************************************/
void heapSort1(int* nums, int n, accord& data)
{
	//初始化堆，从最后一个非叶子结点往前
	for (int i = (n - 1) / 2; i >= 0; --i)
		heapify1(nums, i, n - 1, data);//下标从[i, n - 1]
	//堆排序，将已经排好的堆 top 放到最后（相当于出堆）
	for (int i = n - 1; i > 0; --i)//从后往前放top
	{
		int t = nums[0];
		nums[0] = nums[i];
		nums[i] = t;
		data.move += 3;

		heapify1(nums, 0, i - 1, data);//放到最后了，重新堆化
	}
}
/***************************************************************************
  函数名称：heapSort2
  功    能：堆排序，递归算法
  输入参数：int* nums, int n, accord& data
			数组首地址，数组大小，记录比较次数与移动次数
  返 回 值：
  说    明：
***************************************************************************/
void heapSort2(int* nums, int n, accord& data)
{
	//初始化堆，从中间往前
	for (int i = (n - 1) / 2; i >= 0; --i)
		heapify2(nums, i, n - 1, data);//下标从[i, n - 1]
	//堆排序，将已经排好的堆 top 放到最后（相当于出堆）
	for (int i = n - 1; i > 0; --i)//从后往前放top
	{
		int t = nums[0];
		nums[0] = nums[i];
		nums[i] = t;
		//记录步数
		data.move += 3;

		heapify2(nums, 0, i - 1, data);//放到最后了，重新堆化
	}
}

/***************************************************************************
  函数名称：bucket
  功    能：LSD算法辅助函数
  输入参数：int* nums, int n, int base, accord& data
			数组首地址，数组大小，当前位数，记录比较次数与移动次数
  返 回 值：
  说    明：
***************************************************************************/
void bucket(int* nums, int n, int base, accord& data)
{
	const int BUCKETNUM = 10;
	int* bucket = new int[BUCKETNUM];
	assert(bucket != NULL);
	int* temp = new int[n];
	assert(temp != NULL);
	//桶的初始化
	for (int i = 0; i < BUCKETNUM; ++i)
		bucket[i] = 0;

	//记录每位数字对应的桶
	for (int i = 0; i < n; ++i)
		++bucket[(nums[i] / base) % 10];

	//bucket[i]表示i前面元素个数
	for (int i = 1; i < BUCKETNUM; ++i)
		bucket[i] += bucket[i - 1];
	//从后往前将元素放入temp，得到的就是按某位数字排好的
	for (int i = n - 1; i >= 0; --i)
	{
		int index = (nums[i] / base) % 10;
		temp[bucket[index] - 1] = nums[i];//因为桶里面记录的个数，-1转换为下标
		--bucket[index];//用掉一个元素减去一个
		++data.move;
	}
	//将temp中按某位数字排好的元素放回nums
	for (int i = 0; i < n; ++i)
		nums[i] = temp[i];
	data.move += n;

	//释放申请的动态空间
	delete[] temp;
	delete[] bucket;
}
/***************************************************************************
  函数名称：radixSortLSD
  功    能：基数排序LSD
  输入参数：int* nums, int n, accord& data
			数组首地址，数组大小，记录比较次数与移动次数
  返 回 值：
  说    明：适用于位数较少的
***************************************************************************/
void radixSortLSD(int* nums, int n, accord& data)
{
	int Max = INT_MIN;
	//获得最大值
	for (int i = 0; i < n; ++i)
		if (++data.cmp && nums[i] > Max)
			Max = nums[i];
	//base从个位增大到元素中的最大位数
	for (int base = 1; Max / base > 0; base *= 10)
		bucket(nums, n, base, data);
}

/***************************************************************************
  函数名称：MSDhelper
  功    能：基数排序MSD的辅助函数
  输入参数：int* nums, int beg, int end, int base, accord& data
			数组首地址，数组范围，当前位数，记录比较次数与移动次数
  返 回 值：
  说    明：适用于位数较多的
***************************************************************************/
void MSDhelper(int* nums, int beg, int end, int base, accord& data)
{
	//桶中元素不大于1个
	if (beg + 1 >= end)
		return;
	//基数不合法
	if (base <= 0)
		return;
	const int BUCKETNUM = 10;
	int Size = end - beg + 1;
	//申请空间
	int* bucket = new int[BUCKETNUM];
	int* temp = new int[Size];
	assert(bucket != NULL && temp != NULL);

	//bucket数组初始化
	for (int i = 0; i < BUCKETNUM; ++i)
		bucket[i] = 0;

	//记录base位的个数
	for (int i = beg; i <= end; ++i)
		++bucket[(nums[i] / base) % 10];

	//求bucket前缀和以得到目标下标
	for (int i = 1; i < BUCKETNUM; ++i)
		bucket[i] += bucket[i - 1];

	//放入temp中的目标位置
	for (int i = beg; i <= end; ++i)
	{
		int index = (nums[i] / base) % 10;
		temp[bucket[index] - 1] = nums[i];
		--bucket[index];
		++data.move;
	}

	//temp数组中排好的序列放回nums数组
	for (int i = beg; i <= end; ++i)
		nums[i] = temp[i - beg];
	data.move += Size;

	//此时bucket[i]存放base位为i的，在temp数组中的第一个位置
	//进入递归函数
	for (int i = 0; i < BUCKETNUM - 1; ++i)
		MSDhelper(nums, beg + bucket[i], beg + bucket[i + 1] - 1, base / 10, data);
	//最后一部分的范围上界为end
	MSDhelper(nums, beg + bucket[BUCKETNUM - 1], end, base / 10, data);


	//释放空间
	delete[] temp;
	delete[] bucket;
}
/***************************************************************************
  函数名称：radixSortMSD
  功    能：基数排序MSD
  输入参数：int* nums, int n, accord& data
			数组首地址，数组大小，记录比较次数与移动次数
  返 回 值：
  说    明：适用于位数较多的
***************************************************************************/
void radixSortMSD(int* nums, int n, accord& data)
{
	int Max = INT_MIN;
	//获得最大值
	for (int i = 0; i < n; ++i)
		if (++data.cmp, nums[i] > Max)
			Max = nums[i];
	//获得最大位数
	int base = 1;
	while (Max / base > 10)
		base *= 10;
	MSDhelper(nums, 0, n - 1, base, data);
}


const int defaultSizeString = 50;
class String {
private:
	int Size;//指向尾零的位置，初始化时候注意SIze = 1
	int capacity;
	char* data;
	void expand();
	void getNext(const char* str, int* next, int len);
public:
	//构造函数
	String();
	String(String& str);
	String(const char* str);
	String(const char* str, int size);

	//析构函数
	~String();
	//字符串长度
	int length()const {
		return Size - 1;
	}
	int strLen(const char* str);

	//重载=
	String& operator=(const String& str);
	String& operator=(const char* str);
	String& operator=(const char& ch);

	//重载<<
	friend ostream& operator<<(ostream& out, const String& str) {
		out << str.data;
		return out;
	}
	//重载>>
	friend istream& operator>>(istream& in, String& str) {
		//万一输入太多了怎么办
		in >> str.data;
		str.Size = str.strLen(str.data) + 1;
		return in;
	}
	//重载比较
	friend int strCmp(const String& str1, const String& str2)
	{
		int i = 0;
		while (str1.data[i] && str2.data[i])
		{
			if (str1.data[i] != str2.data[i])
				return str1.data[i] - str2.data[i];
			else
				++i;
		}

		if (str1.data[i])
			return str1.data[i];
		else
			return 0 - str2.data[i];
	}
	friend bool operator<(const String& str1, const String& str2) {
		return strCmp(str1, str2) < 0;
	}
	friend bool operator>(const String& str1, const String& str2) {
		return strCmp(str1, str2) > 0;
	}
	friend bool operator<=(const String& str1, const String& str2) {
		return strCmp(str1, str2) <= 0;
	}
	friend bool operator>=(const String& str1, const String& str2) {
		return strCmp(str1, str2) >= 0;
	}
	//重载[]
	inline char& operator[](const int index) {
		return data[index];
	}
	inline char& operator[](const size_t index) {
		return data[index];
	}
	//重载==
	bool operator==(const String& str);
	bool operator==(const char* str);
	//重载+
	String operator+(const String& str);
	String operator+(const char* str);
	//重载+=
	String& operator+=(const String& str);
	String& operator+=(const char* str);
	String& operator+=(const char ch);
	//返回字符串类型
	char* c_str() {
		return data;
	}
	char* c_str() const {
		return data;
	}
	//模式匹配
	int find(const char* str);
	int find(String& str);
	//删除所有的某个字符
	void erase(char ch);
	//翻转
	void reverse();
	//清空
	void clear();
	//删掉最后一个
	void pop_back() {
		//空的字符串
		if (Size == 1)
			return;

		--Size;
		data[Size - 1] = '\0';
	}
	//最后一个字符
	char back() const {
		if (Size <= 1)
			return '\0';
		return data[Size - 2];
	}
};
String::String()
{
	Size = 1;
	capacity = defaultSizeString;
	data = new char[capacity];
	data[0] = '\0';
}
String::String(String& str)
{
	Size = str.Size;
	capacity = (Size / defaultSizeString + 1) * defaultSizeString;
	data = new char[capacity];
	for (int i = 0; i < Size; ++i)
		data[i] = str.data[i];
}
String::String(const char* str)
{
	int size = 0;
	while (str[size] != '\0')
		++size;
	++size;//最后一个尾零

	Size = size;

	capacity = (Size / defaultSizeString + 1) * defaultSizeString;
	data = new char[capacity];
	for (int i = 0; i < Size; ++i)
		data[i] = str[i];

}
String::String(const char* str, int size)
{
	Size = size;
	capacity = (Size / defaultSizeString + 1) * defaultSizeString;
	data = new char[capacity];

	for (int i = 0; i < Size; ++i)
		data[i] = str[i];
}

String::~String() {
	delete[] data;
}
int String::strLen(const char* str)
{
	int size = 0;
	while (str[size] != '\0')
		++size;
	return size;
}

void String::expand()
{
	capacity += defaultSizeString;
	char* newData = new char[capacity];
	for (int i = 0; i < Size && Size < capacity; ++i)
		newData[i] = data[i];
	delete[] data;
	data = newData;
}
String& String::operator=(const String& str)
{
	Size = str.Size;
	capacity = (Size / defaultSizeString + 1) * defaultSizeString;
	delete[] data;
	data = new char[capacity];
	for (int i = 0; i < Size; ++i)
		data[i] = str.data[i];
	return *this;
}
String& String::operator=(const char* str)
{
	int size = 0;
	while (str[size] != '\0')
		++size;
	++size;//尾零

	Size = size;
	capacity = (Size / defaultSizeString + 1) * defaultSizeString;
	delete[] data;
	data = new char[capacity];
	for (int i = 0; i < Size; ++i)
		data[i] = str[i];
	return *this;
}
String& String::operator=(const char& ch)
{
	Size = 2;
	capacity = (Size / defaultSizeString + 1) * defaultSizeString;
	delete[] data;
	data = new char[capacity];
	data[0] = ch;
	data[1] = '\0';
	return *this;
}
bool String::operator==(const String& str)
{
	if (Size != str.Size)
		return false;
	for (int i = 0; i < Size; ++i)
		if (data[i] != str.data[i])
			return false;
	return true;
}
bool String::operator==(const char* str)
{
	int size = 0;
	while (str[size] != '\0')
		++size;
	++size;//尾零

	if (Size != size)
		return false;

	for (int i = 0; i < Size; ++i)
		if (data[i] != str[i])
			return false;
	return true;
}

String String::operator+(const String& str)
{
	String temp(str.data, str.Size + Size);

	//包括str的尾零
	//注意data[Size]是尾零
	for (int i = 0; i <= str.Size; ++i)
		temp.data[Size + i - 1] = str.data[i];

	return temp;
}
String String::operator+(const char* str)
{
	int size = 0;
	while (str[size] != '\0')
		++size;
	++size;
	String temp(str, Size + size);


	//包括str的尾零
	//注意data[Size]是尾零
	for (int i = 0; i <= size; ++i)
		temp.data[Size + i - 1] = str[i];

	return temp;
}
String& String::operator+=(const String& str)
{
	if (Size + str.Size > capacity)
	{
		capacity = ((str.Size + Size) / defaultSizeString + 1) * defaultSizeString;
		char* newData = new char[capacity];
		for (int i = 0; i < Size; ++i)
			newData[i] = data[i];
		delete[] data;
		data = newData;
	}
	//包括str的尾零
	//注意data[Size - 1]是尾零
	for (int i = 0; i < str.Size; ++i)
		data[Size + i - 1] = str.data[i];

	Size += str.Size - 1;
	return *this;
}
String& String::operator+=(const char* str)
{
	int size = 0;
	while (str[size] != '\0')
		++size;
	++size;

	if (Size + size > capacity)
	{
		capacity = ((size + Size) / defaultSizeString + 1) * defaultSizeString;
		char* newData = new char[capacity];
		for (int i = 0; i < Size; ++i)
			newData[i] = data[i];
		delete[] data;
		data = newData;
	}
	//包括str的尾零
	//注意data[Size - 1]是尾零
	for (int i = 0; i < size; ++i)
		data[Size + i - 1] = str[i];

	Size += size - 1;
	return *this;
}
String& String::operator+=(const char ch)
{
	if (Size + 1 > capacity)
	{
		capacity = ((1 + Size) / defaultSizeString + 1) * defaultSizeString;
		char* newData = new char[capacity];
		for (int i = 0; i < Size; ++i)
			newData[i] = data[i];
		delete[] data;
		data = newData;
	}
	//包括str的尾零
	//注意data[Size - 1]是尾零
	data[Size - 1] = ch;
	data[Size] = '\0';
	++Size;
	return *this;
}

void String::getNext(const char* str, int* next, int len)
{
	next[0] = -1;
	next[1] = 0;
	int i = 2;//从2开始
	int cn = 0;//cn表示next[i - 1]的信息

	while (i < len)
	{
		if (str[i - 1] == str[cn])//可以继续相等
			next[i++] = ++cn;
		else if (cn > 0)//不可以继续相等
			cn = next[cn];
		else
			next[i++] = 0;
	}
}
int String::find(String& str)
{

	if (Size < str.Size || Size == 1 || str.Size == 1)
		return -1;
	int i1 = 0, i2 = 0, len1 = Size - 1, len2 = str.Size - 1;

	int* next = new int[len2 + 1];
	getNext(str.data, next, len2);

	while (i1 < len1 && i2 < len2)
	{
		if (data[i1] == str.data[i2])
			++i1, ++i2;
		else if (i2 != 0)
			i2 = next[i2];
		else
			++i1;
	}
	delete[] next;
	return i2 == len2 ? i1 - i2 : -1;
}
int String::find(const char* str)
{
	int len2 = 0, len1 = Size - 1;
	while (str[len2] != '\0')
		++len2;

	if (len1 < len2 || len1 == 0 || len2 == 0)
		return -1;

	int* next = new int[len2 + 1];
	getNext(str, next, len2);

	int i1 = 0, i2 = 0;
	while (i1 < len1 && i2 < len2)
	{
		if (data[i1] == str[i2])
			++i1, ++i2;
		else if (i2 != 0)
			i2 = next[i2];
		else
			++i1;
	}
	delete[] next;
	return i2 == len2 ? i1 - i2 : -1;
}
void String::erase(char ch)
{
	int i = 0, k = 0;
	while (i < Size)
	{
		if (ch != data[i])//data[i]不等于了才赋值并且新数组的指针k++
			data[k++] = data[i];
		++i;
	}
	Size -= i - k;
	cout << "size:" << Size << endl;
}
void String::reverse()
{
	int len = Size - 1;
	for (int i = 0; i < len / 2; ++i)
	{
		char t = data[i];
		data[i] = data[len - i - 1];
		data[len - i - 1] = t;
	}
}
void String::clear()
{
	//删掉原来的
	delete[] data;
	//重新设置
	Size = 1;
	capacity = defaultSizeString;
	data = new char[capacity];
	data[0] = '\0';
}


#endif // !_SORT_H 

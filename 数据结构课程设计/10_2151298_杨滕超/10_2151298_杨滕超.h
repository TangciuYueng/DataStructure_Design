#ifndef _SORT_H
#define _SORT_H
#include <iostream>
#include <assert.h>
#include <climits>
#include <random>
#include <chrono>
using namespace std;

//��¼�Ƚϴ����ͽ�������
struct accord {
	long long move;
	long long cmp;
	accord(long long move = 0, long long cmp = 0)
		:move(move), cmp(cmp) {}
};

/***************************************************************************
  �������ƣ�randomArray
  ��    �ܣ�����������������
  ���������int* nums, int n, �����׵�ַ�������С
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void randomArray(int* nums, int n)
{
	//����[0, n]���ȷֲ��������
	uniform_int_distribution<unsigned> u(0, n);
	default_random_engine e;
	for (int i = 0; i < n; ++i)
		nums[i] = u(e);
}


/***************************************************************************
  �������ƣ�bubbleSort
  ��    �ܣ�ð������
  ���������int* nums, int n, accord& data
			�����׵�ַ�������С����¼�Ƚϴ������ƶ�����
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void bubbleSort(int* nums, int n, accord& data)
{
	//ÿһ�ֽ�ԭ����nums[i]������ȥ������λ��
	for (int i = 0; i < n - 1; ++i)
	{
		//�����ǣ������һ����Ϊtrue˵�����Խ���
		bool isSorted = true;
		for (int j = 0; j < n - i - 1; ++j)
		{
			if (++data.cmp, nums[j] > nums[j + 1])
			{
				//��Ԫ�ؽ���������Ĳ�������
				isSorted = false;
				//����
				int t = nums[j];
				nums[j] = nums[j + 1];
				nums[j + 1] = t;
				//�ƶ���������
				data.move += 3;
			}
		}
		//���涼������ǰ����
		if (isSorted)
			break;
	}
}

/***************************************************************************
  �������ƣ�selectSort
  ��    �ܣ�ѡ������
  ���������int* nums, int n, accord& data
			�����׵�ַ�������С����¼�Ƚϴ������ƶ�����
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void selectSort(int* nums, int n, accord& data)
{
	//��û����Ԫ�����ҵ���С�ŵ���ǰ��
	for (int i = 0; i < n - 1; ++i)
	{
		//�ҵ���СԪ�ص��±꣬������ǰ��
		int minIndex = i;
		for (int j = i + 1; j < n; ++j)
			if (++data.cmp, nums[minIndex] > nums[j])
			{
				minIndex = j;
			}
		//����
		int t = nums[minIndex];
		nums[minIndex] = nums[i];
		nums[i] = t;
		//�ƶ�����
		data.move += 3;
	}
}

/***************************************************************************
  �������ƣ�insertSort
  ��    �ܣ���������
  ���������int* nums, int n, accord& data
			�����׵�ַ�������С����¼�Ƚϴ������ƶ�����
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void insertSort(int* nums, int n, accord& data)
{
	//�ӵ�ǰλ����ǰɨ�裬������ȷλ��
	for (int i = 1; i < n; ++i)
	{
		int temp = nums[i];
		++data.move;
		int j = i - 1;
		//���ж�����м�¼����
		while (j >= 0 && (++data.cmp, temp < nums[j]))
		{
			nums[j + 1] = nums[j];//Ԫ�������ƣ���temp�ڳ�λ��
			++data.move;
			--j;
		}
		nums[j + 1] = temp;
		//�ƶ�����
		++data.move;
	}
}

/***************************************************************************
  �������ƣ�shellSort
  ��    �ܣ�ϣ������
  ���������int* nums, int n, accord& data
			�����׵�ַ�������С����¼�Ƚϴ������ƶ�����
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void shellSort(int* nums, int n, accord& data)
{
	//�м���Ĳ������򣬼��step������С����������->����
	int i, temp;
	for (int step = n >> 2; step > 0; step >>= 2)
		for (int pos = step; pos < n; ++pos)
		{
			temp = nums[pos];//��¼Ҫ��λ�õ�ֵ
			++data.move;
			//��������
			for (i = pos - step; i >= 0 && (++data.cmp, nums[i] > temp); i -= step)
			{
				nums[i + step] = nums[i];//ǰ���Ԫ�������ƣ���temp�ڳ�λ��
				//��¼����
				++data.move;
			}
			nums[i + step] = temp;//�ҵ�����λ��
			//��¼����
			++data.move;
		}
}

/***************************************************************************
  �������ƣ�insertSort
  ��    �ܣ�������Ҫ�Ĳ��뺯��
  ���������int* nums, int beg, int end, accord& data
			�����׵�ַ����������ķ�Χ[beg, end]����¼�Ƚϴ������ƶ�����
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void insertSort(int* nums, int beg, int end, accord& data)
{
	//���������С
	int n = end - beg + 1;
	//�ӵ�ǰλ����ǰɨ�裬������ȷλ��
	for (int i = beg + 1; i <= end; ++i)
	{
		int temp = nums[i];
		++data.move;
		int j = i - 1;
		//���ж�����м�¼����
		while (j >= beg && (++data.cmp, temp < nums[j]))
		{
			nums[j + 1] = nums[j];//Ԫ�������ƣ���temp�ڳ�λ��
			++data.move;
			--j;
		}
		nums[j + 1] = temp;
		//�ƶ�����
		++data.move;
	}
}

//begΪ��һ���±꣬endΪ���һ�����±꣬[beg, end]
/***************************************************************************
  �������ƣ�_quickSort
  ��    �ܣ���������ĸ�������
  ���������int* nums, int beg, int end, int n, accord& data
			�����׵�ַ������ķ�Χ�������С����¼�Ƚϴ������ƶ�����
  �� �� ֵ��
  ˵    ������������С��ʱ����ò��������Ż�
***************************************************************************/
void _quickSort1(int* nums, int beg, int end, int n, accord& data)
{
	if (beg >= end)//�ݹ��������
		return;
	//��������Сʱ���ò�������
	if (end - beg + 1 <= 20)
	{
		insertSort(nums, beg, end, data);
		return;
	}
	//ȡ��ߵ�һ��Ϊ��׼
	int pivot = nums[beg];
	//����ָ�����Ҽ���pivotС�ķ���ߣ������ұ�
	int left = beg, right = end;
	while (left < right)
	{
		//������Χ������pivotС��һֱ�ƶ��ұ�ָ��
		while (left < right && (++data.cmp, nums[right] >= pivot))
			--right;
		//�����ָ�뽻��λ��ֵ
		nums[left] = nums[right];
		//�ƶ�����
		++data.move;
		//������Χ������pivot���һֱ�ƶ����ָ��
		while (left < right && (++data.cmp, nums[left] <= pivot))
			++left;
		//����λ��
		nums[right] = nums[left];
		//�ƶ�����
		++data.move;
	}
	//��ѭ��left == right���ҵ��ʼpivot��λ��
	nums[left] = pivot;
	//�ƶ�����
	++data.move;
	//����Ϊ��������
	_quickSort1(nums, beg, left - 1, n, data);
	_quickSort1(nums, left + 1, end, n, data);
}
/***************************************************************************
  �������ƣ�quickSort1
  ��    �ܣ���������ݹ��㷨
  ���������int* nums, int n, accord& data
			�����׵�ַ�������С����¼�Ƚϴ������ƶ�����
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void quickSort1(int* nums, int n, accord& data)
{
	//������ŵݹ麯��
	_quickSort1(nums, 0, n - 1, n, data);
}
//��Ԫ�ṹ��洢���鷶Χ��Ϣ
struct RANGE {
	int beg, end;
	//���캯��
	RANGE(const int beg = 0, const int end = 0)
		:beg(beg), end(end) {}
};

/***************************************************************************
  �������ƣ�quickSort2
  ��    �ܣ���������ǵݹ��㷨
  ���������int* nums, int n, accord& data
			�����׵�ַ�������С����¼�Ƚϴ������ƶ�����
  �� �� ֵ��
  ˵    ��������ջ�洢Ҫ����ķ�Χ���ɴ˽��еݹ�չ��
***************************************************************************/
void quickSort2(int* nums, int n, accord& data)
{
	//�ж����鳤���Ƿ�Ϸ�������ռ�ʱ����Ҫ
	if (n <= 0)
		return;
	RANGE* stk = new(nothrow) RANGE[n];
	//��֤���뵽�ռ��˲��ܼ�������
	assert(stk != NULL);
	//ջ��ָ��
	int top = 0;
	//���Χ��ջ
	stk[top++] = RANGE(0, n - 1);
	//��������
	int pivot = -1, left = -1, right = -1;
	while (top)
	{
		RANGE range = stk[--top];
		//��������
		if (range.beg >= range.end)
			continue;

		//ȡ��ߵ�һ��Ϊ��׼
		pivot = nums[range.beg];
		//����ָ�����Ҽ���pivotС�ķ���ߣ������ұ�
		left = range.beg, right = range.end;

		while (left < right)
		{
			//������Χ������pivotС��һֱ�ƶ��ұ�ָ��
			while (left < right && (++data.cmp, nums[right] >= pivot))
				--right;
			//�����ָ�뽻��λ��ֵ
			nums[left] = nums[right];
			//�ƶ�����
			++data.move;
			//������Χ������pivot���һֱ�ƶ����ָ��
			while (left < right && (++data.cmp, nums[left] <= pivot))
				++left;
			//����λ��
			nums[right] = nums[left];
			//�ƶ�����
			++data.move;
		}
		//��ѭ��left == right���ҵ��ʼpivot��λ��
		nums[left] = pivot;
		//�ƶ�����
		++data.move;

		//��ջ
		stk[top++] = RANGE(range.beg, left - 1);
		stk[top++] = RANGE(left + 1, range.end);

	}
	//�ͷſռ�
	delete[] stk;
}

/***************************************************************************
  �������ƣ�countingSort
  ��    �ܣ���������
  ���������int* nums, int n, accord& data
			�����׵�ַ�������С����¼�Ƚϴ������ƶ�����
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void countingSort(int* nums, int n, accord& data)
{
	//���⿪������ռ��¼ֵΪi��Ԫ�س��ֵĴ���
	//���ҵ���ֵ�����߽�
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

	//����ռ�ʧ��
	if (temp == NULL)
		return;
	//��ʼ��
	for (int i = 0; i < Max - Min + 1; ++i)
		temp[i] = 0;
	//��¼���ִ���
	for (int i = 0; i < n; ++i)
		++temp[nums[i] - Min];

	for (int i = 0, j = 0; i < Max - Min + 1; )
	{
		if (temp[i])//���滹��Ԫ��
		{
			nums[j++] = i + Min;//Ԫ�ص�ֵ
			++data.move;
			--temp[i];
		}
		else//û��Ԫ����
			++i;
	}
	delete[] temp;
}

/***************************************************************************
  �������ƣ�mergeSort
  ��    �ܣ��鲢����
  ���������int* nums, int n, accord& data
			�����׵�ַ�������С����¼�Ƚϴ������ƶ�����
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void mergeSort(int* nums, int n, accord& data)//���¶��ϵ�����ʽʵ��
{
	//�������飬����a�Ǹ���ǰ�����飬b�Ǹ��º������
	int* a = nums;
	int* b = new int[n];
	//����ռ䲻�ɹ�
	assert(b != NULL);
	//�������ϣ����䲻������
	for (int seg = 1; seg < n; seg <<= 1)
	{
		for (int start = 0; start < n; start += seg + seg)//һ�αȽ�����seg
		{
			int start1 = start, start2 = min(start + seg, n);
			int end1 = start2, end2 = min(start + seg + seg, n);
			int index = start1;
			while (start1 < end1 && start2 < end2)//ѡ��˭˭��ָ��������
			{
				b[index++] = a[start1] < a[start2] ? a[start1++] : a[start2++];
				++data.cmp;
				++data.move;
			}
			//������ʣ�µ�ֱ�ӷŵ�����
			while (start1 < end1)
				b[index++] = a[start1++], ++data.move;
			while (start2 < end2)
				b[index++] = a[start2++], ++data.move;
		}
		//����a�Ǹ���ǰ�����飬b�Ǹ��º������
		int* t = a;
		a = b;
		b = t;
	}
	//���û�л��������׵�ַ������ʱa������ռ���Ǹ���b��nums
	if (a != nums)
	{
		for (int i = 0; i < n; ++i)//���յĴ����鸳ֵ��nums
			b[i] = a[i];
		b = a;//����ռ�ĸ�b
	}
	//����������˾Ͳ��ø�ֵ��
	//�ͷ�����Ŀռ�
	delete[] b;
}

/***************************************************************************
  �������ƣ�heapify1
  ��    �ܣ����������������ǵݹ��㷨
  ���������int* nums, int start, int end, accord& data
			�����׵�ַ�����鷶Χ����¼�Ƚϴ������ƶ�����
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void heapify1(int* nums, int start, int end, accord& data)//[beg, end]
{
	int dad = start, son = 2 * dad + 1;
	while (son <= end)
	{
		//ȡ����Ǹ�����
		if ((son + 1) <= end && (++data.cmp, nums[son] < nums[son + 1]))
			++son;
		if (++data.cmp, nums[dad] > nums[son])//dad��son��ֱ�ӽ�������ΪҪ����top���
			return;
		//С��nums[dad]�³����ϴ���ӽ���λ��
		int t = nums[dad];
		nums[dad] = nums[son];
		nums[son] = t;
		//��¼����
		data.move += 3;

		dad = son;//������������ӽ��
		son = dad * 2 + 1;
	}
}
/***************************************************************************
  �������ƣ�heapify2
  ��    �ܣ����������������ݹ��㷨
  ���������int* nums, int start, int end, accord& data
			�����׵�ַ�����鷶Χ����¼�Ƚϴ������ƶ�����
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void heapify2(int* nums, int start, int end, accord& data)
{
	int dad = start, son = 2 * dad + 1;
	if (son > end)//�ݹ��������
		return;
	//ȡ�ϴ����
	if (son + 1 <= end && (++data.cmp, nums[son] < nums[son + 1]))
		++son;
	//dad�Ѿ���son���˾Ͳ����³���
	if (++data.cmp, nums[dad] > nums[son])
		return;
	int t = nums[dad];
	nums[dad] = nums[son];
	nums[son] = t;
	//��¼����
	data.move += 3;
	//����ݹ麯������son��Ϊ��һ����start
	heapify2(nums, son, end, data);
}
/***************************************************************************
  �������ƣ�heapSort1
  ��    �ܣ������򣬷ǵݹ��㷨
  ���������int* nums, int n, accord& data
			�����׵�ַ�������С����¼�Ƚϴ������ƶ�����
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void heapSort1(int* nums, int n, accord& data)
{
	//��ʼ���ѣ������һ����Ҷ�ӽ����ǰ
	for (int i = (n - 1) / 2; i >= 0; --i)
		heapify1(nums, i, n - 1, data);//�±��[i, n - 1]
	//�����򣬽��Ѿ��źõĶ� top �ŵ�����൱�ڳ��ѣ�
	for (int i = n - 1; i > 0; --i)//�Ӻ���ǰ��top
	{
		int t = nums[0];
		nums[0] = nums[i];
		nums[i] = t;
		data.move += 3;

		heapify1(nums, 0, i - 1, data);//�ŵ�����ˣ����¶ѻ�
	}
}
/***************************************************************************
  �������ƣ�heapSort2
  ��    �ܣ������򣬵ݹ��㷨
  ���������int* nums, int n, accord& data
			�����׵�ַ�������С����¼�Ƚϴ������ƶ�����
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void heapSort2(int* nums, int n, accord& data)
{
	//��ʼ���ѣ����м���ǰ
	for (int i = (n - 1) / 2; i >= 0; --i)
		heapify2(nums, i, n - 1, data);//�±��[i, n - 1]
	//�����򣬽��Ѿ��źõĶ� top �ŵ�����൱�ڳ��ѣ�
	for (int i = n - 1; i > 0; --i)//�Ӻ���ǰ��top
	{
		int t = nums[0];
		nums[0] = nums[i];
		nums[i] = t;
		//��¼����
		data.move += 3;

		heapify2(nums, 0, i - 1, data);//�ŵ�����ˣ����¶ѻ�
	}
}

/***************************************************************************
  �������ƣ�bucket
  ��    �ܣ�LSD�㷨��������
  ���������int* nums, int n, int base, accord& data
			�����׵�ַ�������С����ǰλ������¼�Ƚϴ������ƶ�����
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void bucket(int* nums, int n, int base, accord& data)
{
	const int BUCKETNUM = 10;
	int* bucket = new int[BUCKETNUM];
	assert(bucket != NULL);
	int* temp = new int[n];
	assert(temp != NULL);
	//Ͱ�ĳ�ʼ��
	for (int i = 0; i < BUCKETNUM; ++i)
		bucket[i] = 0;

	//��¼ÿλ���ֶ�Ӧ��Ͱ
	for (int i = 0; i < n; ++i)
		++bucket[(nums[i] / base) % 10];

	//bucket[i]��ʾiǰ��Ԫ�ظ���
	for (int i = 1; i < BUCKETNUM; ++i)
		bucket[i] += bucket[i - 1];
	//�Ӻ���ǰ��Ԫ�ط���temp���õ��ľ��ǰ�ĳλ�����źõ�
	for (int i = n - 1; i >= 0; --i)
	{
		int index = (nums[i] / base) % 10;
		temp[bucket[index] - 1] = nums[i];//��ΪͰ�����¼�ĸ�����-1ת��Ϊ�±�
		--bucket[index];//�õ�һ��Ԫ�ؼ�ȥһ��
		++data.move;
	}
	//��temp�а�ĳλ�����źõ�Ԫ�طŻ�nums
	for (int i = 0; i < n; ++i)
		nums[i] = temp[i];
	data.move += n;

	//�ͷ�����Ķ�̬�ռ�
	delete[] temp;
	delete[] bucket;
}
/***************************************************************************
  �������ƣ�radixSortLSD
  ��    �ܣ���������LSD
  ���������int* nums, int n, accord& data
			�����׵�ַ�������С����¼�Ƚϴ������ƶ�����
  �� �� ֵ��
  ˵    ����������λ�����ٵ�
***************************************************************************/
void radixSortLSD(int* nums, int n, accord& data)
{
	int Max = INT_MIN;
	//������ֵ
	for (int i = 0; i < n; ++i)
		if (++data.cmp && nums[i] > Max)
			Max = nums[i];
	//base�Ӹ�λ����Ԫ���е����λ��
	for (int base = 1; Max / base > 0; base *= 10)
		bucket(nums, n, base, data);
}

/***************************************************************************
  �������ƣ�MSDhelper
  ��    �ܣ���������MSD�ĸ�������
  ���������int* nums, int beg, int end, int base, accord& data
			�����׵�ַ�����鷶Χ����ǰλ������¼�Ƚϴ������ƶ�����
  �� �� ֵ��
  ˵    ����������λ���϶��
***************************************************************************/
void MSDhelper(int* nums, int beg, int end, int base, accord& data)
{
	//Ͱ��Ԫ�ز�����1��
	if (beg + 1 >= end)
		return;
	//�������Ϸ�
	if (base <= 0)
		return;
	const int BUCKETNUM = 10;
	int Size = end - beg + 1;
	//����ռ�
	int* bucket = new int[BUCKETNUM];
	int* temp = new int[Size];
	assert(bucket != NULL && temp != NULL);

	//bucket�����ʼ��
	for (int i = 0; i < BUCKETNUM; ++i)
		bucket[i] = 0;

	//��¼baseλ�ĸ���
	for (int i = beg; i <= end; ++i)
		++bucket[(nums[i] / base) % 10];

	//��bucketǰ׺���Եõ�Ŀ���±�
	for (int i = 1; i < BUCKETNUM; ++i)
		bucket[i] += bucket[i - 1];

	//����temp�е�Ŀ��λ��
	for (int i = beg; i <= end; ++i)
	{
		int index = (nums[i] / base) % 10;
		temp[bucket[index] - 1] = nums[i];
		--bucket[index];
		++data.move;
	}

	//temp�������źõ����зŻ�nums����
	for (int i = beg; i <= end; ++i)
		nums[i] = temp[i - beg];
	data.move += Size;

	//��ʱbucket[i]���baseλΪi�ģ���temp�����еĵ�һ��λ��
	//����ݹ麯��
	for (int i = 0; i < BUCKETNUM - 1; ++i)
		MSDhelper(nums, beg + bucket[i], beg + bucket[i + 1] - 1, base / 10, data);
	//���һ���ֵķ�Χ�Ͻ�Ϊend
	MSDhelper(nums, beg + bucket[BUCKETNUM - 1], end, base / 10, data);


	//�ͷſռ�
	delete[] temp;
	delete[] bucket;
}
/***************************************************************************
  �������ƣ�radixSortMSD
  ��    �ܣ���������MSD
  ���������int* nums, int n, accord& data
			�����׵�ַ�������С����¼�Ƚϴ������ƶ�����
  �� �� ֵ��
  ˵    ����������λ���϶��
***************************************************************************/
void radixSortMSD(int* nums, int n, accord& data)
{
	int Max = INT_MIN;
	//������ֵ
	for (int i = 0; i < n; ++i)
		if (++data.cmp, nums[i] > Max)
			Max = nums[i];
	//������λ��
	int base = 1;
	while (Max / base > 10)
		base *= 10;
	MSDhelper(nums, 0, n - 1, base, data);
}


const int defaultSizeString = 50;
class String {
private:
	int Size;//ָ��β���λ�ã���ʼ��ʱ��ע��SIze = 1
	int capacity;
	char* data;
	void expand();
	void getNext(const char* str, int* next, int len);
public:
	//���캯��
	String();
	String(String& str);
	String(const char* str);
	String(const char* str, int size);

	//��������
	~String();
	//�ַ�������
	int length()const {
		return Size - 1;
	}
	int strLen(const char* str);

	//����=
	String& operator=(const String& str);
	String& operator=(const char* str);
	String& operator=(const char& ch);

	//����<<
	friend ostream& operator<<(ostream& out, const String& str) {
		out << str.data;
		return out;
	}
	//����>>
	friend istream& operator>>(istream& in, String& str) {
		//��һ����̫������ô��
		in >> str.data;
		str.Size = str.strLen(str.data) + 1;
		return in;
	}
	//���رȽ�
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
	//����[]
	inline char& operator[](const int index) {
		return data[index];
	}
	inline char& operator[](const size_t index) {
		return data[index];
	}
	//����==
	bool operator==(const String& str);
	bool operator==(const char* str);
	//����+
	String operator+(const String& str);
	String operator+(const char* str);
	//����+=
	String& operator+=(const String& str);
	String& operator+=(const char* str);
	String& operator+=(const char ch);
	//�����ַ�������
	char* c_str() {
		return data;
	}
	char* c_str() const {
		return data;
	}
	//ģʽƥ��
	int find(const char* str);
	int find(String& str);
	//ɾ�����е�ĳ���ַ�
	void erase(char ch);
	//��ת
	void reverse();
	//���
	void clear();
	//ɾ�����һ��
	void pop_back() {
		//�յ��ַ���
		if (Size == 1)
			return;

		--Size;
		data[Size - 1] = '\0';
	}
	//���һ���ַ�
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
	++size;//���һ��β��

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
	++size;//β��

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
	++size;//β��

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

	//����str��β��
	//ע��data[Size]��β��
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


	//����str��β��
	//ע��data[Size]��β��
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
	//����str��β��
	//ע��data[Size - 1]��β��
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
	//����str��β��
	//ע��data[Size - 1]��β��
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
	//����str��β��
	//ע��data[Size - 1]��β��
	data[Size - 1] = ch;
	data[Size] = '\0';
	++Size;
	return *this;
}

void String::getNext(const char* str, int* next, int len)
{
	next[0] = -1;
	next[1] = 0;
	int i = 2;//��2��ʼ
	int cn = 0;//cn��ʾnext[i - 1]����Ϣ

	while (i < len)
	{
		if (str[i - 1] == str[cn])//���Լ������
			next[i++] = ++cn;
		else if (cn > 0)//�����Լ������
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
		if (ch != data[i])//data[i]�������˲Ÿ�ֵ�����������ָ��k++
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
	//ɾ��ԭ����
	delete[] data;
	//��������
	Size = 1;
	capacity = defaultSizeString;
	data = new char[capacity];
	data[0] = '\0';
}


#endif // !_SORT_H

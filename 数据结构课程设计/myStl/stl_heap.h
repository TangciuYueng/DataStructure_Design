#ifndef _MY_STL_HEAP
#define _MY_STL_HEAP
#include "stl_vector.h"
#include "stl_functional.h"

//����
template<class Iter, class Compare>
void pushHeap(Iter beg, Iter end, Compare cmp)
{
	if (end - 1 <= beg)
		return;
	siftFix(beg, end, cmp);
}
template<class Iter>
void pushHeap(Iter beg, Iter end)
{
	typedef typename Iter::value_type value_type;

	if (end - 1 <= beg)
		return;
	siftFix(beg, end, Less<value_type>());
}
template<class Iter, class Compare>
void siftFix(Iter beg, Iter end, Compare cmp)
{
	typedef typename Iter::value_type value_type;

	//�¼����Ԫ�ص�ֵ
	value_type val = *(end - 1);
	//Ҫ�����hole��λ��
	int hole = (end - 1) - beg;
	//hole�ĸ��ڵ�
	int parent = (hole - 1) / 2;
	//���� ���� ���� holeԽ�� or ������cmp��ϵ
	while (hole >= 0 && hole != parent && cmp( *(beg + parent), val))
	{
		//���ڵ��ֵ����
		*(beg + hole) = *(beg + parent);
		//hole��ȥ
		hole = parent;
		parent = (hole - 1) / 2;
	}
	//hole��ȥ������ȥ�����λ��
	*(beg + hole) = val;
}



//����ϵ�Ԫ�طŵ����
template<class Iter>
void popHeap(Iter beg, Iter end)
{
	typedef typename Iter::value_type value_type;

	if (end - 1 <= beg)
		return;
	sinkFix(beg, end, Less<value_type>());
}
template<class Iter, class Compare>
void popHeap(Iter beg, Iter end, Compare cmp)
{
	if (end - 1 <= beg)
		return;
	sinkFix(beg, end, cmp);
}
template<class Iter, class Compare>
void sinkFix(Iter beg, Iter end, Compare cmp)
{
	typedef typename Iter::value_type value_type;

	//Ҫ�����Ԫ�ص�ֵ
	value_type val = *beg;
	int hole = 0;
	int leftNode = hole * 2 + 1;
	int rightNode = leftNode + 1;
	int len = end - beg;
	//Ѱ�����һ��Ԫ��Ҫȥ��hole����Ϊ��һ��Ԫ��Ҫռ��
	while (rightNode < len)
	{
		//ѡ�з����������Ǹ����ӽ�����hole�³�
		if (cmp(*(beg + rightNode), *(beg + leftNode)))
		{
			*(beg + hole) = *(beg + leftNode);
			hole = leftNode;
		}
		else
		{
			*(beg + hole) = *(beg + rightNode);
			hole = rightNode;
		}
		leftNode = hole * 2 + 1;
		rightNode = leftNode + 1;
	}
	//����һ�����������ӣ�����hole�³�
	if (leftNode < len)
	{
		*(beg + hole) = *(beg + leftNode);
		hole = leftNode;
	}
	//���һ��λ��Ҫ��valռ�ã�
	*(beg + hole) = *(end - 1);
	//���������˳���ٽ�������
	siftFix(beg, beg + hole + 1, cmp);
	*(end - 1) = val;
}

#endif // !_MY_STL_HEAP

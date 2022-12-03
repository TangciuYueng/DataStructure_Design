#ifndef _MY_STL_PRIORITY_QUEUE
#define _MY_STL_PRIORITY_QUEUE

#include <iostream>
using namespace std;
#include "stl_heap.h"
#include "stl_functional.h"
template<class T,  class Seq = Vector<T>, class Compare = Less<T>>
class Priority_queue {
private:
	Seq data;
	Compare cmp;
public:
	//���캯��
	Priority_queue() :data(), cmp() {}
	Priority_queue(const Compare& cmp) :data(), cmp(cmp) {}
	/*������
	template<class Iter, class T>
	Priority_queue(Iter beg, Iter end, Compare cmp = Less<T>()) :data(beg, end){
		//makeHeap(beg, end, cmp);
	}*/
	//��������
	~Priority_queue() {}
	//�ж��Ƿ�Ϊ��
	bool empty() const {
		return data.empty();
	}
	//���ش�С
	int size() const {
		return data.size();
	}
	//��
	const T top() const{
		return data.front();
	}
	//����Ԫ��
	void emplace(const T& x)
	{
		data.emplace_back(x);
		pushHeap(data.begin(), data.end());
	}
	//����Ԫ��
	void pop()
	{
		popHeap(data.begin(), data.end());
		data.pop_back();
	}
	void showData()
	{
		for (auto it = data.begin(); it != data.end(); ++it)
			cout << *it << " ";
		cout << endl;
	}
};

#endif // !_MY_STL_PRIORITY_QUEUE

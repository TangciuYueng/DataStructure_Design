#ifndef _ELESYSTEM_H
#define _ELESYSTEM_H

#include <iostream>
#include <climits> 
#include <algorithm>
using namespace std;


template<class T>
struct Less {
	bool operator()(const T& x, const T& y) {
		return x < y;
	}
};
template<class T>
struct Greater {
	bool operator()(const T& x, const T& y) {
		return x > y;
	}
};
template<class T>
void Swap(T& x, T& y) {
	T temp = x;
	x = y;
	y = temp;
}
template <typename Iter>
void Random_shuffle(Iter begin, Iter end)
{
	int rest = end - begin;
	while (begin != end) {
		Swap(*begin, *(begin + rand() % rest));
		--rest;
		++begin;
	}
}

//Pair��Ԫ����
template<class T1, class T2>
class Pair {
public:
	T1 first;
	T2 second;
public:
	//���캯��
	Pair() :first(T1()), second(T2()) {}
	Pair(const T1& first, const T2& second) {
		this->first = first;
		this->second = second;
	}
	Pair(const Pair<T1, T2>& P) {
		this->first = P.first;
		this->second = P.second;
	}
	//�����Եĸ��ƹ��캯��
	template<class U1, class U2>
	Pair(const Pair<U1, U2>& P) :first(P.first), second(P.second) {}
	//���������
	Pair& operator=(const Pair<T1, T2>& P)
	{
		first = P.first;
		second = P.second;
		return *this;
	}
	//��д����Ԫ��������������const�޶� 
	inline friend bool operator==(const Pair<T1, T2>& p1, const Pair<T1, T2>& p2) {
		return p1.first == p2.first && p1.second == p2.second;
	}
	inline friend bool operator!=(const Pair<T1, T2>& p1, const Pair<T1, T2>& p2) {
		return p1.first != p2.first || p1.second != p2.second;
	}
	inline friend bool operator<(const Pair<T1, T2>& p1, const Pair<T1, T2>& p2) {
		return p1.first < p2.first || (p1.first == p2.first && p1.second < p2.second);
	}
	inline friend bool operator>(const Pair<T1, T2>& p1, const Pair<T1, T2>& p2) {
		return p1.first > p2.first || (p1.first == p2.first && p1.second > p2.second);
	}
	inline friend bool operator<=(const Pair<T1, T2>& p1, const Pair<T1, T2>& p2) {
		return p1.first <= p2.first || (p1.first == p2.first && p1.second <= p2.second);
	}
	inline friend bool operator>=(const Pair<T1, T2>& p1, const Pair<T1, T2>& p2) {
		return p1.first >= p2.first || (p1.first == p2.first && p1.second >= p2.second);
	}
	Pair& operator+(const Pair<T1, T2>& P) {
		return Pair<T1, T2>(first + P.first, second + P.second);
	}
	Pair& operator-(const Pair<T1, T2>& P) {
		return Pair<T1, T2>(first - P.first, second - P.second);
	}
};

template<class T1, class T2>
inline Pair< T1, T2> Make_pair(const T1& x, const T2& y) {
	return Pair<T1, T2>(x, y);
}


//����ڵ�
template<class T>
struct list_node {
	T val;
	list_node* prev, * next;
	list_node() {
		prev = NULL;
		next = NULL;
	}
	//���캯��
	list_node(const T& val, list_node* prev = NULL, list_node* next = NULL) :
		val(val), prev(prev), next(next) {}
};

//precious declare the class has template
//so that in the list<T> we can friend class Stack<T>
template<class T>
class Stack;

template<class T>
class Queue;

//˫������ʵ��
template<class T>
class List {
	typedef list_node<T>* _iterator;
	//	template<class T>
	friend class Stack<T>;
	//	template<class T>
	friend class Queue<T>;
private:
	//ͷ��� β���
	list_node<T>* head, * tail;

	//������
	int Size;

	//�鲢�ݹ麯��
	list_node<T>* _mergeSort(list_node<T>* head);

	//��from��ʼ�ж�step��㣬���������һ��
	list_node<T>* cut(list_node<T>* from, int step);

	//�鲢����ĺϲ�
	list_node<T>* merge(list_node<T>* l1, list_node<T>* l2);

public:
	//���캯��
	List();

	//��������
	~List();

	//���������С
	inline int size() const {
		return Size;
	}

	//�ж������Ƿ�Ϊ��
	inline bool empty() const {
		return head == tail;
	}

	//�õ�ͷ���
	inline list_node<T>* getHead() const {
		return head;
	}

	//�õ�β�ڵ�
	inline list_node<T>* getTail() const {
		return tail;
	}

	//�������
	void clear();

	//������Ԫ��
	void emplace_back(const T& x);

	//���ɾ��Ԫ��
	void pop_back();

	//��ͷ���Ԫ��
	void emplace_front(const T& x);

	//��ͷɾ��Ԫ��
	void pop_front();

	//����=
	List<T>& operator=(const List<T>& L);

	//���������
	class list_iterator {
		friend class List<T>;
	private:
		//ָ��ڵ��ָ��
		_iterator data;
	public:
		//���캯��
		list_iterator(_iterator data) {
			this->data = data;
		}
		list_iterator(const T& x) {
			data = new list_node<T>(x);
		}
		//����*
		T& operator*() {
			return data->val;
		}
		//����->
		T* operator->() {
			return &(data->val);
		}
		//����==
		inline bool operator==(const list_iterator& it) const {
			return this->data == it.data;
		}
		//����!=
		inline bool operator!=(const list_iterator& it) const {
			return this->data != it.data;
		}
		//�����Լ�
		inline List<T>::list_iterator& operator++()
		{
			if (data != NULL)
				data = data->next;
			return *this;
		}
		//�����Լ�
		inline List<T>::list_iterator& operator--()
		{
			if (data != NULL)
				data = data->prev;
			return *this;
		}
		//�����Լ�
		List<T>::list_iterator operator++(int)
		{
			List<T>::list_iterator temp = *this;
			++(*this);
			return temp;
		}
		//�����Լ�
		List<T>::list_iterator operator--(int)
		{
			List<T>::list_iterator temp = *this;
			--(*this);
			return temp;
		}
		//���������
		List<T>::list_iterator operator+(int num)
		{
			List<T>::list_iterator temp = *this;
			for (int i = 0; i < num; ++i)
				++temp;
			return temp;
		}
		//���������
		List<T>::list_iterator operator-(int num)
		{
			List<T>::list_iterator temp = *this;
			for (int i = 0; i < num; ++i)
				--temp;
			return temp;
		}
		//�Լ�
		List<T>::list_iterator operator+=(int num)
		{
			for (int i = 0; i < num; ++i)
				++(*this);
			return *this;
		}
		//�Լ�
		List<T>::list_iterator operator-=(int num)
		{
			for (int i = 0; i < num; ++i)
				--(*this);
			return *this;
		}
		//�������
		int operator-(const list_iterator& it)
		{
			int ans = 0;
			List<T>::list_iterator temp = *this;
			while (temp != it)
			{
				--temp;
				++ans;
			}
			return ans;
		}
	};

	//���ƹ��캯��
	List(const List<T>& L);

	//����
	void insert(const List<T>::list_iterator& it, const T& x);

	//ɾ��
	void remove(const List<T>::list_iterator& it);

	//������begin
	inline List<T>::list_iterator begin() {
		return List<T>::list_iterator(head->next);
	}

	//������end
	inline List<T>::list_iterator end() {
		return List<T>::list_iterator(tail->next);
	}

	//���ص������Ĳ���
	typename List<T>::list_iterator find(const T& x);

	//�ݹ�����
	void mergeSort1() {
		if (head->next == NULL)//û��Ԫ��
			return;
		//����û��ͷ�Ľ���������
		head->next = _mergeSort(head->next);
		list_node<T>* cur = head->next;
		//�����һ�����
		while (cur->next)
			cur = cur->next;
		//���������һ�����
		tail = cur;
	}

	//��������
	void mergeSort2();
};

//���캯��
template<class T>
List<T>::List()
{
	head = new list_node<T>();
	tail = head;
	Size = 0;
}

//��ֵ���캯��
template<class T>
List<T>::List(const List<T>& L)
{
	head = new list_node<T>();
	tail = head;
	Size = 0;
	list_node<T>* Lcur = L.getHead()->next;
	while (Lcur)
	{
		emplace_back(Lcur->val);
		Lcur = Lcur->next;
	}
}

//��������
template<class T>
List<T>::~List() {
	clear();
	delete head;
}

//�������
template<class T>
void List<T>::clear()
{
	list_node<T>* cur = head->next;
	while (cur)
	{
		head->next = cur->next;
		delete cur;
		cur = head->next;
	}
	Size = 0;
	tail = head;
}

//������Ԫ��
template<class T>
void List<T>::emplace_back(const T& x)
{
	//�����µĿռ�
	list_node<T>* node = new list_node<T>(x);
	++Size;//Ԫ�ظ�������
	//�������һ��
	tail->next = node;
	node->prev = tail;
	//β������
	tail = node;
}

//���ɾ��Ԫ��
template<class T>
void List<T>::pop_back()
{
	if (empty())//���˾Ͳ���ɾ��
		return;
	--Size;//Ԫ�ظ�������
	list_node<T>* temp = tail->prev;
	delete tail;
	tail = temp;
	tail->next = NULL;//β������β
}

//��ͷ���Ԫ��
template<class T>
void List<T>::emplace_front(const T& x)
{
	list_node<T>* node = new list_node<T>(x);
	++Size;//Ԫ�ظ�������
	if (empty())//����Ϊ��ע�����β���
	{
		head->next = node;
		node->prev = head;

		tail = node;
	}
	else
	{
		node->next = head->next;
		node->prev = head;

		head->next = node;
		node->next->prev = node;
	}
}

//ɾ����ͷԪ��
template<class T>
void List<T>::pop_front()
{
	if (empty())//���˾Ͳ���ɾ��
		return;
	--Size;//Ԫ�ظ�������
	//Ҫɾ���Ľڵ����һ��
	list_node<T>* temp = head->next->next;
	list_node<T>* del = head->next;
	delete del;
	head->next = temp;
	if (temp)//�����һ����Ϊ��
		temp->prev = head;
	else//��һ��Ϊ�գ�����β���ָ��ͷ���
		tail = head;
}

//���õ���������
template<class T>
void List<T>::insert(const List<T>::list_iterator& it, const T& x)
{
	if (it.data == NULL)
		return;
	//�е������ṩ�ɲ���λ�ã������ܸı�β���
	list_node<T>* temp = it.data;

	temp->prev->next = new list_node<T>(x, temp->prev, temp);
	temp->prev = temp->prev->next;

	++Size;
}

//���õ�����ɾ��
template<class T>
void List<T>::remove(const List<T>::list_iterator& it)
{
	if (it.data == NULL)//������Ϊ��
		return;

	list_node<T>* temp = it.data;
	//β��������
	if (temp == tail)
	{
		tail = temp->prev;
		tail->next = NULL;
	}
	else
	{
		temp->next->prev = temp->prev;
		temp->prev->next = temp->next;
	}
	delete temp;
	--Size;//Ԫ�ظ�������
}

//���ظ�ֵ
template<class T>
List<T>& List<T>::operator=(const List<T>& L)
{
	clear();//�����ԭ�����
	list_node<T>* cur = L.getHead()->next;
	while (cur)
	{
		emplace_back(cur->val);
		cur = cur->next;
	}

	return *this;
}

//��ѯ�Ƿ���ֵ
template<class T>
typename List<T>::list_iterator List<T>::find(const T& x)
{
	for (auto it = begin(); it != end(); ++it)
		if (*it == x)
			return it;
	return NULL;
}

//�ݹ�鲢����
template<class T>
list_node<T>* List<T>::_mergeSort(list_node<T>* head)
{
	//û�н���ֻ�пս�㣬ֱ�ӷ���
	if (head == NULL || head->next == NULL)
		return head;

	list_node<T>* slow = head, * fast = head, * prev = NULL;
	//����ָ�����м�
	while (fast && fast->next)
	{
		prev = slow;
		slow = slow->next;
		fast = fast->next->next;
	}

	//�Ͽ��м䣬�ֳ�����
	prev->next = NULL;

	list_node<T>* p1, * p2, * D = new list_node<T>(0), * p3 = D;
	p1 = _mergeSort(head);
	p2 = _mergeSort(slow);
	//�ϲ�
	while (p1 && p2)
	{
		if (p1->val < p2->val)
		{
			p3->next = p1;
			p1->prev = p3;

			p1 = p1->next;
			p3 = p3->next;
		}
		else
		{
			p3->next = p2;
			p2->prev = p3;

			p2 = p2->next;
			p3 = p3->next;
		}
	}
	//ʣ�µ�һ����
	while (p1)
	{
		p3->next = p1;
		p1->prev = p3;

		p1 = p1->next;
		p3 = p3->next;
	}
	while (p2)
	{
		p3->next = p2;
		p2->prev = p3;

		p2 = p2->next;
		p3 = p3->next;
	}
	p3->next = NULL;//��β����

	list_node<T>* ans = D->next;
	//�ͷſռ�
	delete D;
	return ans;
}

//�����鲢����
template<class T>
void List<T>::mergeSort2()
{
	//ֻ��һ����û�н��
	if (head->next == NULL || head->next->next == NULL)
		return;

	list_node<T>* cur;

	for (int step = 1; step < Size; step *= 2)//������ϳ�2
	{
		list_node<T>* tempTail = head;
		cur = head->next;

		while (cur)
		{
			list_node<T>* left = cur;
			list_node<T>* right = cut(left, step);
			cur = cut(right, step);
			tempTail->next = merge(left, right);
			while (tempTail->next)
				tempTail = tempTail->next;
		}
		tail = tempTail;//����β���
	}
}

//��from��ʼ�е�ǰstep��Ԫ�أ��������һ��Ԫ��
template<class T>
list_node<T>* List<T>::cut(list_node<T>* from, int step)
{
	--step;
	while (from && step)
	{
		from = from->next;
		--step;
	}
	//����step��Ԫ��
	if (from == NULL)
		return NULL;
	list_node<T>* next = from->next;
	//�ж�
	from->next = NULL;
	return next;
}

//�ϲ������������������ϲ�Ϊһ��������
template<class T>
list_node<T>* List<T>::merge(list_node<T>* l1, list_node<T>* l2)
{
	list_node<T>* D = new list_node<T>(0);
	list_node<T>* cur = D;
	while (l1 && l2) {
		if (l1->val < l2->val)
		{
			cur->next = l1;
			l1->prev = cur;

			l1 = l1->next;
		}
		else
		{
			cur->next = l2;
			l2->prev = cur;

			l2 = l2->next;
		}
		cur = cur->next;
	}
	while (l1)
	{
		cur->next = l1;
		l1->prev = cur;

		l1 = l1->next;
		cur = cur->next;
	}
	while (l2)
	{
		cur->next = l2;
		l2->prev = cur;

		l2 = l2->next;
		cur = cur->next;
	}
	cur->next = NULL;//��β����
	list_node<T>* ans = D->next;
	delete D;
	return ans;
}

//��ʽ������
template<class T>
class Queue {
private:
	List<T> data;
public:
	Queue() {}
	inline bool empty() const {
		return data.empty();
	}
	inline int size() const {
		return data.Size;
	}
	void clear() {
		data.clear();
	}
	void emplace(const T& x) {
		data.emplace_back(x);
	}
	void pop() {
		data.pop_front();
	}
	T& front() {
		return data.getHead()->next->val;
	}
};


const int defaultSize = 10;

template<class T>
class Vector {
	//����������
	typedef T* iterator;
private:
	//Ԫ�ظ���
	int Size;

	//ʵ������
	int capacity;

	//�ڲ�����
	T* data;

	//���ݺ���
	void expand();
public:
	//���캯��
	Vector();
	Vector(int size);
	Vector(const Vector<T>& V);
	Vector(int size, const T& val);

	//��������
	~Vector();

	//����Ԫ�ظ���
	inline int size() const {
		return Size;
	}

	//�ж������Ƿ�Ϊ��
	inline bool empty() const {
		return Size == 0;
	}

	//Vector������
	class vector_iterator {
		friend class Vector<T>;
	private:
		iterator data;
	public:
		typedef T value_type;
		vector_iterator(iterator data) :data(data) {}
		//����*
		T& operator*() {
			return *data;
		}
		T* operator->() {
			return data;
		}
		//����==
		inline bool operator==(const vector_iterator& it) const {
			return this->data == it.data;
		}
		//����!=
		inline bool operator!=(const vector_iterator& it) const {
			return this->data != it.data;
		}
		//���ز��Ⱥ�
		inline bool operator<(const vector_iterator& it) const {
			return this->data < it.data;
		}
		inline bool operator>(const vector_iterator& it) const {
			return this->data > it.data;
		}
		inline bool operator<=(const vector_iterator& it) const {
			return this->data <= it.data;
		}
		inline bool operator>=(const vector_iterator& it) const {
			return this->data >= it.data;
		}
		//�����Լ�
		inline Vector<T>::vector_iterator& operator++()
		{
			if (data != NULL)
				++data;
			return *this;
		}
		//�����Լ�
		inline Vector<T>::vector_iterator& operator--()
		{
			if (data != NULL)
				--data;
			return *this;
		}
		//�����Լ�
		Vector<T>::vector_iterator operator++(int)
		{
			Vector<T>::vector_iterator temp = *this;
			++(*this);
			return temp;
		}
		//�����Լ�
		Vector<T>::vector_iterator operator--(int)
		{
			Vector<T>::vector_iterator temp = *this;
			--(*this);
			return temp;
		}
		//���������
		friend Vector<T>::vector_iterator operator+(const vector_iterator& it, int num)
		{
			Vector<T>::vector_iterator temp = it;
			for (int i = 0; i < num; ++i)
				++temp;
			return temp;
		}
		//���������
		friend Vector<T>::vector_iterator operator-(const vector_iterator& it, int num)
		{
			Vector<T>::vector_iterator temp = it;
			for (int i = 0; i < num; ++i)
				--temp;
			return temp;
		}
		//�Լ�
		Vector<T>::vector_iterator operator+=(int num)
		{
			for (int i = 0; i < num; ++i)
				++(*this);
			return *this;
		}
		//�Լ�
		Vector<T>::vector_iterator operator-=(int num)
		{
			for (int i = 0; i < num; ++i)
				--(*this);
			return *this;
		}
		//�������
		friend int operator-(const vector_iterator& it1, const vector_iterator& it2)
		{
			int ans = 0;
			Vector<T>::vector_iterator temp = it1;
			while (it2 != temp)
			{
				--temp;
				++ans;
			}
			return ans;
		}
	};

	//���Vector
	void clear();

	//������Ԫ��
	void emplace_back(const T& x);

	//���ɾ��Ԫ��
	void pop_back();

	//�������Ԫ��
	const T back() const {
		return data[Size - 1];
	}
	T& back() {
		return data[Size - 1];
	}

	//���ؿ�ͷԪ��
	const T front() const {
		return data[0];
	}
	T& front() {
		return data[0];
	}

	//����
	void insert(const Vector<T>::vector_iterator& it, const T& x);


	//ɾ��
	void remove(const Vector<T>::vector_iterator& it);

	//������begin
	inline Vector<T>::vector_iterator begin() {
		if (Size == 0)
			return NULL;
		return vector_iterator(data);
	}
	//������end
	inline Vector<T>::vector_iterator end() {
		if (Size == 0)
			return NULL;
		return vector_iterator(data + Size);
	}

	//���ص������Ĳ���
	typename Vector<T>::vector_iterator find(const T& x);

	//����[]
	T& operator[](const int index) {
		return data[index];
	}

	//����=
	Vector<T>& operator=(const Vector<T>& V);

	//�������ô�С
	void resize(int size);
	void resize(int size, const T& val);
};

//���캯��
template<class T>
Vector<T>::Vector()
{
	Size = 0;
	capacity = defaultSize;
	data = new T[capacity];
}

//ָ����С���캯��
template<class T>
Vector<T>::Vector(int size)
{
	Size = size;
	capacity = (Size / defaultSize + 1) * defaultSize;
	Size = 0;//ֻ����Ҫsize���ռ䣬��û�����Ԫ�ؽ���
	data = new T[capacity];
}

//���ƹ��캯��
template<class T>
Vector<T>::Vector(const Vector<T>& V)
{
	Size = V.Size();
	capacity = (Size / defaultSize + 1) * defaultSize;
	data = new T[capacity];

	for (int i = 0; i < Size; ++i)
		data[i] = V.data[i];
}

//ָ����С��Ԫ��ֵ���캯��
template<class T>
Vector<T>::Vector(int size, const  T& val)
{
	Size = size;
	capacity = (Size / defaultSize + 1) * defaultSize;
	data = new T[capacity];
	for (int i = 0; i < Size; ++i)
		data[i] = val;
}

//��������
template<class T>
Vector<T>::~Vector()
{
	delete[] data;
}

//���ݺ���
template<class T>
void Vector<T>::expand()
{
	capacity += defaultSize;
	T* newData = new T[capacity];

	for (int i = 0; i < Size && i < capacity; ++i)
		newData[i] = data[i];

	delete[] data;
	data = newData;
}

//���Vector
template<class T>
void Vector<T>::clear()
{
	Size = 0;
	capacity = defaultSize;

	delete[] data;
	data = new T[capacity];
}

//��������
template<class T>
void Vector<T>::emplace_back(const T& x)
{
	if (Size == capacity - 1)
		expand();
	data[Size++] = x;//��data[Size]��λ�����
}

//���ɾ��
template<class T>
void Vector<T>::pop_back()
{
	if (Size == 0)
		return;
	--Size;//ֱ�Ӳ�Ҫ����Ǹ��ռ�
}

//���õ���������
template<class T>
void Vector<T>::insert(const Vector<T>::vector_iterator& it, const T& x)
{
	int loc = it - begin();//���Ҫ������±�
	if (loc < 0 || loc > Size + 1)
		return;

	if (Size == capacity - 1)//�ռ䲻��������
		expand();

	for (int i = Size - 1; i >= loc; --i)//loc��Size-1��Ԫ��ȫ������
		data[i + 1] = data[i];

	data[loc] = x;
	++Size;
}

//���õ�����ɾ��
template<class T>
void Vector<T>::remove(const Vector<T>::vector_iterator& it)
{
	if (it == NULL || Size == 0)
		return;

	int loc = it - begin();
	if (loc < 0 || loc >= Size)
		return;

	//��ǰ�ƣ����ǵ�locλ��
	for (int i = loc; i < Size - 1; ++i)
		data[i] = data[i + 1];

	--Size;
}

//����=
template<class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& V)
{
	Size = V.size();
	capacity = V.capacity;
	delete[] data;
	data = new T[capacity];
	for (int i = 0; i < Size && i < capacity; ++i)
		data[i] = V.data[i];
	return *this;
}

//�������ô�С
template<class T>
void Vector<T>::resize(int size)
{
	if (capacity < size)
	{
		capacity = (size / defaultSize + 1) * defaultSize;
		T* newData = new T[capacity];
		for (int i = 0; i < Size; ++i)
			newData[i] = data[i];
		delete[] data;
		data = newData;
	}
}

//����Ԫ����䣬�������ô�С
template<class T>
void Vector<T>::resize(int size, const T& val)
{
	if (capacity < size)
	{
		capacity = (size / defaultSize + 1) * defaultSize;
		T* newData = new T[capacity];
		for (int i = 0; i < Size; ++i)
			newData[i] = val;//��ֵȫ����Ϊval
		delete[] data;
		data = newData;
		Size = size;
	}
	else//�����ֱ�����
	{
		for (int i = 0; i < size; ++i)
			data[i] = val;//��ֵȫ����Ϊval
		Size = size;
	}
}

//Ѱ��ֵΪx�ģ����ص�����
template<class T>
typename Vector<T>::vector_iterator Vector<T>::find(const T& x)
{
	for (auto it = begin(); it != end(); ++it)
		if (*it == x)
			return it;
	return NULL;
}

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
	while (hole >= 0 && hole != parent && cmp(*(beg + parent), val))
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

// ģ��Ҳ������Ĭ�ϲ���
template<class T, class Seq = Vector<T>, class Compare = Less<T>>
class Priority_queue {
private:
	Seq data;
	Compare cmp;
public:
	//���캯��
	Priority_queue() :data(), cmp() {}
	Priority_queue(const Compare& cmp) :data(), cmp(cmp) {}
	//������
	template<class Iter, class T>
	Priority_queue(Iter beg, Iter end, Compare cmp = Less<T>()) : data(beg, end) {
		//makeHeap(beg, end, cmp);
	}
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
	const T top() const {
		return data.front();
	}
	//����Ԫ��
	void emplace(const T& x)
	{
		data.emplace_back(x);
		pushHeap(data.begin(), data.end(), cmp);
	}
	//����Ԫ��
	void pop()
	{
		popHeap(data.begin(), data.end(), cmp);
		data.pop_back();
	}
	void showData()
	{
		for (auto it = data.begin(); it != data.end(); ++it)
			cout << *it << " ";
		cout << endl;
	}
};


//Ĭ������ռ��С50��char
const int defaultSizeString = 50;

class String {
private:
	//ָ��β���λ�ã���ʼ��ʱ��ע��Size = 1
	int Size;

	//ʵ������
	int capacity;

	//��������
	char* data;

	//��������defaultSizeString
	void expand();

	//ģʽ��ƥ��õ�next���麯��
	void getNext(const char* str, int* next, int len);
public:
	//�չ��캯��
	String();

	//��ֵ���캯��
	String(const String& str);

	//�ַ������캯��
	String(const char* str);

	//��СΪsize���ַ������캯��
	String(const char* str, int size);

	//��������
	~String();

	//�ַ�������
	int length()const {
		//��ȥ����β��
		return Size - 1;
	}

	//�����ַ������ȣ���ʵ���������޹أ�����Ϊ��̬��Ա����
	static int strLen(const char* str);

	//����=��Stirng
	String& operator=(const String& str);

	//����=���ַ���
	String& operator=(const char* str);

	//����=��һ���ַ�
	String& operator=(const char& ch);

	//����<<
	friend ostream& operator<<(ostream& out, const String& str) {
		out << str.data;
		return out;
	}

	//����>>
	friend istream& operator>>(istream& in, String& str) {
		//����������⣬����̫���ַ�������Ǻ�
		in >> str.data;
		str.Size = str.strLen(str.data) + 1;
		return in;
	}

	//���رȽϺ���
	friend int strCmp(const String& str1, const String& str2)
	{
		int i = 0;
		while (str1.data[i] && str2.data[i])
		{
			//�����˲�ͬ�ģ�������ͬλ�õ�һ�����ڶ���
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
	//����< > <= >=
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
		data[Size - 1] = '\0';//֮ǰβ��ǰ���ַ�����β��
	}

	//������һ���ַ�
	char back() const {
		if (Size <= 1)
			return '\0';
		return data[Size - 2];
	}

};
//���캯��
String::String()
{
	Size = 1;
	capacity = defaultSizeString;
	data = new char[capacity];
	data[0] = '\0';
}
String::String(const String& str)
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

//��������
String::~String() {
	delete[] data;
}

//�ַ�������
int String::strLen(const char* str)
{
	int size = 0;
	while (str[size] != '\0')
		++size;
	return size;
}

//��������defaultSizeString
void String::expand()
{
	capacity += defaultSizeString;
	char* newData = new char[capacity];
	for (int i = 0; i < Size && Size < capacity; ++i)
		newData[i] = data[i];
	delete[] data;
	data = newData;
}

//����=
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

//����==
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

//����+
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

//����+=
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

//ģʽ��ƥ��
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

//ɾ������ֵΪch��
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
}

//��ת
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

//���
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

enum COLOR {
	RED, BLACK
};

/*
	������ڵ�
	������ɫ������avl����ƽ������
	�����½ڵ�Ĭ��Ϊ��ɫ������븸�ڵ�������ɫ�ƻ��͵���
*/
template<class K, class V>
struct RBTreeNode {
	Pair<K, V> _kv;
	COLOR _color;
	RBTreeNode<K, V>* _parent;
	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;

	RBTreeNode(const Pair<K, V>& kv = Pair<K, V>(),
		COLOR color = RED, RBTreeNode<K, V>* parent = NULL
		, RBTreeNode<K, V>* left = NULL
		, RBTreeNode<K, V>* right = NULL)
		: _kv(kv), _color(color),
		_parent(parent), _left(left), _right(right)
	{}
};

template<class K, class V>
class RBTree;

template<class K, class V>
class tree_iterator {
	//friend class RBTree<K, V>;
	typedef RBTreeNode<K, V> Node;
	typedef tree_iterator<K, V> Self;
public:
	Node* data;
public:
	tree_iterator(Node* data = NULL) : data(data) {}
	Pair<K, V>& operator*() {
		return data->_kv;
	}
	Pair<K, V>* operator->() {
		return &(data->_kv);
	}
	Self& operator++()
	{
		//������������ĺ�һ��, �ȵ�ǰdata��_kv.first��ĵ�һ��
		if (data->_right)//���ҽ��
		{
			data = data->_right;
			while (data->_left)
				data = data->_left;
		}
		else//û���ҽ�㣬���Ҹ��ڵ�
		{
			Node* fa = data->_parent;
			while (data == fa->_right)//�Ǹ��ڵ��������
			{
				data = fa;
				fa = fa->_parent;
			}
			if (data->_right != fa)
				data = fa;
		}
		return *this;
	}
	Self& operator--()
	{
		if (data->_left)
		{
			data = data->_left;
			while (data->_right)
				data = data->_right;
		}
		else
		{
			Node* fa = data->_parent;
			while (data == fa->_left)
			{
				data = fa;
				fa = fa->_parent;
			}
			if (data->_left != fa)
				data = fa;
		}
		return *this;
	}
	Self operator++(int) {
		Self old = *this;
		++* this;
		return old;
	}
	Self operator--(int) {
		Self old = *this;
		--* this;
		return old;
	}
};

template<class K, class V>
inline bool operator==(const tree_iterator<K, V>& it1,
	const tree_iterator<K, V>& it2) {
	return it1.data == it2.data;
}
template<class K, class V>
inline bool operator!=(const tree_iterator<K, V>& it1,
	const tree_iterator<K, V>& it2) {
	return it1.data != it2.data;
}

//�����
template<class K, class V>
class RBTree {
	typedef RBTreeNode<K, V> Node;
	typedef tree_iterator<K, V> Iterator;
private:
	Node* head;
	size_t Size;
public:
	RBTree();
	~RBTree() {
		clear();
		delete head;
	}
	inline bool empty() const {
		return head->_parent = head;
	}
	inline size_t size() const {
		return Size;
	}
	inline Iterator begin() {
		return Iterator(mostLeft(head->_parent));
	}
	inline Iterator end() {
		return NULL;
	}
	inline Node* getRoot() {
		return head->_parent;
	}
	inline Node* getHead() const {
		return head;
	}
	Pair<Iterator, bool> insert(const Pair<K, V>& p);
	void erase(Iterator it);
	void erase(const K& key);
	Iterator find(const K& key);
	static Node* mostLeft(Node* cur)
	{
		while (cur->_left)
			cur = cur->_left;
		return cur;
	}
	static Node* mostRight(Node* cur)
	{
		while (cur->_right)
			cur = cur->_right;
		return cur;
	}
	void inOrder() {
		inOrder(getRoot());
	}
	void clear();
private:
	void inOrder(Node* root);
	void adjust(Node* son);
	void clear(Node* cur);
	void rotateLeft(Node*& fa);
	void rotateRight(Node*& fa);
	Pair<Node*, bool> findToPair(const K& key);
};

template<class K, class V>
RBTree<K, V>::RBTree()
{
	head = new Node();
	head->_left = head;
	head->_right = head;
	head->_parent = head;
	Size = 0;
}


template<class K, class V>
void RBTree<K, V>::clear()
{
	//ɾ������ͷ�������н��
	clear(head->_parent->_left);
	clear(head->_parent->_right);
	//ͷ���ָ���ʼ��
	head->_left = head;
	head->_right = head;
	head->_parent = head;
	Size = 0;//Ԫ�ظ�����ʼ��
}

template<class K, class V>
void RBTree<K, V>::clear(Node* cur)
{
	if (cur == head || cur == NULL)//�ݹ����
		return;

	clear(cur->_left);//ɾ�����ӽڵ�
	clear(cur->_right);//ɾ�����ӽ��

	delete cur;//ɾ���Լ�
	cur = NULL;//�ÿ�
}

template<class K, class V>
Pair<RBTreeNode<K, V>*, bool> RBTree<K, V>::findToPair(const K& key)
{
	if (head->_parent == head)//����
		return Pair<RBTreeNode<K, V>*, bool>(NULL, false);
	//�Ӹ��ڵ㿪ʼѰ��
	Node* cur = head->_parent;
	//��¼���
	Pair<RBTreeNode<K, V>*, bool> res(NULL, false);

	while (cur)
	{
		//��¼���ڵ�, ��Ҫ�ҵĽڵ�
		res.first = cur;
		if (key < cur->_kv.first)
			cur = cur->_left;
		else if (key > cur->_kv.first)
			cur = cur->_right;
		else//�ҵ�key��ͬ��, ���ظýڵ�
			return Pair<RBTreeNode<K, V>*, bool>(cur, true);
	}
	//�Ҳ�����������ҵĸ��ڵ�, ��¼�ɲ���λ��
	return res;
}

template<class K, class V>
Pair<tree_iterator<K, V>, bool> RBTree<K, V>::insert(const Pair<K, V>& p)
{
	if (head->_parent == head)//����, ������Ϊ�����
	{
		head->_parent = new Node(p);
		head->_left = head->_parent;
		head->_right = head->_parent;
		head->_parent->_parent = head;
		++Size;

		return Pair<tree_iterator<K, V>, bool>(tree_iterator<K, V>(head->_parent), true);
	}


	Pair<Node*, bool> res = findToPair(p.first);
	if (res.second)//�ҵ���ͬkey
		return Pair<tree_iterator<K, V>, bool>(tree_iterator<K, V>(res.first), false);

	Node* fa = res.first;//Ҫ����ڵ�ĸ��ڵ�
	Node* son = new Node(p);
	//����key�Ĵ�С����fa���ӽ��
	if (p.first < fa->_kv.first)
		fa->_left = son;
	else
		fa->_right = son;
	//head������ָ��min��max
	if (p.first > head->_right->_kv.first)
		head->_right = son;
	else if (p.first < head->_left->_kv.first)
		head->_left = son;
	//��Ҫ���˸��ڵ��ָ��
	son->_parent = fa;

	++Size;//Ԫ�ظ�������
	adjust(son);//����

	return Pair<tree_iterator<K, V>, bool>(tree_iterator<K, V>(son), true);
}

template<class K, class V>
tree_iterator<K, V> RBTree<K, V>::find(const K& key)
{
	Node* cur = head->_parent;//�Ӹ���㿪ʼ��
	//û�н��
	if (cur == head || cur == NULL)
		return tree_iterator<K, V>(NULL);//�Ҳ������ؿ�
	while (cur)
	{
		if (key < cur->_kv.first)
			cur = cur->_left;
		else if (key > cur->_kv.first)
			cur = cur->_right;
		else//�ҵ�key���ֱ�ӷ���
			return tree_iterator<K, V>(cur);
	}
	return tree_iterator<K, V>(NULL);//�Ҳ������ؿ�
}

template<class K, class V>
void RBTree<K, V>::adjust(Node* son)
{
	Node* fa = son->_parent;
	//������Ĭ�Ϻ�ɫ, ���ڵ�ͬ����ɫ��Υ�����������
	if (fa == head)//���ڵ�Ϊͷ���ݹ����
		return;

	if (fa->_color == BLACK)//���ڵ��ɫ, ���õ���
		return;
	//���үү�ڵ������ڵ�
	Node* ffa = fa->_parent;
	Node* uncle = (fa == ffa->_left ? ffa->_right : ffa->_left);

	/*
			 ffa:B              ffa:R
			 / 	 \				/   \
		  fa:R  uncle:R		 fa:B  uncle:B
		  /					  /
		son:R   			son:R
	*/
	if (uncle && uncle->_color == RED)//����ڵ���ڲ��Һ͸��ڵ�һ����
	{
		fa->_color = BLACK;
		uncle->_color = BLACK;
		ffa->_color = RED;
		adjust(ffa);//���ϴ���үү�ڵ�
	}
	else//uncleΪ��
	{

		if (fa == ffa->_left)
		{
			/*
					ffa:B         fa:B
					/  			 /    \
				  fa:R		   son:R  ffa:R
				  /
				son:R
			*/
			if (son == fa->_left)//�������ӽڵ㣬����
			{
				fa->_color = BLACK;//���ڵ���
				ffa->_color = RED;//үү�ڵ���
				//����ffa��parent��fa
				if (ffa == ffa->_parent->_parent)
					ffa->_parent->_parent = fa;
				else if (ffa == ffa->_parent->_right)
					ffa->_parent->_right = fa;
				else
					ffa->_parent->_left = fa;
				//��������
				ffa->_left = fa->_right;
				if (fa->_right)
					fa->_right->_parent = ffa;
				fa->_right = ffa;
				fa->_parent = ffa->_parent;
				ffa->_parent = fa;
			}
			/*
					  ffa:B		    ffa:B
					/ 				/
				   fa:R			  son:R
					  \ 		  /
					  son:R		fa:R
			*/
			else//���ӵ����������һ�����, ��ɵ���fa
			{
				ffa->_left = son;
				son->_parent = ffa;
				fa->_parent = son;
				fa->_right = son->_left;
				if (fa->_right)
					fa->_right->_parent = fa;
				son->_left = fa;
				adjust(fa);
			}
		}
		else
		{
			/*
					ffa:B             fa:B
					   \			 /    \
					   fa:R			fa:R  son:R
						\
						son:R
			*/
			if (son == fa->_right)//�������ӽڵ㣬����
			{
				fa->_color = BLACK;
				ffa->_color = RED;
				if (ffa == ffa->_parent->_parent)
					ffa->_parent->_parent = fa;
				else if (ffa == ffa->_parent->_right)
					ffa->_parent->_right = fa;
				else
					ffa->_parent->_left = fa;
				//��������
				ffa->_right = fa->_left;
				if (fa->_left)
					fa->_left->_parent = ffa;
				fa->_left = ffa;
				fa->_parent = ffa->_parent;
				ffa->_parent = fa;
			}
			/*
					ffa:B           ffa:B
						\				\
						fa:R			son:R
						/				 \
					son:R				 fa:R
			*/
			else//���ӵ����������һ�����, ��ɵ���fa
			{
				ffa->_right = son;
				son->_parent = ffa;
				fa->_parent = son;
				fa->_left = son->_right;
				if (fa->_left)
					fa->_left->_parent = fa;
				son->_right = fa;
				adjust(fa);
			}
		}
	}
}

template<class K, class V>
void RBTree<K, V>::inOrder(Node* root)
{
	if (root)//����ǿգ������������
	{
		inOrder(root->_left);
		cout << root->_kv.first << ' ' << root->_kv.second << endl;
		inOrder(root->_right);
	}
}

template<class K, class V>
void RBTree<K, V>::rotateLeft(Node*& fa)
{
	/*
			 ffa			ffa
			 /				/
			fa            subR
		   /  \			  /  \
			  subR       fa
			  /	 \      /  \
			subRL 		  subRL
	*/
	Node* subR = fa->_right;
	Node* subRL = subR->_left;
	//exchange the childNode
	fa->_right = subRL;
	if (subRL)//�ǿվ����ϸ��ڵ�
		subRL->_parent = fa;
	subR->_left = fa;
	//exchange the parentNode
	Node* ffa = fa->_parent;
	fa->_parent = subR;
	subR->_parent = ffa;

	if (ffa == head)
		head->_parent = subR;
	else
	{
		if (fa == ffa->_left)
			ffa->_left = subR;
		else
			ffa->_right = subR;
	}
}

template<class K, class V>
void RBTree<K, V>::rotateRight(Node*& fa)
{
	/*
			 ffa			ffa
			 /				/
			fa            subL
		   /  \			  /  \
		  subL        		 fa
		  /	 \      		/  \
			subRL 		  subRL
	*/
	Node* subL = fa->_left;
	Node* subLR = subL->_right;
	//exchange the childNode
	fa->_left = subLR;
	if (subLR)
		subLR->_parent = fa;
	subL->_right = fa;
	//exchange the parentNode
	Node* ffa = fa->_parent;
	fa->_parent = subL;
	subL->_parent = ffa;

	if (ffa == head)
		head->_parent = subL;
	else
	{
		if (fa == ffa->_left)
			ffa->_left = subL;
		else
			ffa->_right = subL;
	}
}

template<class K, class V>
void RBTree<K, V>::erase(const K& key)
{
	tree_iterator<K, V> del = find(key);//���ص�����
	if (del.data == NULL)//�Ҳ���Ҫɾ����
		return;
	erase(del);
}

template<class K, class V>
/*
	��ɫ�ڵ�ֱ�Ӱ�AVLɾ��
	��ɫɾ����Ӱ��ڸ���Ҫ����
	1.û���ӽڵ�
	2.ֻ��һ���ӽ��
		ɾ���ڵ�ֻ���Ǻ�ɫ�����ӽڵ�Ϊ��ɫ�������޷����������������ˡ� ��ʱ��ɾ���ڵ���ӽڵ�ӵ����ڵ㣬�ҽ��ӽڵ���ɫͿ�ڣ���֤��ɫ������
	3.�������ӽ��, �ú�̽ڵ���Ϊ�滻��Ҫɾ���Ľڵ�, תΪ���1 2
*/
void RBTree<K, V>::erase(tree_iterator<K, V> it)
{
	Node* rm = it.data;//Ҫɾ���Ľڵ�
	if (rm == head || rm == NULL)//�����ͷ���or��ֱ���˳�
		return;

	Node* succ = NULL;
	Node* rrm = NULL;
	Node* succ_p = rm->_parent;

	//succ��ΪҪɾ���ڵ���е��ӽڵ�
	if (rm->_left == NULL)
		succ = rm->_right;
	else if (rm->_right == NULL)
		succ = rm->_left;
	else//����������
	{
		++it;//ȥ����̽ڵ�
		rrm = it.data;//rrm��¼��̽ڵ�
		succ = rrm->_right;
	}

	if (rrm)//����к�̽ڵ�
	{
		rm->_left->_parent = rrm;
		rrm->_left = rm->_left;
		if (rrm != rm->_right)
		{
			succ_p = rrm->_parent;
			if (succ)
				succ->_parent = succ_p;
			succ_p->_left = succ;
			rrm->_right = rm->_right;
			rm->_right->_parent = rrm;
		}
		else
			succ_p = rrm;
		if (head->_parent == rm)
			head->_parent = rrm;
		else if (rm->_parent->_left == rm)
			rm->_parent->_left = rrm;
		else
			rm->_parent->_right = rrm;
		rrm->_parent = rm->_parent;
		COLOR temp = rrm->_color;
		rrm->_color = rm->_color;
		rm->_color = temp;
	}
	else//û�к�̽ڵ�
	{
		if (succ)
			succ->_parent = rm->_parent;
		if (head->_parent == rm)
			head->_parent = succ;
		else if (rm->_parent->_left == rm)
			rm->_parent->_left = succ;
		else
			rm->_parent->_right = succ;
		if (rm == head->_left)
			head->_left = (rm->_right == NULL ? rm->_parent : mostLeft(succ));
		if (rm == head->_right)
			head->_right = (rm->_left == NULL ? rm->_parent : mostRight(succ));
	}
	if (rm->_color != RED)//Ҫɾ�����Ǻ�ɫ��Ҫ����
	{
		while (succ != head->_parent && (succ == NULL || succ->_color == BLACK))
		{
			if (succ == succ_p->_left)
			{
				Node* s = succ_p->_right;
				if (s->_color == RED)
				{
					s->_color = BLACK;
					succ_p->_color = RED;
					rotateLeft(succ_p);
					s = succ_p->_right;
				}
				if ((s->_left == NULL || s->_left->_color == BLACK) &&
					(s->_right == NULL || s->_right->_color == BLACK))
				{
					s->_color = RED;
					succ = succ_p;
					succ_p = succ->_parent;
				}
				else
				{
					if (s->_right == NULL || s->_right->_color == BLACK)
					{
						s->_left->_color = BLACK;
						s->_color = RED;
						rotateRight(s);
						s = succ_p->_right;
					}
					s->_color = succ_p->_color;
					succ_p->_color = BLACK;
					if (s->_right)
						s->_right->_color = BLACK;
					rotateLeft(succ_p);
					break;
				}
			}
			else
			{
				Node* s = succ_p->_left;
				if (s->_color == RED)
				{
					s->_color = BLACK;
					succ_p->_color = RED;
					rotateRight(succ_p);
					s = succ_p->_left;
				}
				if ((s->_left == NULL || s->_left->_color == BLACK) &&
					(s->_right == NULL || s->_right->_color == BLACK))
				{
					s->_color = RED;
					succ = succ_p;
					succ_p = succ->_parent;
				}
				else
				{
					if (s->_left == NULL || s->_left->_color == BLACK)
					{
						s->_right->_color = BLACK;
						s->_color = RED;
						rotateLeft(s);
						s = succ_p->_left;
					}
					s->_color = succ_p->_color;
					succ_p->_color = BLACK;
					if (s->_left)
						s->_left->_color = BLACK;
					rotateRight(succ_p);
					break;
				}
			}
		}
		if (succ)
			succ->_color = BLACK;
	}

	delete rm;
	--Size;
}


template<class K, class V>
class Map {
private:
	RBTree<K, V> data;
public:
	inline size_t size() const {
		return data.size();
	}
	inline bool empty() const {
		return data.empty();
	}
	tree_iterator<K, V> begin() {
		return data.begin();
	}
	tree_iterator<K, V> end() {
		return data.end();
	}

	Pair<tree_iterator<K, V>, bool> insert(const Pair<K, V>& p) {
		return data.insert(p);
	}

	void erase(const K& key) {
		data.erase(key);
	}

	void erase(const tree_iterator<K, V>& it) {
		data.erase(it);
	}

	V& operator[](const K& key) {
		//�Ȳ��룬���֮ǰ���˾Ͳ���ʧ���ҵ��Ѵ��ڵ�key��Ӧ�ĵ�����
		//���֮ǰû�оͲ����µģ�����V��ֵ��֪��
		auto res = insert(Pair<K, V>(key, V(NULL)));
		return (*res.first).second;
	}

	tree_iterator<K, V> find(const K& key) {
		return data.find(key);
	}

	void clear() {
		data.clear();
	}

	void inOrder() {
		data.inOrder();
	}
};

//���鼯
class unionFind {
public:
	//���캯��
	unionFind() {
		numOfSet = 0;
	}
	unionFind(const int n) {
		fa.resize(n);
		for (int i = 0; i < n; ++i)
			fa[i] = i;
		numOfSet = n;
	}
	void resize(const int n) {
		fa.resize(n);
		for (int i = 0; i < n; ++i)
			fa[i] = i;
		numOfSet = n;
	}
	int find(int x) {
		if (numOfSet == 0)
			return 0;
		while (fa[x] != x) {
			fa[x] = fa[fa[x]];
			x = fa[x];
		}
		return x;
	}
	bool union_xy(int x, int y) {
		int root_x = find(x);
		int root_y = find(y);

		if (root_x == root_y)
			return false;
		fa[root_x] = root_y;
		//��������
		--numOfSet;
		return true;
	}
	bool is_connected(int x, int y) {
		return find(x) == find(y);
	}
	inline int getNumOfSet()const {
		return numOfSet;
	}
	void clear() {
		fa.clear();
		numOfSet = 0;
	}
private:
	Vector<int> fa;
	int numOfSet;
};

//�߽��
struct edge {
	int first, second, val;
	//�������ȶ��д���С���෴����
	friend bool operator>(const edge& a, const edge& b) {
		return a.val < b.val;
	}
	friend bool operator<(const edge& a, const edge& b) {
		return a.val > b.val;
	}
};

void heapify1(edge* nums, int start, int end)//[beg, end]
{
	int dad = start, son = 2 * dad + 1;
	while (son <= end)
	{
		//ȡ����Ǹ�����
		if ((son + 1) <= end && nums[son] < nums[son + 1])
			++son;
		if (nums[son] < nums[dad])//dad��son��ֱ�ӽ�������ΪҪ����top���
			return;
		//С��nums[dad]�³����ϴ���ӽ���λ��
		edge t = nums[dad];
		nums[dad] = nums[son];
		nums[son] = t;

		dad = son;//������������ӽ��
		son = dad * 2 + 1;
	}
}

void Sort(edge* nums, int size)
{
	//��ʼ���ѣ������һ����Ҷ�ӽ����ǰ
	for (int i = (size - 1) / 2; i >= 0; --i)
		heapify1(nums, i, size - 1);
	//�����򣬽��Ѿ��źõĶ� top �ŵ�����൱�ڳ��ѣ�
	for (int i = size - 1; i > 0; --i)
	{
		edge t = nums[0];
		nums[0] = nums[i];
		nums[i] = t;

		heapify1(nums, 0, size - 1);
	}
}



//����ģ��ϵͳ
class elecSys {
private:
	//�����������string��Ӧ��int��֮���ٽ��д�ͼ
	Vector<edge> edges;
	Map<String, int> hash;
	Vector<String> node;
	Vector<Vector<int>> adj;
	//������С�������ߵļ���
	Vector<edge> ansEdge;
	//��¼�Ƿ����е㶼������һ��
	unionFind uf;
	//������
	int tot;
	//��С����������
	int cost;
	//��С���������
	int start;
	//����Ƿ����е㶼������
	bool edgeFinish;
	//�������
	void clear();
public:
	//���캯��
	elecSys() {
		tot = 0;
		cost = 0;
		start = 0;
		edgeFinish = false;
	}

	//��������
	~elecSys() {}

	//���������������
	void buildNode();

	//��ӵ����ı�
	void addEdges();

	//������С��������ʾ
	void buildTree();

	//Prim�㷨������С������
	void  Prim();

	//Prim�㷨���ȶ��а汾
	void PrimPriorityQueue();

	int Kruskal();

	//��ʾ��С������
	void show();
};



#endif // !_ELESYSTEM_H

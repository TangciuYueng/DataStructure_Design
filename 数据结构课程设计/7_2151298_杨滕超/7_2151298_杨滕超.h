#ifndef _WOODCUT_H
#define _WOODCUT_H


#include <iostream>
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

#endif // !_WOODCUT_H

#ifndef _LIST_INTERSECTION_H
#define _LIST_INTERSECTION_H


#include <iostream>


using namespace std;


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

#endif // !_LIST_INTERSECTION_H


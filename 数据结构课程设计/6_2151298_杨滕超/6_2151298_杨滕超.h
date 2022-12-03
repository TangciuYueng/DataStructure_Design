#ifndef _FAMILY_TREE_H
#define _FAMILY_TREE_H

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


//28��������Ϊhashtable��size
const int primeNum = 28;
static const unsigned long primeList[primeNum] =
{
  53ul,         97ul,         193ul,       389ul,       769ul,
  1543ul,       3079ul,       6151ul,      12289ul,     24593ul,
  49157ul,      98317ul,      196613ul,    393241ul,    786433ul,
  1572869ul,    3145739ul,    6291469ul,   12582917ul,  25165843ul,
  50331653ul,   100663319ul,  201326611ul, 402653189ul, 805306457ul,
  1610612741ul, 3221225473ul, 4294967291ul
};
//���ش���n����С���������ݵ�ʱ����Ҫ
inline unsigned long getNextPrime(unsigned long num)
{
	if (num == 4294967291ul)//���һλ������û����һλ��
		return num;
	//���ֲ���
	int l = 0, r = primeNum - 1;
	while (l < r)
	{
		int mid = (l + r) >> 1;//���Ƴ��Զ�
		if (primeList[mid] <= num)
			l = mid;
		else
			r = mid - 1;
	}
	//���ظ����ֵ���һλ
	return primeList[l + 1];
}

//��ϣ���еĽ��
template<class K, class V>
struct hashNode {
	pair<K, V> kv;
	hashNode<K, V>* next;
	hashNode(const pair<K, V>& _kv, hashNode<K, V>* _next = NULL)
		:kv(_kv), next(_next) {}
};

template<class K>
struct hashfunc {
	size_t operator()(const K& key) {
		return key;
	}
};

template<>
struct hashfunc<String> {
	size_t operator()(const String& str) {
		size_t hash = 0;
		size_t Size = str.length() + 1;
		for (size_t i = 0; i < Size; ++i) {
			hash *= 31;
			hash += str.c_str()[i];
		}
		return hash;
	}
};

template<>
struct hashfunc<string> {
	size_t operator()(const string& str) {
		size_t hash = 0;
		for (size_t i = 0; i < str.length() + 1; ++i) {
			hash *= 31;
			hash += str[i];
		}
		return hash;
	}
};

template<class K, class V, class Func = hashfunc<K>>
class hashtable {
	typedef hashNode<K, V> Node;
public:
	//���캯��
	hashtable();
	hashtable(const size_t sz);
	//��������
	~hashtable();
	//����
	Node* find(const K& key);
	//����
	void insert(const pair<K, V>& p);
	//ɾ��
	void erase(const K& key);
	//�ж��Ƿ�Ϊ��
	bool empty() const {
		return Size == 0;
	}
	//����Ԫ�ظ���
	bool size() const {
		return Size;
	}
private:
	//���ź���
	void expand();

	Node** table = NULL;
	size_t Size = 0;
	size_t capacity = 0;
	Func hf;
};

//���캯��
template<class K, class V, class Func>
hashtable<K, V, Func>::hashtable() {
	capacity = 53ul;
	table = new(nothrow) Node * [capacity];
	if (table == NULL)
		exit(1);
	for (size_t i = 0; i < capacity; ++i)
		table[i] = NULL;
}

template<class K, class V, class Func>
hashtable<K, V, Func>::hashtable(const size_t sz) {
	capacity = getNextPrime(sz);//ʵ�ʻ��sz����һ������
	table = new(nothrow) Node * [capacity];
	if (table == NULL)
		exit(1);
	for (size_t i = 0; i < capacity; ++i)
		table[i] = NULL;
}

//��������
template<class K, class V, class Func>
hashtable<K, V, Func>::~hashtable() {
	Node* cur = NULL, * temp = NULL;
	for (size_t i = 0; i < capacity; ++i)
	{
		cur = table[i];
		while (cur) {
			temp = cur->next;
			delete cur;
			cur = temp;
		}
	}
	delete[] table;
}

//���Һ���
template<class K, class V, class Func>
hashNode<K, V>* hashtable<K, V, Func>::find(const K& key) {
	size_t index = hf(key) % capacity;
	Node* cur = table[index];
	while (cur) {
		if (cur->kv.first == key)
			break;
		cur = cur->next;
	}
	return cur;
}

//ɾ������
template<class K, class V, class Func>
void hashtable<K, V, Func>::erase(const K& key) {
	size_t index = hf(key) % capacity;
	Node* cur = table[index], * prev = NULL;
	while (cur) {
		if (cur->kv.first == key)
			break;
		prev = cur;
		cur = cur->next;
	}

	if (cur == NULL)//û���ҵ�Ҫɾ����
		return;

	if (prev == NULL)//Ҫɾ�����ǵ�һ��
	{
		table[index] = cur->next;
		delete cur;
	}
	else
	{
		prev = cur->next;
		delete cur;
	}
	--Size;
}

//���ź���
template<class K, class V, class Func>
void hashtable<K, V, Func>::expand() {
	size_t newCapacity = getNextPrime(capacity);
	Node** newTable = new(nothrow) Node * [newCapacity];
	if (newTable == NULL)
		exit(1);
	for (size_t i = 0; i < newCapacity; ++i)
		newTable[i] = NULL;

	for (size_t i = 0; i < capacity; ++i)
	{
		Node* cur = table[i];

		while (cur) {
			size_t index = hf(cur->kv.first) % capacity;
			//��ͷ
			cur->next = newTable[index];
			newTable[index] = cur;
		}
	}
	delete[] table;
	table = newTable;
	capacity = newCapacity;
}

//���뺯��
template<class K, class V, class Func>
void hashtable<K, V, Func>::insert(const pair<K, V>& p) {
	if (Size * 100 / capacity > 70)
		expand();

	size_t index = hf(p.first) % capacity;
	Node* newNode = new Node(p, table[index]);
	table[index] = newNode;

	++Size;
}

//�������Ľ�㣬�����ֺͺ���
struct familyTreeNode {
	String id;
	Vector<familyTreeNode*> children;
	familyTreeNode(String& id) :id(id) {}
};

//��������
class familyTree {
private:
	//�����
	familyTreeNode* root;

	//һ�����ٸ����
	int Size;

	//ͨ�����ֵݹ�Ѱ��
	familyTreeNode* search(String& id, familyTreeNode* cur);

	//ͨ��hashtableѰ��
	familyTreeNode* _search(String& id);

	//�ݹ�ɾ������
	void removeChildren(familyTreeNode* cur);

	//����ɾ������
	void _removeChildren(familyTreeNode* cur);

	//hash���ѯ�Ƿ��ڼ������У����� <���֣��ڵ��ַ> �ļ�ֵ��
	hashtable<String, familyTreeNode*> ht;

public:
	//���캯��
	familyTree();

	//��������
	~familyTree();

	//���Ƽ���
	void buildFamily();

	//�����Ů
	void addChild();

	//��������
	void changeId();

	//��ɢ��ͥ��û����Ů
	void removeChildren();

	//չʾ
	void show();
};

#endif // !_FAMILY_TREE_H

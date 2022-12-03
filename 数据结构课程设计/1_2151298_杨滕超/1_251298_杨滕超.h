#ifndef _STUDENT_H
#define _STUDENT_H

#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;


//链表节点
template<class T>
struct list_node {
	T val;
	list_node* prev, * next;
	list_node() {
		prev = NULL;
		next = NULL;
	}
	//构造函数
	list_node(const T& val, list_node* prev = NULL, list_node* next = NULL) :
		val(val), prev(prev), next(next) {}
};

//precious declare the class has template
//so that in the list<T> we can friend class Stack<T>
template<class T>
class Stack;

template<class T>
class Queue;

//双向链表实现
template<class T>
class List {
	typedef list_node<T>* _iterator;
	//	template<class T>
	friend class Stack<T>;
	//	template<class T>
	friend class Queue<T>;
private:
	//头结点 尾结点
	list_node<T>* head, * tail;

	//结点个数
	int Size;

	//归并递归函数
	list_node<T>* _mergeSort(list_node<T>* head);

	//从from开始切断step结点，并返回最后一个
	list_node<T>* cut(list_node<T>* from, int step);

	//归并排序的合并
	list_node<T>* merge(list_node<T>* l1, list_node<T>* l2);

public:
	//构造函数
	List();

	//析构函数
	~List();

	//返回链表大小
	inline int size() const {
		return Size;
	}

	//判断链表是否为空
	inline bool empty() const {
		return head == tail;
	}

	//得到头结点
	inline list_node<T>* getHead() const {
		return head;
	}

	//得到尾节点
	inline list_node<T>* getTail() const {
		return tail;
	}

	//清空链表
	void clear();

	//最后添加元素
	void emplace_back(const T& x);

	//最后删除元素
	void pop_back();

	//开头添加元素
	void emplace_front(const T& x);

	//开头删除元素
	void pop_front();

	//重载=
	List<T>& operator=(const List<T>& L);

	//链表迭代器
	class list_iterator {
		friend class List<T>;
	private:
		//指向节点的指针
		_iterator data;
	public:
		//构造函数
		list_iterator(_iterator data) {
			this->data = data;
		}
		list_iterator(const T& x) {
			data = new list_node<T>(x);
		}
		//重载*
		T& operator*() {
			return data->val;
		}
		//重载->
		T* operator->() {
			return &(data->val);
		}
		//重载==
		inline bool operator==(const list_iterator& it) const {
			return this->data == it.data;
		}
		//重载!=
		inline bool operator!=(const list_iterator& it) const {
			return this->data != it.data;
		}
		//重载自加
		inline List<T>::list_iterator& operator++()
		{
			if (data != NULL)
				data = data->next;
			return *this;
		}
		//重载自减
		inline List<T>::list_iterator& operator--()
		{
			if (data != NULL)
				data = data->prev;
			return *this;
		}
		//后置自加
		List<T>::list_iterator operator++(int)
		{
			List<T>::list_iterator temp = *this;
			++(*this);
			return temp;
		}
		//后置自减
		List<T>::list_iterator operator--(int)
		{
			List<T>::list_iterator temp = *this;
			--(*this);
			return temp;
		}
		//与数字相加
		List<T>::list_iterator operator+(int num)
		{
			List<T>::list_iterator temp = *this;
			for (int i = 0; i < num; ++i)
				++temp;
			return temp;
		}
		//与数字相减
		List<T>::list_iterator operator-(int num)
		{
			List<T>::list_iterator temp = *this;
			for (int i = 0; i < num; ++i)
				--temp;
			return temp;
		}
		//自加
		List<T>::list_iterator operator+=(int num)
		{
			for (int i = 0; i < num; ++i)
				++(*this);
			return *this;
		}
		//自减
		List<T>::list_iterator operator-=(int num)
		{
			for (int i = 0; i < num; ++i)
				--(*this);
			return *this;
		}
		//两个相减
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

	//复制构造函数
	List(const List<T>& L);

	//插入
	void insert(const List<T>::list_iterator& it, const T& x);

	//删除
	void remove(const List<T>::list_iterator& it);

	//迭代器begin
	inline List<T>::list_iterator begin() {
		return List<T>::list_iterator(head->next);
	}

	//迭代器end
	inline List<T>::list_iterator end() {
		return List<T>::list_iterator(tail->next);
	}

	//返回迭代器的查找
	typename List<T>::list_iterator find(const T& x);

	//递归排序
	void mergeSort1() {
		if (head->next == NULL)//没有元素
			return;
		//排序没有头的进入排序函数
		head->next = _mergeSort(head->next);
		list_node<T>* cur = head->next;
		//找最后一个结点
		while (cur->next)
			cur = cur->next;
		//出来是最后一个结点
		tail = cur;
	}

	//迭代排序
	void mergeSort2();
};

//构造函数
template<class T>
List<T>::List()
{
	head = new list_node<T>();
	tail = head;
	Size = 0;
}

//赋值构造函数
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

//析构函数
template<class T>
List<T>::~List() {
	clear();
	delete head;
}

//清空链表
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

//最后添加元素
template<class T>
void List<T>::emplace_back(const T& x)
{
	//申请新的空间
	list_node<T>* node = new list_node<T>(x);
	++Size;//元素个数更新
	//连接最后一个
	tail->next = node;
	node->prev = tail;
	//尾结点更新
	tail = node;
}

//最后删除元素
template<class T>
void List<T>::pop_back()
{
	if (empty())//空了就不能删除
		return;
	--Size;//元素个数减少
	list_node<T>* temp = tail->prev;
	delete tail;
	tail = temp;
	tail->next = NULL;//尾结点的收尾
}

//开头添加元素
template<class T>
void List<T>::emplace_front(const T& x)
{
	list_node<T>* node = new list_node<T>(x);
	++Size;//元素个数增加
	if (empty())//链表为空注意更新尾结点
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

//删除开头元素
template<class T>
void List<T>::pop_front()
{
	if (empty())//空了就不能删除
		return;
	--Size;//元素个数减少
	//要删除的节点的下一个
	list_node<T>* temp = head->next->next;
	list_node<T>* del = head->next;
	delete del;
	head->next = temp;
	if (temp)//如果下一个不为空
		temp->prev = head;
	else//下一个为空，更新尾结点指向头结点
		tail = head;
}

//利用迭代器插入
template<class T>
void List<T>::insert(const List<T>::list_iterator& it, const T& x)
{
	if (it.data == NULL)
		return;
	//有迭代器提供可插入位置，不可能改变尾结点
	list_node<T>* temp = it.data;

	temp->prev->next = new list_node<T>(x, temp->prev, temp);
	temp->prev = temp->prev->next;

	++Size;
}

//利用迭代器删除
template<class T>
void List<T>::remove(const List<T>::list_iterator& it)
{
	if (it.data == NULL)//迭代器为空
		return;

	list_node<T>* temp = it.data;
	//尾结点的特判
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
	--Size;//元素个数减少
}

//重载赋值
template<class T>
List<T>& List<T>::operator=(const List<T>& L)
{
	clear();//先清空原来结点
	list_node<T>* cur = L.getHead()->next;
	while (cur)
	{
		emplace_back(cur->val);
		cur = cur->next;
	}

	return *this;
}

//查询是否有值
template<class T>
typename List<T>::list_iterator List<T>::find(const T& x)
{
	for (auto it = begin(); it != end(); ++it)
		if (*it == x)
			return it;
	return NULL;
}

//递归归并排序
template<class T>
list_node<T>* List<T>::_mergeSort(list_node<T>* head)
{
	//没有结点或只有空结点，直接返回
	if (head == NULL || head->next == NULL)
		return head;

	list_node<T>* slow = head, * fast = head, * prev = NULL;
	//快慢指针找中间
	while (fast && fast->next)
	{
		prev = slow;
		slow = slow->next;
		fast = fast->next->next;
	}

	//断开中间，分成两端
	prev->next = NULL;

	list_node<T>* p1, * p2, * D = new list_node<T>(0), * p3 = D;
	p1 = _mergeSort(head);
	p2 = _mergeSort(slow);
	//合并
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
	//剩下的一条链
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
	p3->next = NULL;//收尾工作

	list_node<T>* ans = D->next;
	//释放空间
	delete D;
	return ans;
}

//迭代归并排序
template<class T>
void List<T>::mergeSort2()
{
	//只有一个或没有结点
	if (head->next == NULL || head->next->next == NULL)
		return;

	list_node<T>* cur;

	for (int step = 1; step < Size; step *= 2)//间隔不断乘2
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
		tail = tempTail;//更新尾结点
	}
}

//从from开始切掉前step个元素，返回最后一个元素
template<class T>
list_node<T>* List<T>::cut(list_node<T>* from, int step)
{
	--step;
	while (from && step)
	{
		from = from->next;
		--step;
	}
	//不够step个元素
	if (from == NULL)
		return NULL;
	list_node<T>* next = from->next;
	//切断
	from->next = NULL;
	return next;
}

//合并函数，两条有序链合并为一条有序链
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
	cur->next = NULL;//收尾工作
	list_node<T>* ans = D->next;
	delete D;
	return ans;
}


//默认申请空间大小50个char
const int defaultSizeString = 50;

class String {
private:
	//指向尾零的位置，初始化时候注意Size = 1
	int Size;

	//实际容量
	int capacity;

	//数据数组
	char* data;

	//容量扩张defaultSizeString
	void expand();

	//模式串匹配得到next数组函数
	void getNext(const char* str, int* next, int len);
public:
	//空构造函数
	String();

	//赋值构造函数
	String(const String& str);

	//字符串构造函数
	String(const char* str);

	//大小为size的字符串构造函数
	String(const char* str, int size);

	//析构函数
	~String();

	//字符串长度
	int length()const {
		//减去的是尾零
		return Size - 1;
	}

	//计算字符串长度，与实例化对象无关，声明为静态成员函数
	static int strLen(const char* str);

	//重载=，Stirng
	String& operator=(const String& str);

	//重载=，字符串
	String& operator=(const char* str);

	//重载=，一个字符
	String& operator=(const char& ch);

	//重载<<
	friend ostream& operator<<(ostream& out, const String& str) {
		out << str.data;
		return out;
	}

	//重载>>
	friend istream& operator>>(istream& in, String& str) {
		//这里存在问题，输入太多字符该如何是好
		in >> str.data;
		str.Size = str.strLen(str.data) + 1;
		return in;
	}

	//重载比较函数
	friend int strCmp(const String& str1, const String& str2)
	{
		int i = 0;
		while (str1.data[i] && str2.data[i])
		{
			//出现了不同的，返回相同位置第一个减第二个
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
	//重载< > <= >=
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
		data[Size - 1] = '\0';//之前尾零前的字符放上尾零
	}

	//获得最后一个字符
	char back() const {
		if (Size <= 1)
			return '\0';
		return data[Size - 2];
	}

};
//构造函数
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

//析构函数
String::~String() {
	delete[] data;
}

//字符串长度
int String::strLen(const char* str)
{
	int size = 0;
	while (str[size] != '\0')
		++size;
	return size;
}

//容量扩张defaultSizeString
void String::expand()
{
	capacity += defaultSizeString;
	char* newData = new char[capacity];
	for (int i = 0; i < Size && Size < capacity; ++i)
		newData[i] = data[i];
	delete[] data;
	data = newData;
}

//重载=
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

//重载==
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

//重载+
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

//重载+=
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

//模式串匹配
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

//删除所有值为ch的
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
}

//翻转
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

//清空
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


//Pair二元组类
template<class T1, class T2>
class Pair {
public:
	T1 first;
	T2 second;
public:
	//构造函数
	Pair() :first(T1()), second(T2()) {}
	Pair(const T1& first, const T2& second) {
		this->first = first;
		this->second = second;
	}

	Pair(const Pair<T1, T2>& P) {
		this->first = P.first;
		this->second = P.second;
	}
	//兼容性的复制构造函数
	template<class U1, class U2>
	Pair(const Pair<U1, U2>& P) :first(P.first), second(P.second) {}
	//重载运算符
	Pair& operator=(const Pair<T1, T2>& P)
	{
		first = P.first;
		second = P.second;
		return *this;
	}
	//都写成友元函数，将两个都const限定 
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


enum COLOR {
	RED, BLACK
};

/*
	红黑树节点
	定义颜色代替了avl树的平衡因子
	插入新节点默认为红色，如果与父节点连续红色破坏就调整
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
		//根据中序遍历的后一个, 比当前data的_kv.first大的第一个
		if (data->_right)//有右结点
		{
			data = data->_right;
			while (data->_left)
				data = data->_left;
		}
		else//没有右结点，就找父节点
		{
			Node* fa = data->_parent;
			while (data == fa->_right)//是父节点的右子树
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
		//中序匾历的上一个
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

//红黑树
template<class K, class V>
class RBTree {
	typedef RBTreeNode<K, V> Node;
	typedef tree_iterator<K, V> Iterator;
private:
	//头结点，父结点为root，left为最小，right为最大
	Node* head;
	//记录红黑树中插入了多少元素
	size_t Size;
public:
	//构造函数
	RBTree();
	//析构函数
	~RBTree() {
		clear();
		delete head;
	}
	//判断是否为空
	inline bool empty() const {
		return Size == 0;
	}
	//返回红黑树的元素个数
	inline size_t size() const {
		return Size;
	}
	//返回第一个元素的迭代器
	inline Iterator begin() {
		return Iterator(head->_left);
	}
	//返回最后一个后面的
	inline Iterator end() {
		return head;
	}
	//返回根结点
	inline Node* getRoot() {
		return head->_parent;
	}
	//返回头结点
	inline Node* getHead() const {
		return head;
	}
	//插入函数，参数为Pair键值对
	Pair<Iterator, bool> insert(const Pair<K, V>& p);
	//利用迭代器删除
	void erase(Iterator it);
	//利用key删除
	void erase(const K& key);
	//查找，利用key，返回迭代器
	Iterator find(const K& key);
	//找关键码最小的结点
	static Node* mostLeft(Node* cur)
	{
		while (cur->_left)
			cur = cur->_left;
		return cur;
	}
	//找关键码最大的结点
	static Node* mostRight(Node* cur)
	{
		while (cur->_right)
			cur = cur->_right;
		return cur;
	}
	//中序遍历
	void inOrder() {
		inOrder(getRoot());
	}
	//清空红黑树
	void clear();
private:
	void inOrder(Node* root);
	void adjust(Node* son);
	void clear(Node* cur);
	void rotateLeft(Node*& fa);
	void rotateRight(Node*& fa);
	Pair<Node*, bool> findToPair(const K& key);
};

//构造函数
template<class K, class V>
RBTree<K, V>::RBTree()
{
	//为头结点申请空间
	head = new Node();
	//初始化头结点的指向
	head->_left = head;
	head->_right = head;
	head->_parent = head;
	//初始化元素个数
	Size = 0;
}


template<class K, class V>
void RBTree<K, V>::clear()
{
	//删除除了头结点的所有结点
	clear(head->_parent->_left);
	clear(head->_parent->_right);
	//头结点指向初始化
	head->_left = head;
	head->_right = head;
	head->_parent = head;
	Size = 0;//元素个数初始化
}

template<class K, class V>
void RBTree<K, V>::clear(Node* cur)
{
	if (cur == NULL || cur == head)//递归结束
		return;

	clear(cur->_left);//删除左子节点
	clear(cur->_right);//删除右子结点

	delete cur;//删除自己
	cur = NULL;//置空
}

template<class K, class V>
Pair<RBTreeNode<K, V>*, bool> RBTree<K, V>::findToPair(const K& key)
{
	if (head->_parent == head)//空树
		return Pair<RBTreeNode<K, V>*, bool>(NULL, false);
	//从根节点开始寻找
	Node* cur = head->_parent;
	//记录结果
	Pair<RBTreeNode<K, V>*, bool> res(NULL, false);

	while (cur)
	{
		//记录父节点, 或要找的节点
		res.first = cur;
		if (key < cur->_kv.first)
			cur = cur->_left;
		else if (key > cur->_kv.first)
			cur = cur->_right;
		else//找到key相同的, 返回该节点
			return Pair<RBTreeNode<K, V>*, bool>(cur, true);
	}
	//找不到返回最后找的父节点, 记录可插入位置
	return res;
}

template<class K, class V>
Pair<tree_iterator<K, V>, bool> RBTree<K, V>::insert(const Pair<K, V>& p)
{
	if (head->_parent == head)//空树, 插入作为根结点
	{
		head->_parent = new Node(p);
		head->_left = head->_parent;
		head->_right = head->_parent;
		head->_parent->_parent = head;
		++Size;

		return Pair<tree_iterator<K, V>, bool>(tree_iterator<K, V>(head->_parent), true);
	}


	Pair<Node*, bool> res = findToPair(p.first);
	if (res.second)//找到相同key
		return Pair<tree_iterator<K, V>, bool>(tree_iterator<K, V>(res.first), false);

	Node* fa = res.first;//要插入节点的父节点
	Node* son = new Node(p);
	//根据key的大小插入fa的子结点
	if (p.first < fa->_kv.first)
		fa->_left = son;
	else
		fa->_right = son;
	//head的左右指向min，max
	if (p.first > head->_right->_kv.first)
		head->_right = son;
	else if (p.first < head->_left->_kv.first)
		head->_left = son;
	//不要忘了父节点的指向
	son->_parent = fa;

	++Size;//元素个数增加
	adjust(son);//调整

	return Pair<tree_iterator<K, V>, bool>(tree_iterator<K, V>(son), true);
}

template<class K, class V>
tree_iterator<K, V> RBTree<K, V>::find(const K& key)
{
	Node* cur = head->_parent;//从根结点开始找
	//没有结点
	if (cur == head || cur == NULL)
		return tree_iterator<K, V>(NULL);//找不到返回空
	while (cur)
	{
		if (key < cur->_kv.first)
			cur = cur->_left;
		else if (key > cur->_kv.first)
			cur = cur->_right;
		else//找到key相等直接返回
			return tree_iterator<K, V>(cur);
	}
	return tree_iterator<K, V>(NULL);//找不到返回空
}

template<class K, class V>
void RBTree<K, V>::adjust(Node* son)
{
	Node* fa = son->_parent;
	//插入结点默认红色, 父节点同样红色就违反红黑树性质
	if (fa == head)//父节点为头结点递归结束
		return;

	if (fa->_color == BLACK)//父节点黑色, 不用调整
		return;
	//获得爷爷节点和叔叔节点
	Node* ffa = fa->_parent;
	Node* uncle = (fa == ffa->_left ? ffa->_right : ffa->_left);

	/*
			 ffa:B              ffa:R
			 / 	 \				/   \
		  fa:R  uncle:R		 fa:B  uncle:B
		  /					  /
		son:R   			son:R
	*/
	if (uncle && uncle->_color == RED)//叔叔节点存在并且和父节点一样红
	{
		fa->_color = BLACK;
		uncle->_color = BLACK;
		ffa->_color = RED;
		adjust(ffa);//向上处理爷爷节点
	}
	else//uncle为空
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
			if (son == fa->_left)//都是左子节点，右旋
			{
				fa->_color = BLACK;//父节点变黑
				ffa->_color = RED;//爷爷节点变红
				//连接ffa的parent和fa
				if (ffa == ffa->_parent->_parent)
					ffa->_parent->_parent = fa;
				else if (ffa == ffa->_parent->_right)
					ffa->_parent->_right = fa;
				else
					ffa->_parent->_left = fa;
				//右旋操作
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
			else//父子调换，变成上一种情况, 变成调整fa
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
			if (son == fa->_right)//都是右子节点，左旋
			{
				fa->_color = BLACK;
				ffa->_color = RED;
				if (ffa == ffa->_parent->_parent)
					ffa->_parent->_parent = fa;
				else if (ffa == ffa->_parent->_right)
					ffa->_parent->_right = fa;
				else
					ffa->_parent->_left = fa;
				//左旋操作
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
			else//父子调换，变成上一种情况, 变成调整fa
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
	if (root)//如果非空，继续中序遍历
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
	if (subRL)//非空就连上父节点
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
	tree_iterator<K, V> del = find(key);//返回迭代器
	if (del.data == NULL)//找不到要删除的
		return;
	erase(del);
}

template<class K, class V>
/*
	红色节点直接按AVL删除
	黑色删除会影响黑高需要调整
	1.没有子节点
	2.只有一个子结点
		删除节点只能是黑色，其子节点为红色，否则无法满足红黑树的性质了。 此时用删除节点的子节点接到父节点，且将子节点颜色涂黑，保证黑色数量。
	3.有两个子结点, 用后继节点作为替换的要删除的节点, 转为情况1 2
*/
void RBTree<K, V>::erase(tree_iterator<K, V> it)
{
	Node* rm = it.data;//要删除的节点
	if (rm == head || rm == NULL)//如果是头结点or空直接退出
		return;

	Node* succ = NULL;
	Node* rrm = NULL;
	Node* succ_p = rm->_parent;

	//succ作为要删除节点的有的子节点
	if (rm->_left == NULL)
		succ = rm->_right;
	else if (rm->_right == NULL)
		succ = rm->_left;
	else//有左右子树
	{
		++it;//去到后继节点
		rrm = it.data;//rrm记录后继节点
		succ = rrm->_right;
	}

	if (rrm)//如果有后继节点
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
	else//没有后继节点
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
	if (rm->_color != RED)//要删除的是黑色，要调整
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
		//先插入，如果之前有了就插入失败找到已存在的key对应的迭代器
		//如果之前没有就插入新的，但是V的值不知道
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



//考生系统类
class StudentSystem;

//考生类
class Stu {
	friend class StudentSystem;
private:
	String name, type, gender;//自己写的string类
	String num;//考号
	unsigned int age;//正整数储存年龄
public:
	//构造函数
	Stu() :num(""), name(""), gender("male"), age(0), type("") {

	}
	//赋值构造函数
	Stu(const Stu& s)
		:num(s.num), name(s.name), gender(s.gender), age(s.age), type(s.type) {

	}
	//重载输入输出流运算符
	friend istream& operator>>(istream& in, Stu& s) {
		in >> s.num >> s.name >> s.gender >> s.age >> s.type;
		return in;
	}
	friend ostream& operator<<(ostream& out, const Stu& s) {
		const int WIDTH = 11;
		out.width(WIDTH);//设置宽度
		out.setf(ios::left);//设置左对齐
		out << s.num;

		out.width(WIDTH + 2);
		out << s.name.c_str();

		out.width(WIDTH);
		out << s.gender.c_str();

		out.width(WIDTH - 3);
		out << s.age;

		out.width(WIDTH);
		out << s.type.c_str() << endl;

		return out;
	}
	//重载==
	bool operator==(const Stu& s) {
		return num == s.num;
	}

};


//考生系统
class StudentSystem {
private:
	List<Stu> data;
	void insertProperly(Stu& s);
	//内部查找函数，返回迭代器
	List<Stu>::list_iterator mySearch(const Stu& s);
	List<Stu>::list_iterator mySearch(const String& num);
public:
	//构造函数
	StudentSystem() {
		;
	}
	//析构函数
	~StudentSystem() {
		;
	}
	//初始化
	bool ini();
	//系统数据size
	inline int size()const {
		return data.size();
	}
	//查找
	void search();
	//插入
	void insert();
	//修改
	void change();
	//保存入文件
	void save();
	//删除
	void remove();
	//统计
	void statistics();
	//展示
	void show();
	//输入回车
	void to_be_continue();
};
#endif // !_STUDENT_H

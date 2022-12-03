#ifndef _KEYACTIVITY_H
#define _KEYACTIVITY_H

#include <iostream>
#include <climits>

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


//链式队列类
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
	//迭代器类型
	typedef T* iterator;
private:
	//元素个数
	int Size;

	//实际容量
	int capacity;

	//内部数组
	T* data;

	//扩容函数
	void expand();
public:
	//构造函数
	Vector();
	Vector(int size);
	Vector(const Vector<T>& V);
	Vector(int size, const T& val);

	//析构函数
	~Vector();

	//返回元素个数
	inline int size() const {
		return Size;
	}

	//判断数组是否为空
	inline bool empty() const {
		return Size == 0;
	}

	//Vector迭代器
	class vector_iterator {
		friend class Vector<T>;
	private:
		iterator data;
	public:
		typedef T value_type;
		vector_iterator(iterator data) :data(data) {}
		//重载*
		T& operator*() {
			return *data;
		}
		T* operator->() {
			return data;
		}
		//重载==
		inline bool operator==(const vector_iterator& it) const {
			return this->data == it.data;
		}
		//重载!=
		inline bool operator!=(const vector_iterator& it) const {
			return this->data != it.data;
		}
		//重载不等号
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
		//重载自加
		inline Vector<T>::vector_iterator& operator++()
		{
			if (data != NULL)
				++data;
			return *this;
		}
		//重载自减
		inline Vector<T>::vector_iterator& operator--()
		{
			if (data != NULL)
				--data;
			return *this;
		}
		//后置自加
		Vector<T>::vector_iterator operator++(int)
		{
			Vector<T>::vector_iterator temp = *this;
			++(*this);
			return temp;
		}
		//后置自减
		Vector<T>::vector_iterator operator--(int)
		{
			Vector<T>::vector_iterator temp = *this;
			--(*this);
			return temp;
		}
		//与数字相加
		friend Vector<T>::vector_iterator operator+(const vector_iterator& it, int num)
		{
			Vector<T>::vector_iterator temp = it;
			for (int i = 0; i < num; ++i)
				++temp;
			return temp;
		}
		//与数字相减
		friend Vector<T>::vector_iterator operator-(const vector_iterator& it, int num)
		{
			Vector<T>::vector_iterator temp = it;
			for (int i = 0; i < num; ++i)
				--temp;
			return temp;
		}
		//自加
		Vector<T>::vector_iterator operator+=(int num)
		{
			for (int i = 0; i < num; ++i)
				++(*this);
			return *this;
		}
		//自减
		Vector<T>::vector_iterator operator-=(int num)
		{
			for (int i = 0; i < num; ++i)
				--(*this);
			return *this;
		}
		//两个相减
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

	//清空Vector
	void clear();

	//最后添加元素
	void emplace_back(const T& x);

	//最后删除元素
	void pop_back();

	//返回最后元素
	const T back() const {
		return data[Size - 1];
	}
	T& back() {
		return data[Size - 1];
	}

	//返回开头元素
	const T front() const {
		return data[0];
	}
	T& front() {
		return data[0];
	}

	//插入
	void insert(const Vector<T>::vector_iterator& it, const T& x);


	//删除
	void remove(const Vector<T>::vector_iterator& it);

	//迭代器begin
	inline Vector<T>::vector_iterator begin() {
		if (Size == 0)
			return NULL;
		return vector_iterator(data);
	}
	//迭代器end
	inline Vector<T>::vector_iterator end() {
		if (Size == 0)
			return NULL;
		return vector_iterator(data + Size);
	}

	//返回迭代器的查找
	typename Vector<T>::vector_iterator find(const T& x);

	//重载[]
	T& operator[](const int index) {
		return data[index];
	}

	//重载=
	Vector<T>& operator=(const Vector<T>& V);

	//重新设置大小
	void resize(int size);
	void resize(int size, const T& val);
};

//构造函数
template<class T>
Vector<T>::Vector()
{
	Size = 0;
	capacity = defaultSize;
	data = new T[capacity];
}

//指定大小构造函数
template<class T>
Vector<T>::Vector(int size)
{
	Size = size;
	capacity = (Size / defaultSize + 1) * defaultSize;
	Size = 0;//只是需要size个空间，并没有添加元素进来
	data = new T[capacity];
}

//复制构造函数
template<class T>
Vector<T>::Vector(const Vector<T>& V)
{
	Size = V.Size();
	capacity = (Size / defaultSize + 1) * defaultSize;
	data = new T[capacity];

	for (int i = 0; i < Size; ++i)
		data[i] = V.data[i];
}

//指定大小和元素值构造函数
template<class T>
Vector<T>::Vector(int size, const  T& val)
{
	Size = size;
	capacity = (Size / defaultSize + 1) * defaultSize;
	data = new T[capacity];
	for (int i = 0; i < Size; ++i)
		data[i] = val;
}

//析构函数
template<class T>
Vector<T>::~Vector()
{
	delete[] data;
}

//扩容函数
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

//清空Vector
template<class T>
void Vector<T>::clear()
{
	Size = 0;
	capacity = defaultSize;

	delete[] data;
	data = new T[capacity];
}

//在最后添加
template<class T>
void Vector<T>::emplace_back(const T& x)
{
	if (Size == capacity - 1)
		expand();
	data[Size++] = x;//在data[Size]的位置添加
}

//最后删除
template<class T>
void Vector<T>::pop_back()
{
	if (Size == 0)
		return;
	--Size;//直接不要最后那个空间
}

//利用迭代器插入
template<class T>
void Vector<T>::insert(const Vector<T>::vector_iterator& it, const T& x)
{
	int loc = it - begin();//获得要插入的下标
	if (loc < 0 || loc > Size + 1)
		return;

	if (Size == capacity - 1)//空间不够就扩容
		expand();

	for (int i = Size - 1; i >= loc; --i)//loc到Size-1的元素全部后移
		data[i + 1] = data[i];

	data[loc] = x;
	++Size;
}

//利用迭代器删除
template<class T>
void Vector<T>::remove(const Vector<T>::vector_iterator& it)
{
	if (it == NULL || Size == 0)
		return;

	int loc = it - begin();
	if (loc < 0 || loc >= Size)
		return;

	//往前移，覆盖掉loc位置
	for (int i = loc; i < Size - 1; ++i)
		data[i] = data[i + 1];

	--Size;
}

//重载=
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

//重新设置大小
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

//给出元素填充，重新设置大小
template<class T>
void Vector<T>::resize(int size, const T& val)
{
	if (capacity < size)
	{
		capacity = (size / defaultSize + 1) * defaultSize;
		T* newData = new T[capacity];
		for (int i = 0; i < Size; ++i)
			newData[i] = val;//将值全部设为val
		delete[] data;
		data = newData;
		Size = size;
	}
	else//够大就直接填充
	{
		for (int i = 0; i < size; ++i)
			data[i] = val;//将值全部设为val
		Size = size;
	}
}

//寻找值为x的，返回迭代器
template<class T>
typename Vector<T>::vector_iterator Vector<T>::find(const T& x)
{
	for (auto it = begin(); it != end(); ++it)
		if (*it == x)
			return it;
	return NULL;
}


//边的结点
struct edge {
	//指向的位置，权值大小
	int to, val;

	//指向下一个结点
	edge* next;

	//初始化构造函数
	edge(const int& to, const int& val, edge* next = NULL) :
		to(to), val(val), next(next) {}
};

class criticalActivity {
private:
	//同一起点的边在同一个桶，一个图，一个反图
	Vector<edge*> graph1, graph2;

	//记录入度
	Vector<int> in;

	//记录出度
	Vector<int> out;

	//N为顶点个数，M为边的个数
	int N = 0, M = 0;
public:
	//寻找关键活动函数
	void AOE();

	//得到N, M值
	void getNM(const int& N, const int& M);

	//初始化
	void init();

	//记录边
	void setEdge(int from, int to, int val);

	//检查是否输入的边是否合法
	bool checkValid();

	//析构函数释放结点空间
	~criticalActivity();
};


#endif // !_KEYACTIVITY_H


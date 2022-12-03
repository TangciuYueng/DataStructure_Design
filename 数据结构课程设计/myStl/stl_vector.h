#ifndef _MY_STL_VECTOR
#define _MY_STL_VECTOR

#include <iostream>
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
		vector_iterator(iterator data) :data(data){}
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
		friend Vector<T>::vector_iterator operator+(const vector_iterator& it,int num)
		{
			Vector<T>::vector_iterator temp = it;
			for (int i = 0; i < num; ++i)
				++temp;
			return temp;
		}
		//���������
		friend Vector<T>::vector_iterator operator-(const vector_iterator& it,int num)
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
Vector<T>::Vector(int size,const  T& val)
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
	if (it == NULL|| Size == 0)
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
void Vector<T>::resize(int size,const T& val)
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
#endif 
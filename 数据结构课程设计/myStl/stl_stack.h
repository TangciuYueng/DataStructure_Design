#ifndef _MY_STL_STACK
#define _MY_STL_STACK


#include "stl_list.h"

template<class T>
class Stack {
private:
	List<T> data;
public:
	Stack() {

	}
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
		data.pop_back();
	}
	T& top() {
		return data.getTail()->val;
	}
};
#endif // !_MY_STL_STACK
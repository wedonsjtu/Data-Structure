#include <iostream>
using namespace std;

template <class elemType>
class list {
public:
	virtual int length() const = 0;
	virtual int search(const elemType &x) const = 0;
	virtual elemType visit(int i) const = 0;
	virtual void insert(int i, const elemType &x) = 0;
	virtual void remove(int i) = 0;
	virtual void clear() = 0;
	virtual void traverse() const = 0;
	virtual ~list() {}
};

class OutOfBound{};
class IllegalSize{};

template <class elemType>
class seqList: public list<elemType> {
private:
	elemType *data;
	int currentLength;
	int maxSize;
public:
	seqList(int initSize = 10);
	~seqList() {delete[] data;};
	int length() const;
	int search(const elemType &x) const;
	elemType visit(int i) const;
    void insert(int i, const elemType &x); 
    void remove(int i);  
    void clear();
    void traverse() const;
};

template <class elemType>
seqList<elemType>::seqList(int initSize) {
	data = new elemType[initSize];
	if (!data) throw IllegalSize();
	maxSize = initSize;
	currentLength = 0;
}

template <class elemType>
int seqList<elemType>::length() const {
	return currentLength;
}

template <class elemType>
int seqList<elemType>::search(const elemType &x) const {
	for (int i=0; i < currentLength; ++i)
		if (data[i] == x) return i;
	return -1;
}

template <class elemType>
elemType seqList<elemType>::visit(int i) const {
	if (i < 0 || i >= currentLength) throw OutOfBound();
	return data[i];
}

template <class elemType>
void seqList<elemType>::insert(int i, const elemType &x) {
	if (i < 0 || i > currentLength || currentLength == maxSize) throw OutOfBound();
	for (int j = currentLength++; j > i; --j) data[j] = data[j - 1];
	data[i] = x;
}

template <class elemType>
void seqList<elemType>::remove(int i) {
	if (i < 0 || i >= currentLength) throw OutOfBound();
	for (int j = i; j < currentLength - 1; ++j)
		data[j] = data[j + 1];
	--currentLength;
}

template <class elemType>
void seqList<elemType>::clear() {
	currentLength = 0;
}

template <class elemType>
void seqList<elemType>::traverse() const {
	for (int i = 0; i < currentLength; ++i) {
		cout << data[i];
		if (i != currentLength - 1) cout << '\t';
	}
}


int main() {
	seqList<int> a;
	cout << a.length();
	a.insert(0, 2);
	cout << a.length();
	a.insert(1, 3);
	cout << endl;
	a.traverse();
	cout << endl;
	a.remove(1);
	cout << a.length();
	cout << endl;
	a.traverse();
	cout << endl;
	return 0;
}


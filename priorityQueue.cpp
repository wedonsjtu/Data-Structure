#include <iostream>
using namespace std;

template <class elemType>
class queue {
public:
	virtual bool enQueue(const elemType &x) = 0;
	virtual elemType deQueue() = 0;
	virtual bool isEmpty() const = 0;
	virtual elemType getHead() const = 0;
	virtual ~queue() {};
};

template <class elemType>
class minHeap: public queue<elemType> {
private:
	int currentSize;
	elemType *array;
	int maxSize;
	// void doubleSpace();
	void buildHeap();
	void percolateDown(int hole);
public:
	minHeap(int capacity = 100) {
		array = new elemType[capacity];
		maxSize = capacity;
		currentSize = 0;
	}
	minHeap(const elemType *items, int size);
	~minHeap() {delete[] array;}
	bool isEmpty() const {return currentSize == 0;}
	bool enQueue(const elemType &x);
	elemType deQueue();
	elemType getHead() const {return array[1];}
	int find(const elemType &x, int i = 1); // 找出优先级值大于x的最小的元素，输出其下标。如果有多个元素优先级值相同输出下标最小的那个。
	void decrease(int i, const elemType &v); // 将第i个节点的优先级值减少v
};

template <class elemType>
bool minHeap<elemType>::enQueue(const elemType &x) {
	if (currentSize == maxSize - 1) return false;
	int hole = ++currentSize;
	for (; hole > 1 && x < array[hole / 2]; hole /= 2) array[hole] = array[hole / 2];
	array[hole] = x;
	return true;
} 

template <class elemType>
elemType minHeap<elemType>::deQueue() {
	elemType minItem;
	minItem = array[1];
	array[1] = array[currentSize--];
	percolateDown(1);
	return minItem;
}

template <class Type>
void minHeap<Type>::percolateDown(int hole) {
	int child;
	Type tmp = array[hole];
	for (; hole * 2 <= currentSize; hole = child) {
		child = hole * 2;
		if (child != currentSize && array[child + 1] < array[child]) child++;
		if (array[child] < tmp) array[hole] = array[child];
		else break;
	}
	array[hole] = tmp;
}

template <class elemType>
void minHeap<elemType>::buildHeap() {
	for (int i = currentSize / 2; i > 0; i--)
        percolateDown(i);
}

template <class elemType>
minHeap<elemType>::minHeap(const elemType *items, int size) {
	maxSize = size * 2;
	currentSize = size;
	array = new elemType[maxSize];
	for (int i = 0; i < size; i++) array[i + 1] = items[i];
	buildHeap();
}

template <class elemType>
int minHeap<elemType>::find(const elemType &x, int i) {
	if (array[i] > x) return i;
	bool left = true, right = true;
	int left1, right1;
	if (2 * i <= currentSize) {
		left1 = find(x, 2 * i);
	}
	else left = false;
	if (2 * i + 1 <= currentSize) {
		right1 = find(x, 2 * i + 1);
	}
	else right = false;
	if (!left && !right) return currentSize + 1;
	if (!left || left1 == currentSize + 1) return right1;
	if (!right || right1 == currentSize + 1) return left1;
	if (array[left1] == array[right1]) return (left1 <= right1)?left1:right1;
	else if (array[left1] < array[right1]) return left1;
	return right1;
}

template <class elemType>
void minHeap<elemType>::decrease(int i, const elemType &v) {
	array[i] -= v;
	elemType x = array[i];
	for (; i > 1 && x < array[i / 2]; i /= 2) array[i] = array[i / 2];
	array[i] = x;
}

//=====================================================================================

template <class elemType>
class maxHeap: public queue<elemType> {
private:
	int currentSize;
	elemType *array;
	int maxSize;
	// void doubleSpace();
	void buildHeap();
	void percolateDown(int hole);
public:
	maxHeap(int capacity = 100) {
		array = new elemType[capacity];
		maxSize = capacity;
		currentSize = 0;
	}
	maxHeap(const elemType *items, int size);
	~maxHeap() {delete[] array;}
	bool isEmpty() const {return currentSize == 0;}
	bool enQueue(const elemType &x);
	elemType deQueue();
	elemType getHead() const {return array[1];}
};

template <class elemType>
bool maxHeap<elemType>::enQueue(const elemType &x) {
	if (currentSize == maxSize - 1) return false;
	int hole = ++currentSize;
	for (; hole > 1 && x > array[hole / 2]; hole /= 2) array[hole] = array[hole / 2];
	array[hole] = x;
	return true;
} 

template <class elemType>
elemType maxHeap<elemType>::deQueue() {
	elemType minItem;
	minItem = array[1];
	array[1] = array[currentSize--];
	percolateDown(1);
	return minItem;
}

template <class Type>
void maxHeap<Type>::percolateDown(int hole) {
	int child;
	Type tmp = array[hole];
	for (; hole * 2 <= currentSize; hole = child) {
		child = hole * 2;
		if (child != currentSize && array[child + 1] > array[child]) child++;
		if (array[child] > tmp) array[hole] = array[child];
		else break;
	}
	array[hole] = tmp;
}

template <class elemType>
void maxHeap<elemType>::buildHeap() {
	for (int i = currentSize / 2; i > 0; i--)
        percolateDown(i);
}

template <class elemType>
maxHeap<elemType>::maxHeap(const elemType *items, int size) {
	maxSize = size * 2;
	currentSize = size;
	array = new elemType[maxSize];
	for (int i = 0; i < size; i++) array[i + 1] = items[i];
	buildHeap();
}

//=====================================================================================

/*
int main() {
	int s[] = {13, 53, 12, 34, 2, 12, 4, 67, 1, 5, 7, 4, 3, 2, 9, 10, 8, 0, 12};

	minHeap<int> a(s, sizeof(s) / sizeof(s[0]));
	cout << a.isEmpty() << ' ';
	while (!a.isEmpty()) cout << a.deQueue() << ' ';
	cout << a.isEmpty() << endl;

	maxHeap<int> b(s, sizeof(s) / sizeof(s[0]));
	cout << b.isEmpty() << ' ';
	while (!b.isEmpty()) cout << b.deQueue() << ' ';
	cout << b.isEmpty() << endl;

	return 0;
}
*/

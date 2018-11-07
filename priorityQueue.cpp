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
class priorityQueue: public queue<elemType> {
private:
	int currentSize;
	elemType *array;
	int maxSize;
	// void doubleSpace();
	void buildHeap();
	void percolateDown(int hole);
public:
	priorityQueue(int capacity = 100) {
		array = new elemType[capacity];
		maxSize = capacity;
		currentSize = 0;
	}
	priorityQueue(const elemType *items, int size);
	~priorityQueue() {delete[] array;}
	bool isEmpty() const {return currentSize == 0;}
	bool enQueue(const elemType &x);
	elemType deQueue();
	elemType getHead() const {return array[1];}
	int find(const elemType &x, int i = 1); // 找出优先级值大于x的最小的元素，输出其下标。如果有多个元素优先级值相同输出下标最小的那个。
	void decrease(int i, const elemType &v); // 将第i个节点的优先级值减少v
};

template <class elemType>
bool priorityQueue<elemType>::enQueue(const elemType &x) {
	if (currentSize == maxSize - 1) return false;
	int hole = ++currentSize;
	for (; hole > 1 && x < array[hole / 2]; hole /= 2) array[hole] = array[hole / 2];
	array[hole] = x;
	return true;
} 

template <class elemType>
elemType priorityQueue<elemType>::deQueue() {
	elemType minItem;
	minItem = array[1];
	array[1] = array[currentSize--];
	percolateDown(1);
	return minItem;
}

template <class Type>
void priorityQueue<Type>::percolateDown(int hole) {
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
void priorityQueue<elemType>::buildHeap() {
	for (int i = currentSize / 2; i > 0; i--)
        percolateDown(i);
}

template <class elemType>
priorityQueue<elemType>::priorityQueue(const elemType *items, int size) {
	maxSize = size * 2;
	currentSize = size;
	array = new elemType[maxSize];
	for (int i = 0; i < size; i++) array[i + 1] = items[i];
	buildHeap();
}

template <class elemType>
int priorityQueue<elemType>::find(const elemType &x, int i) {
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
void priorityQueue<elemType>::decrease(int i, const elemType &v) {
	array[i] -= v;
	elemType x = array[i];
	for (; i > 1 && x < array[i / 2]; i /= 2) array[i] = array[i / 2];
	array[i] = x;
}


int main() {
	int s[] = {1, 5, 7, 4, 3, 2, 9};
	priorityQueue<int> a(s, 7);
	cout << a.isEmpty();
	cout << a.deQueue();
	cout << a.deQueue();
	cout << a.deQueue();
	cout << a.deQueue();
	cout << a.deQueue();
	cout << a.deQueue();
	cout << a.deQueue();
	cout << a.isEmpty() << endl;
	return 0;
}


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
class seqQueue:public queue<elemType> {
private:
	elemType *elem;
	int maxSize;
	int front, rear;
public:
	seqQueue(int initSize=10);
	~seqQueue() {delete[] elem;}
	bool isEmpty() const {return front == rear;}
	elemType getHead() const {return elem[(front + 1) % maxSize];}
	bool enQueue(const elemType &x);
	elemType deQueue();
};

template <class elemType>
seqQueue<elemType>::seqQueue(int initSize) {
	elem = new elemType[initSize];
	maxSize = initSize;
	front = rear = 0;
}

template <class elemType>
bool seqQueue<elemType>::enQueue(const elemType &x) {
	if ((rear + 1) % maxSize == front) return false;
	rear = (rear + 1) % maxSize;
	elem[rear] = x;
	return true;
}

template <class elemType>
elemType seqQueue<elemType>::deQueue() {
	front = (front + 1) % maxSize;
	return elem[front];
}

template <class elemType>
class linkQueue:public queue<elemType> {
private:
	struct node {
		elemType data;
		node* next;
		node():next(NULL) {}
		node(const elemType &x, node* N = NULL) {
			data = x;
			next = N;
		}
		~node() {}
	};
	node *front, *rear;
public:
	linkQueue() {front = rear = NULL;}
	~linkQueue();
	bool isEmpty() const {return front == NULL;}
	elemType getHead() const {return front -> data;}
	bool enQueue(const elemType &x);
	elemType deQueue();
};

template <class elemType>
linkQueue<elemType>::~linkQueue() {
	node* tmp;
	while (front) {
		tmp = front;
		front = front -> next;
		delete tmp;
	}
}

template <class elemType>
bool linkQueue<elemType>::enQueue(const elemType &x) {
	if (!rear) front = rear = new node(x);
	else {
		rear -> next = new node(x);
		rear = rear -> next;
	}
	return true;
}

template <class elemType>
elemType linkQueue<elemType>::deQueue() {
	node* tmp = front;
	elemType value = front -> data;
	front = front -> next;
	if (!front) rear = NULL;
	delete tmp;
	return value;
}

/*
int main() {
	seqQueue<int> a;
	cout << a.isEmpty();
	a.enQueue(2);
	a.enQueue(3);
	cout << a.isEmpty();
	cout << a.getHead();
	cout << a.deQueue();
	cout << a.getHead();
	cout << a.deQueue();
	cout << a.isEmpty() << endl;
	linkQueue<int> b;
	cout << b.isEmpty();
	b.enQueue(4);
	b.enQueue(7);
	cout << b.isEmpty();
	cout << b.getHead();
	cout << b.deQueue();
	cout << b.getHead();
	cout << b.deQueue();
	cout << b.isEmpty() << endl;
	return 0;
}
*/

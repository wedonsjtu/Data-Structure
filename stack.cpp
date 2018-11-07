#include <iostream>
using namespace std;

template <class elemType>
class stack {
public:
	virtual bool push(const elemType &x) = 0;
	virtual elemType pop() = 0;
	virtual elemType top() const = 0;
	virtual bool isEmpty() const = 0;
	virtual ~stack() {};
};

template <class elemType>
class seqStack: public stack<elemType> {
private:
	elemType *elem;
	int top_p;
	int maxSize;
public:
	seqStack(int initSize = 10);
	bool push(const elemType &x);
	elemType pop() {return elem[top_p--];}
	elemType top() const {return elem[top_p];}
	bool isEmpty() const {return top_p == -1;}
	~seqStack() {delete[] elem;}
};

template <class elemType>
seqStack<elemType>::seqStack(int initSize) {
	elem = new elemType[initSize];
	maxSize = initSize;
	top_p = -1;
}

template <class elemType>
bool seqStack<elemType>::push(const elemType &x) {
	if (top_p == maxSize - 1) return false;
	elem[++top_p] = x;
	return true;
}

template <class elemType>
class linkStack: public stack<elemType> {
private:
	struct node {
		elemType data;
		node* next;
		node():next(NULL) {}
		node(const elemType &x, node* n=NULL) {
			data = x;
			next = n;
		}
		~node() {};
	};
	node* top_p;
public:
	linkStack() {top_p = NULL;}
	~linkStack();
	bool isEmpty() const {return top_p == NULL;}
	bool push(const elemType &x) {top_p = new node(x, top_p);}
	elemType pop();
	elemType top() const {return top_p->data;}
};

template <class elemType>
elemType linkStack<elemType>::pop() {
	node* tmp = top_p;
	elemType x = tmp->data;
	top_p = top_p->next;
	delete tmp;
	return x;
}

template <class elemType>
linkStack<elemType>::~linkStack() {
	node* tmp;
	while (top_p) {
		tmp = top_p;
		top_p = top_p->next;
		delete tmp;
	}
}

/*
int main() {
	seqStack<int> a(10);
	a.push(2);
	a.push(4);
	cout << a.isEmpty();
	cout << a.top();
	cout << a.pop();
	cout << a.isEmpty();
	cout << a.top();
	cout << a.pop();
	cout << a.isEmpty() << endl;
	linkStack<int> b; 
	b.push(1);
	b.push(3);
	cout << b.isEmpty();
	cout << b.top();
	cout << b.pop();
	cout << b.isEmpty();
	cout << b.top();
	cout << b.pop();
	cout << b.isEmpty() << endl;
}
*/

#include <iostream>
#include <cmath>
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
class bernoulliQueue: public queue<elemType> {
public:
	struct Node {
		Node *child, *sibling;
		elemType data;
		Node(): child(NULL), sibling(NULL) {}
		Node(elemType item, Node *L = NULL, Node *R = NULL):data(item), child(L), sibling(R) {}
		~Node() {}
	};
	Node** forest;
	int noOfTree;
	Node* merge(Node *t1, Node *t2);
	int findmin() const;
	void deleteTree(Node *rt);
public:
	bernoulliQueue(int n=100) {
		noOfTree = int(log(n)/log(2)) + 1;
		forest = new Node*[noOfTree];
		for (int i = 0; i < noOfTree; ++i) forest[i] = NULL;
	}
	~bernoulliQueue() {
		for (int i = 0; i < noOfTree; ++i)
			if (forest[i]) deleteTree(forest[i]);
		delete[] forest;
	}
	bool isEmpty() const;
	bool enQueue(const elemType &x);
	elemType deQueue();
	elemType getHead() const;
	void merge(bernoulliQueue &other);
};

template <class elemType>
void bernoulliQueue<elemType>::deleteTree(Node *rt) {
	Node *c = rt->child, *t;
	while (c) {
		t = c;
		c = c->sibling;
		deleteTree(t);
	}
	delete rt;
}

template <class elemType>
void bernoulliQueue<elemType>::merge(bernoulliQueue &other) {
	Node **tmp = forest, *carry = NULL;
	int tmpSize = noOfTree;
	int min = (noOfTree < other.noOfTree)?noOfTree:other.noOfTree;
	int i;
	if (noOfTree < other.noOfTree) {
		noOfTree = other.noOfTree;
		if (other.forest[noOfTree]) ++noOfTree;
	}
	else if (forest[noOfTree]) ++noOfTree;
	forest = new Node*[noOfTree];
	for (i = 0; i < noOfTree; ++i) forest[i] = NULL;
	for (i = 0; i < min; ++i) {
		if (!carry) {
			if (!tmp[i]) forest[i] = other.forest[i];
			else {
				if (!other.forest[i]) forest[i] = tmp[i];
				else carry = merge(other.forest[i], tmp[i]);
			}
		}
		else {
			if (tmp[i] && other.forest[i]) {
				forest[i] = carry;
				carry = merge(other.forest[i], tmp[i]);
			}
			else {
				if (!tmp[i] && !other.forest[i]) {
					forest[i] = carry;
					carry = NULL;
				}
				else if (!tmp[i]) carry = merge(other.forest[i], carry);
				else carry = merge(tmp[i], carry);
			}
		}
	}
	if (other.noOfTree == min) {
		for (i; i < tmpSize; ++i) {
			if (!carry) forest[i] = tmp[i];
			else if (!tmp[i]) {
				forest[i] = carry;
				carry = NULL;
			}
			else carry = merge(tmp[i], carry);
		}
	}
	else {
		for (i; i < other.noOfTree; ++i) {
			if (!carry) forest[i] = other.forest[i];
			else if (!other.forest[i]) {
				forest[i] = carry;
				carry = NULL;
			}
			else carry = merge(other.forest[i], carry);
		}
	}
	if (carry) forest[i] = carry;
	for (i = 0; i < other.noOfTree; ++i) other.forest[i] = NULL;
	delete[] tmp;
}

template <class elemType>
typename bernoulliQueue<elemType>::Node* bernoulliQueue<elemType>::merge(Node* t1, Node* t2) {
	Node *min, *max;
	if (t1->data < t2->data) {
		min = t1;
		max = t2;
	}
	else {
		min = t2;
		max = t1;
	}
	if (!min->child) min->child = max;
	else {
		Node* t = min->child;
		while (t->sibling) t = t->sibling;
		t->sibling = max;
	}
	return min;
}

template <class elemType>
bool bernoulliQueue<elemType>::enQueue(const elemType &x) {
	bernoulliQueue tmp(1);
	tmp.forest[0] = new Node(x);
	merge(tmp);
	return true;
	// 未判定不能加入的情况
}

template <class elemType>
elemType bernoulliQueue<elemType>::deQueue() {
	elemType value;
	int min = findmin();
	if (min == 0) {
		value = forest[0]->data;
		delete forest[0];
		forest[0] = NULL;
		return value;
	}
	Node* t = forest[min], *c, *s;
	int sizeOfQueue = int(pow(2, min) - 1);
	bernoulliQueue tmp(sizeOfQueue);
	value = t->data;
	forest[min] = NULL;
	c = t->child;
	delete t;
	int i = 0;
	do {
		tmp.forest[i++] = c;
		s = c->sibling;
		c->sibling = NULL;
		c = s;
	} while (c);
	merge(tmp);
	return value;
}

template <class elemType>
int bernoulliQueue<elemType>::findmin() const {
	int min, i = 0;
	for (i; i < noOfTree && !forest[i]; ++i);
	min = i;
	for (i; i < noOfTree; ++i) {
		if (forest[i] && forest[i]->data < forest[min]->data) min = i;
	}
	return min;
}

template <class elemType>
bool bernoulliQueue<elemType>::isEmpty() const {
	for (int i = 0; i < noOfTree; ++i)
		if (forest[i]) return false;
	return true;
}

template <class elemType>
elemType bernoulliQueue<elemType>::getHead() const {
	int pos = findmin();
	return forest[pos]->data;
}

int main() {
	int s[] = {1, 5, 7, 4, 3, 2, 9};
	bernoulliQueue<int> a;
	for (int i=0; i < 7; ++i) a.enQueue(s[i]);
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


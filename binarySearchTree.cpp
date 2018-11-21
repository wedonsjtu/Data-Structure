#include <iostream>
using namespace std;

template <class elemType>
class binarySearchTree {
private:
	struct binaryNode {
		elemType data;
		binaryNode *left, *right;
		binaryNode(const elemType &x, binaryNode *lt = NULL, binaryNode *rt = NULL):data(x), left(lt), right(rt) {}
	};

	binaryNode *root;
	void insert(const elemType &x, binaryNode *&t);
	void remove(const elemType &x, binaryNode *&t);
	bool find(const elemType &x, binaryNode *t) const;
	void makeEmpty(binaryNode *&t);
	void midOrder(binaryNode *t) const;
	void remove_less_than(const elemType &x, binaryNode *&t);
	void remove_greater_than(const elemType &x, binaryNode *&t);
	void remove_interval(const elemType &a, const elemType &b, binaryNode *&t);

public:
	binarySearchTree(binaryNode *t=NULL):root(t) {}
	~binarySearchTree() {makeEmpty(root);}
	bool find(const elemType &x) const {return find(x, root);}
	void insert(const elemType &x) {insert(x, root);}
	void remove(const elemType &x) {remove(x, root);}
	void midOrder() const {midOrder(root); cout << endl;}
	void remove_less_than(const elemType &x) {remove_less_than(x, root);}
	void remove_greater_than(const elemType &x) {remove_greater_than(x, root);}
	void remove_interval(const elemType &a, const elemType &b) {remove_interval(a, b, root);}
	elemType find_with_index(int i, const elemType &notfind);


private:
	void levelOrder(binaryNode *t) const;
public:
	void levelOrder() const;
};

template <class elemType>
bool binarySearchTree<elemType>::find(const elemType &x, binaryNode *t) const {
	if (!t) return false;
	if (x < t->data) return find(x, t->left);
	if (x > t->data) return find(x, t->right);
	return true;
}

template <class elemType>
void binarySearchTree<elemType>::insert(const elemType &x, binaryNode *&t) {
	if (!t) t = new binaryNode(x);
	else if (x < t->data) insert(x, t->left);
	else if (x > t->data) insert(x, t->right);
}

template <class elemType>
void binarySearchTree<elemType>::remove(const elemType &x, binaryNode *&t) {
	if (!t) return;
	if (x < t->data) remove(x, t->left);
	else if (x > t->data) remove(x, t->right);
	else if (t->left && t->right) {
		binaryNode *tmp = t->right;
		while (tmp->left) tmp = tmp->left;
		t->data = tmp->data;
		remove(t->data, t->right);
	}
	else {
		binaryNode *oldNode = t;
		t = (t->left)?t->left:t->right;
		delete oldNode;
	}
}

template <class elemType>
void binarySearchTree<elemType>::makeEmpty(binaryNode *&t) {
	if (!t) return;
	if (t->left) makeEmpty(t->left);
	if (t->right) makeEmpty(t->right);
	delete t;
}

template <class elemType>
void binarySearchTree<elemType>::midOrder(binaryNode *t) const {
	if (t) {
		midOrder(t->left);
		cout << t->data << ' ';
		midOrder(t->right);
	}
}

template <class elemType>
void binarySearchTree<elemType>::remove_less_than(const elemType &x, binaryNode *&t) {
	if (!t) return;
	if (t->data == x) {
		makeEmpty(t->left);
		t->left = NULL;
		return;
	}
	if (t->data < x) {
		makeEmpty(t->left);
		binaryNode *tmp = t;
		t = t->right;
		delete tmp;
		remove_less_than(x, t);
		return;
	}
	remove_less_than(x, t->left);
}

template <class elemType>
void binarySearchTree<elemType>::remove_greater_than(const elemType &x, binaryNode *&t) {
	if (!t) return;
	if (t->data == x) {
		makeEmpty(t->right);
		t->right = NULL;
		return;
	}
	if (t->data > x) {
		makeEmpty(t->right);
		binaryNode *tmp = t;
		t = t->left;
		delete tmp;
		remove_greater_than(x, t);
		return;
	}
	remove_greater_than(x, t->right);
}

template <class elemType>
void binarySearchTree<elemType>::remove_interval(const elemType &a, const elemType &b, binaryNode *&t) { // close interval
	if (!t) return;
	if (t->data <= a) {
		remove_interval(a, b, t->right);
		return;
	}
	if (t->data >= b) {
		remove_interval(a, b, t->left);
		return;
	}
	remove(t->data, t);
	remove_interval(a, b, t);
}


template <class elemType> class linkStack;

template <class elemType>
elemType binarySearchTree<elemType>::find_with_index(int i, const elemType &notfind) {
	if (!root or i < 0) return notfind;

	struct StNode {
		binaryNode* node;
		int TimesPop;
		StNode(binaryNode* n=NULL):node(n), TimesPop(0) {}
	};

	int times = 0; // or 1
	linkStack<StNode> s;
	StNode current(root);
	s.push(current);
	while(!s.isEmpty()) {
		current = s.pop();
		if (++current.TimesPop == 2) {
			if (times == i) return current.node->data;
			++times;
			if (current.node->right) s.push(StNode(current.node->right));
		}
		else {
			s.push(current);
			if (current.node->left) s.push(StNode(current.node->left));
		}
	}

	return notfind;
}

template <class elemType> class linkQueue;

template <class elemType>
void binarySearchTree<elemType>::levelOrder() const {
	cout << "---------------------------" << endl;
	levelOrder(root);
	cout << endl << "---------------------------" << endl;
}

template <class elemType>
void binarySearchTree<elemType>::levelOrder(binaryNode *t) const {
	if (!t) {
		cout << "NULL";
		return;
	}
	linkQueue<binaryNode *> s;
	binaryNode *p;
	int en = 1;
	bool f = true;
	s.enQueue(t);
	while (!s.isEmpty()) {
		p = s.deQueue();
		if (p) {
			en--;
			if (f) cout << p->data;
			else cout << ' ' << p->data;
			if (p->left) {
				s.enQueue(p->left);
				en++;
			}
			else s.enQueue(NULL);
			if (p->right) {
				s.enQueue(p->right);
				en++;
			}
			else s.enQueue(NULL);
		}
		else if (en) {
			if (f) cout << "NULL";
			else cout << ' ' << "NULL";
			//s.enQueue(NULL);
			//s.enQueue(NULL);
		}
		f = false;
	}
}

// ==============================================================

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

// ==============================================================

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

// ==============================================================


int main() {
	int s[] = {6,4,2,8,45,34,1,3,23,89,4,5,7,32,21,45,543,123,324,234,34,78,454};
	binarySearchTree<int> a;
	for (int i = 0; i < sizeof(s) / sizeof(s[0]); ++i) a.insert(s[i]);
	cout << a.find(2) << endl;
	cout << a.find(1) << endl;
	cout << a.find(34) << endl;
	cout << a.find(57) << endl;
	cout << a.find(100) << endl;
	cout << a.find(0) << endl;
	a.remove(34);
	cout << a.find(34) << endl;
	a.remove(100);
	a.insert(34);
	a.remove_less_than(20);
	a.midOrder();
	//a.levelOrder();
	a.remove_greater_than(454);
	a.midOrder();
	a.remove_interval(454,2000);
	a.midOrder();
	for (int i = 0; i < 20; ++i)
		cout << a.find_with_index(i, -1) << endl;
	return 0;
}


#include <iostream>
using namespace std;

template <class elemType>
class AVLTree {
private:
	struct AVLNode {
		elemType data;
		AVLNode *left, *right;
		int height;
		AVLNode(const elemType &elem, AVLNode *lt=NULL, AVLNode *rt=NULL, int h=0) {
			data = elem;
			left = lt;
			right = rt;
			height = h;
		}
	};
	AVLNode *root;
	void insert(const elemType &x, AVLNode *&t);
	bool remove(const elemType &x, AVLNode *&t);
	void makeEmpty(AVLNode *&t);
	int height(AVLNode *t) const {return (!t)?-1:t->height;}
	void LL(AVLNode *&t);
	void LR(AVLNode *&t);
	void RL(AVLNode *&t);
	void RR(AVLNode *&t);
	int max(int a, int b) {return (a >b)?a:b;}

public:
	AVLTree(AVLNode* t=NULL):root(t) {}
	~AVLTree() {makeEmpty(root);}
	bool find(const elemType &x) const;
	void insert(const elemType &x) {insert(x, root);}
	void remove(const elemType &x) {remove(x, root);}

private:
	void levelOrder(AVLNode *t) const;
public:
	void levelOrder() const;
};

template <class elemType>
bool AVLTree<elemType>::find(const elemType &x) const {
	AVLNode *t = root;
	while (t && t->data != x) {
		if (t->data > x) t = t->left;
		else t = t->right;
	}
	return t;
}

template <class elemType>
void AVLTree<elemType>::makeEmpty(AVLNode *&t) {
	if (!t) return;
	if (t->left) makeEmpty(t->left);
	if (t->right) makeEmpty(t->right);
	delete t;
}

template <class elemType>
void AVLTree<elemType>::LL(AVLNode *&t) {
	AVLNode* tmp = t;
	t = t->left;
	tmp->left = t->right;
	t->right = tmp;
	tmp->height = max(height(tmp->left), height(tmp->right)) + 1;
	t->height = max(height(t->left), height(tmp)) + 1;
}

template <class elemType>
void AVLTree<elemType>::RR(AVLNode *&t) {
	AVLNode* tmp = t;
	t = t->right;
	tmp->right = t->left;
	t->left = tmp;
	tmp->height = max(height(tmp->left), height(tmp->right)) + 1;
	t->height = max(height(t->right), height(tmp)) + 1;
}

template <class elemType>
void AVLTree<elemType>::LR(AVLNode *&t) {
	RR(t->left);
	LL(t);
}

template <class elemType>
void AVLTree<elemType>::RL(AVLNode *&t) {
	LL(t->right);
	RR(t);
}

template <class elemType>
void AVLTree<elemType>::insert(const elemType &x, AVLNode *&t) {
	if (!t) {
		t = new AVLNode(x);
		return;
	}
	if (x < t->data) {
		insert(x, t->left);
		if (height(t->left) == height(t->right) + 2) {
			if (x < t->left->data) LL(t);
			else LR(t);
		}
	}
	else if (x > t->data) {
		insert(x, t->right);
		if (height(t->left) == height(t->right) - 2) {
			if (x > t->right->data) RR(t);
			else RL(t);
		}
	}
	t->height = max(height(t->left), height(t->right)) + 1;
}

template <class elemType>
bool AVLTree<elemType>::remove(const elemType &x, AVLNode *&t) {
	bool stop = false;
	bool subTree; // false: left; true: right;
	if (!t) return true;
	if (x < t->data) {
		stop = remove(x, t->left);
		subTree = false;
	}
	else if (x > t->data) {
		stop = remove(x, t->right);
		subTree = true;
	}
	else if (t->left && t->right) {
		AVLNode *tmp = t->right;
		while (tmp->left) tmp = tmp->left;
		t->data = tmp->data;
		stop = remove(t->data, t->right);
		subTree = true;
	}
	else {
		AVLNode *oldNode = t;
		t = (t->left)?t->left:t->right;
		delete oldNode;
		return false;
	}
	if (stop) return true;
	int bf; // 删除t前的平衡因子
	int bfr;
	if (!subTree) {
		bf = height(t->left) - height(t->right) + 1;
		if (bf == 0) return true;
		if (bf == 1) return false;
		bfr = height(t->right->left) - height(t->right->right);
		switch (bfr) {
			case 0:
				RR(t);
				return true;
			case -1:
				RR(t);
				return false;
			default:
				RL(t);
				return false;
		}
	}
	else {
		bf = height(t->left) - height(t->right) - 1;
		if (bf == 0) return true;
		if (bf == -1) return false;
		bfr = height(t->right->left) - height(t->right->right);
		switch (bfr) {
			case 0:
				LL(t);
				return true;
			case -1:
				LL(t);
				return false;
			default:
				LR(t);
				return false;
		}
	}
}

template <class elemType> class linkQueue;

template <class elemType>
void AVLTree<elemType>::levelOrder() const {
	cout << "---------------------------" << endl;
	levelOrder(root);
	cout << endl << "---------------------------" << endl;
}

template <class elemType>
void AVLTree<elemType>::levelOrder(AVLNode *t) const {
	if (!t) {
		cout << "NULL";
		return;
	}
	linkQueue<AVLNode *> s;
	AVLNode *p;
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

/*
int main() {
	int s[] = {6,4,2,8,45,34,1,3,23,89,4,5,7,32,21,45,543,123,324,234,34,78,454};
	AVLTree<int> a;
	a.remove(0);
	cout << a.find(0) << endl;
	for (int i = 0; i < sizeof(s) / sizeof(s[0]); ++i) a.insert(s[i]);
	a.levelOrder();
	cout << a.find(2) << endl;
	cout << a.find(1) << endl;
	cout << a.find(34) << endl;
	cout << a.find(57) << endl;
	cout << a.find(100) << endl;
	cout << a.find(0) << endl;
	a.remove(34);
	cout << a.find(34) << endl;
	a.remove(100);
	return 0;
}
*/

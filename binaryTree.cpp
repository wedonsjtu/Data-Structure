#include <iostream>
using namespace std;

template <class elemType> class linkQueue;

template <class elemType>
class binaryTree {
private:
	struct Node {
		Node *left, *right;
		elemType data;
		Node(): left(NULL), right(NULL) {}
		Node(elemType item, Node *L = NULL, Node *R = NULL):data(item), left(L), right(R) {}
		~Node() {}
	};
	Node *root;
	
public:
	binaryTree():root(NULL) {}
	binaryTree(const elemType &x) {root = new Node(x);}
	~binaryTree() {clear();}
	elemType getRoot() const {return root->data;}
	elemType getLeft() const {return root->left->data;}
	elemType getRight() const {return root->right->data;}
	void makeTree(const elemType &x, binaryTree &lt, binaryTree &rt);
	void delLeft();
	void delRight();
	bool isEmpty() const {return !root;}
	void clear();
	int size() const {return size(root);}
	int height() const {return height(root);}
	void preOrder() const;
	void postOrder() const;
	void midOrder() const;
	void levelOrder() const;
	void createTree(elemType flag);
	void createWithPreOrderAndMidOrder(char* pre, char* mid);
	void preOrderWithSiblings() const;
	void postOrderWithSiblings() const;
	void levelOrderWithSiblings() const;
	void createTreeWithTheNumberOfNodes();
	bool isComplete() const;
private:
	int height(Node *t) const;
	void clear(Node *t);
	int size(Node *t) const;
	void preOrder(Node *t) const;
	void postOrder(Node *t) const;
	void midOrder(Node *t) const;
	void levelOrder(Node *t) const;
	void createWithPreOrderAndMidOrder(Node *&r, char *pre, int pre1, int pre2, char *mid, int mid1, int mid2);
};

template <class elemType>
void binaryTree<elemType>::makeTree(const elemType &x, binaryTree &lt, binaryTree &rt) {
	root = new Node(x, lt.root, rt.root);
	lt.root = NULL;
	rt.root = NULL;
}

template <class elemType>
void binaryTree<elemType>::delLeft() {
	binaryTree tmp = root->left;
	root->left = NULL;
	tmp.clear();
}

template <class elemType>
void binaryTree<elemType>::delRight() {
	binaryTree tmp = root->right;
	root->right = NULL;
	tmp.clear();
}

template <class elemType>
void binaryTree<elemType>::clear() {
	if (root) clear(root);
	root = NULL;
}

template <class elemType>
void binaryTree<elemType>::preOrder() const {
	if (root) preOrder(root);
	cout << endl;
}

template <class elemType>
void binaryTree<elemType>::postOrder() const {
	if (root) postOrder(root);
	cout << endl;
}

template <class elemType>
void binaryTree<elemType>::midOrder() const {
	if (root) midOrder(root);
	cout << endl;
}

template <class elemType>
int binaryTree<elemType>::height(Node *t) const {
	if (!t) return 0;
	int lt = height(t->left), rt = height(t->right);
	return 1 + ((lt > rt)?lt:rt);
}

template <class elemType>
void binaryTree<elemType>::clear(Node *t) {
	if (t->left) clear(t->left);
	if (t->right) clear(t->right);
	delete t;
}

template <class elemType>
int binaryTree<elemType>::size(Node *t) const {
	if (!t) return 0;
	return 1 + size(t->left) + size(t->right);
}

template <class elemType>
void binaryTree<elemType>::preOrder(Node *t) const {
	if (t) {
		cout << t->data << ' ';
		preOrder(t->left);
		preOrder(t->right);
	}
}

template <class elemType>
void binaryTree<elemType>::postOrder(Node *t) const {
	if (t) {

		postOrder(t->left);
		postOrder(t->right);
		cout << t->data << ' ';
	}
}

template <class elemType>
void binaryTree<elemType>::midOrder(Node *t) const {
	if (t) {
		midOrder(t->left);
		cout << t->data << ' ';
		midOrder(t->right);
	}
}

template <class elemType>
void binaryTree<elemType>::levelOrder() const {
	levelOrder(root);
	cout << endl;
}

template <class elemType>
void binaryTree<elemType>::levelOrder(Node *t) const {
	if (!t) {
		cout << "NULL";
		return;
	}
	linkQueue<Node *> s;
	Node *p;
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

template <class elemType>
void binaryTree<elemType>::preOrderWithSiblings() const {
	preOrder();
	/*
	if (!root) {
		cout << endl;
		return;
	}
	cout << root->data;
	Node *t = root->left;
	while (t) {
		cout << ' ';
		preOrder(t);
		t = t->right; 
	}
	cout << endl;
	*/
}

template <class elemType>
void binaryTree<elemType>::postOrderWithSiblings() const {
	midOrder();
	/*
	if (!root) {
		cout << endl;
		return;
	}
	Node *t = root->left;
	while (t) {
		postOrder(t);
		t = t->right;
		cout << ' ';
	}
	cout << root->data << endl;
	*/
}

template <class elemType>
void binaryTree<elemType>::levelOrderWithSiblings() const {
	if (!root) {
		cout << endl;
		return;
	}
	linkQueue<Node *> s;
	Node *p, *t = root;
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
				t = p->left;
				while (t->right) {
					s.enQueue(t->right);
					en++;
					t = t->right;
				}
				s.enQueue(NULL);
			}
			else s.enQueue(NULL);
		}
		//else if (en) {
		//	if (f) cout << "NULL";
		//	else cout << ' ' << "NULL";
		//}
		f = false;
	}
	cout << endl;
}

template <class elemType>
void binaryTree<elemType>::createTreeWithTheNumberOfNodes() {
	int nodenum, pi, qi, vi;
	cin >> nodenum;
	int i = nodenum;
	Node** arr = new Node*[nodenum];
	bool* isNotRoot = new bool[nodenum]();
	for (i; i > 0; --i) arr[i - 1] = new Node(0);
	for (i = 0; i < nodenum; ++i) {
		cin >> pi >> qi >> vi;
		arr[i]->data = vi;
		if (pi != 0) {
			arr[i]->left = arr[--pi];
			isNotRoot[pi] = true;
		}
		if (qi != 0) {
			arr[i]->right = arr[--qi];
			isNotRoot[qi] = true;
		}
	}
	for (i = 0; i < nodenum; ++i) {
		if (!isNotRoot[i]) {
			root = arr[i];
			break;
		}
	}
	delete[] isNotRoot;
	delete[] arr;
}

template <class elemType>
bool binaryTree<elemType>::isComplete() const {
	if (!root) return true;
	linkQueue<Node *> s;
	Node *p;
	int en = 1;
	s.enQueue(root);
	while (!s.isEmpty()) {
		p = s.deQueue();
		if (p) {
			en--;
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
		else if (en) return false;
	}
	return true;
}

template <class elemType>
void binaryTree<elemType>::createTree(elemType flag) {
	linkQueue<Node *> que;
	Node *tmp;
	elemType x, ldata, rdata;
	cout << endl << "Create root node: ";
	cin >> x;
	root = new Node(x);
	que.enQueue(root);
	while (!que.isEmpty()) {
		tmp = que.deQueue();
		cout << endl << "Input " << tmp->data 
			<< "\'s two children(" << flag << " means null node):";
		cin >> ldata >> rdata;
		if (ldata != flag) que.enQueue(tmp->left = new Node(ldata));
		if (rdata != flag) que.enQueue(tmp->right = new Node(rdata));
	}
	cout << endl << "Create completed." << endl;
}

template <class elemType>
void binaryTree<elemType>::createWithPreOrderAndMidOrder(Node *&r, char *pre, int pre1, int pre2, char *mid, int mid1, int mid2) {
	if (pre1 > pre2 || mid1 > mid2) return;
	r = new Node(pre[pre1]);
	//Node* tmp = new Node('\0');
	//r->left = tmp;
	//r->right = tmp;
	int i;
	for (i = mid1; i <= mid2; ++i) {
		if (mid[i] == pre[pre1]) {
			createWithPreOrderAndMidOrder(r->left, pre, pre1 + 1, pre1 + i - mid1, mid, mid1, i - 1);
			createWithPreOrderAndMidOrder(r->right, pre, i + pre1 - mid1 + 1, pre2, mid, i + 1, mid2);
		}
	}
	//if (&r->left == &tmp) r->left = NULL;
	//if (&r->right == &tmp) r->right = NULL;
	//delete tmp;
}

template <class elemType>
void binaryTree<elemType>::createWithPreOrderAndMidOrder(char *pre, char* mid) {	
	int prelen = 0, midlen = 0;
	while (pre[prelen] != '\0') ++prelen;
	while (mid[midlen] != '\0') ++midlen;
	createWithPreOrderAndMidOrder(root, pre, 0, prelen - 1, mid, 0, midlen - 1);
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
	binaryTree<char> a;
	a.createTree('#');
	a.levelOrder();
	a.preOrder();
	a.midOrder();
	a.postOrder();
	return 0;
}
*/

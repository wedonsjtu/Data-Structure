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

public:
	binarySearchTree(binaryNode *t=NULL):root(t) {}
	~binarySearchTree() {makeEmpty(root);}
	bool find(const elemType &x) const {return find(x, root);}
	void insert(const elemType &x) {insert(x, root);}
	void remove(const elemType &x) {remove(x, root);}
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

// ==============================================================

/*
int main() {
	int s[] = {6,4,2,8,45,34,12,57,1,3};
	binarySearchTree<int> a;
	for (int i = 0; i < 10; ++i) a.insert(s[i]);
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

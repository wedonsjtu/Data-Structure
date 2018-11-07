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

template <class elemType>
class linkList: public list<elemType> {
private:
	struct node {
	    elemType data;
		node *next;
		node(const elemType &x, node *p = NULL) {data = x; next = p;}
		node():next(NULL) {}
		~node() {}
	};
	node *head; 
public:
	linkList();
	~linkList() {clear(); delete head;};
	int length() const;
	int search(const elemType &x) const;
	elemType visit(int i) const;
    void insert(int i, const elemType &x); 
    void remove(int i);  
    void clear();
    void traverse() const;
};

template <class elemType>
linkList<elemType>::linkList() {
	head = new node();
}

template <class elemType>
int linkList<elemType>::length() const {
	int len = 0;
	node *p = head->next;
	while (p){
		++len;
		p = p->next;
	}
	return len;
}

template <class elemType>
int linkList<elemType>::search(const elemType &x) const {
	int num = 0;
	node *p = head->next;
	while (p && p->data != x) {
		++num;
		p = p->next;
	}
	if (!p) num = -1;
	return num;
}

template <class elemType>
elemType linkList<elemType>::visit(int i) const {
	node *p = head->next;
	while (i > 0 && p) {
		p = p->next;
		--i;
	}
	if (i < 0 || !p) return -1;
	return p->data;
}

template <class elemType>
void linkList<elemType>::insert(int i, const elemType &x) {
	node *p = head;
	for (int j = 0; j < i; ++j) p = p->next;
	node *tmp = new node(x, p->next);
	p->next = tmp;
	return;
	
	/*
	node *p = head;
	while (p->next) {
		if (p->next->data >= x) break;
		p = p->next;
	}
	node *tmp = new node(x, p->next);
	p->next = tmp;
	*/
}

template <class elemType>
void linkList<elemType>::remove(int i) {
	if (i<0) return;
	node *tmp, *p=head; 
	for (int j = 0; p && (j < i); ++j)  p = p->next;
	if (!p||!p->next) return;
	tmp = p->next;
	p->next = tmp->next; 
	delete tmp;
}

template <class elemType>
void linkList<elemType>::clear() {
	node *p = head->next, *q;
	while (p) {
		q = p;
		p = p->next;
		delete q;
	}
	head->next = NULL;
}

template <class elemType>
void linkList<elemType>::traverse() const {
	node *p = head->next;
	while (p) {
		cout << p->data;
		if (p->next) cout << '\t';
		p = p->next;
	}
}


int main() {
	linkList<int> a;
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

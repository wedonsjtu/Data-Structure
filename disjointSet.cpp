#include <iostream>
using namespace std;

class disjointSet {
private:
	int* parent;
	int size;
public:
	disjointSet(int n);
	disjointSet(int s[], int len);
	~disjointSet() {delete[] parent;}
	void merge(int root1, int root2); // 按规模并，规模越大，根节点值越小（根节点的绝对值越大）
	int find(int x); // 路径压缩，从被查找节点到根节点的路径上所有节点的父亲都被改为根节点
	int findWithoutRecursion(int x); // 路径压缩
	void printDisjointSet();
};

disjointSet::disjointSet(int n) {
	size = n;
	parent = new int[size];
	for (int i=0; i < size; ++i) parent[i] = -1;
}

disjointSet::disjointSet(int s[], int len) {
	size = len;
	parent = new int[size];
	for (int i=0; i < size; ++i) parent[i] = s[i];
}

int disjointSet::find(int x) {
	if (parent[x] < 0) return x;
	parent[x] = find(parent[x]);
	return parent[x];
}

int disjointSet::findWithoutRecursion(int x) {
	int start = x, ret, tmp;
	while (parent[x] >= 0) x = parent[x];
	while (start != x) {
		tmp = start[parent];
		start[parent] = x;
		start = tmp;
	}
	return x;
}

void disjointSet::merge(int root1, int root2) {
	if (root1 == root2) return;
	if (parent[root1] > parent[root2]) {
		parent[root2] += parent[root1];
		parent[root1] = root2;
	}
	else {
		parent[root1] += parent[root2];
		parent[root2] = root1;
	}
}

void disjointSet::printDisjointSet() {
	for (int i=0; i < size; ++i) cout << parent[i] << ' ';
	cout << endl;
}

// ==============================================================

/*
int main() {
	int s[] = {-1, 0, 0, 0, -1, 4, -1, 6, 6, -1, 9, 9, 11, 12, 12};
	int len = sizeof(s) / sizeof(s[0]);
	disjointSet a(s, len);
	a.printDisjointSet();
	a.merge(4, 9);
	a.printDisjointSet();
	cout << a.findWithoutRecursion(12) << endl;
	a.printDisjointSet();
	return 0;
}
*/

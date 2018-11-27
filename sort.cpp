#include <iostream>
using namespace std;

template <class T>
void simpleInsertSort(T a[], int size) {
	int j, k;
	T tmp;
	for (j = 1; j < size; ++j) {
		tmp = a[j];
		for (k = j - 1; tmp < a[k] && k >= 0; --k) a[k+1] = a[k];
		a[k+1] = tmp;
	}
}

//=========================================================

template <class T>
void shellSort(T a[], int size) {
	int step, i, j;
	T tmp;
	for (step = size / 2; step > 0; step /= 2) {
		for (i = step; i < size; ++i) { // similar to simple insert sort
			tmp = a[i];
			for (j = i - step; j >= 0 && a[j] > tmp; j -= step) a[j + step] = a[j];
			a[j + step] = tmp;
		}
	}
}

//=========================================================

template <class T>
void simpleSelectSort(T a[], int size) {
	int i, j, minindex;
	T tmp;
	for (i=0; i < size - 1; ++i) {
		minindex = i;
		for (j = i + 1; j < size; ++j) 
			if (a[j] < a[minindex]) minindex = j;
		tmp = a[i];
		a[i] = a[minindex];
		a[minindex] = tmp;
	}
}

//=========================================================

template <class T>
void percolateDown(T a[], int hole, int size) {
	int child;
	T tmp = a[hole];
	for (; hole * 2 + 1 < size; hole = child) {
		child = hole * 2 + 1;
		if (child != size - 1 && a[child + 1] > a[child]) ++child;
		if (a[child] > tmp) a[hole] = a[child];
		else break;
	}
	a[hole] = tmp;
}

template <class T>
void heapSort(T a[], int size) {
	int i;
	T tmp;
	for (i = size / 2 - 1; i >= 0; --i)
		percolateDown(a, i, size);
	for (i = size - 1; i > 0; --i) {
		tmp = a[0];
		a[0] = a[i];
		a[i] = tmp;
		percolateDown(a, 0, i);
	}
}

//=========================================================

template <class T>
void bubbleSort(T a[], int size) {
	int i, j;
	T tmp;
	bool flag;
	for (i = 1; i < size; ++i) {
		flag = false;
		for (j = 0; j < size - i; ++j) {
			if (a[j+1] < a[j]) {
				tmp = a[j];
				a[j] = a[j+1];
				a[j+1] = tmp;
				flag = true;
			}
		}
		if (!flag) break;
	}
}

//=========================================================

int main() {
	int s[] = {7,4,2,4,8,2,74,21,43,21,65,34,23};
	bubbleSort(s, sizeof(s) / sizeof(s[0]));
	for (int i = 0; i < sizeof(s) / sizeof(s[0]); ++i) {
		cout << s[i] << ' ';
	}
	cout << endl;
}

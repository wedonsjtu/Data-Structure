#include <iostream>
using namespace std;

template <class T>
void insertSort(T a[], int size) {
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
void selectSort(T a[], int size) {
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

template <class T>
int divide(T a[], int low, int high) {
	T k = a[low];
	do {
		while (low < high && a[high] >= k) --high;
		if (low < high) a[low++] = a[high];
		while (low < high && a[low] <= k) ++low;
		if (low < high) a[high--] = a[low];
	}
	while (low != high);
	a[low] = k;
	return low;

}

template <class T>
void qSort(T a[], int low, int high) {
	int mid;
	if (low >= high) return;
	mid = divide(a, low, high);
	qSort(a, low, mid-1);
	qSort(a, mid+1, high);
}

template <class T>
void quickSort(T a[], int size) {
	qSort(a, 0, size-1);
}

//=========================================================

template <class T>
void merge(T a[], int left, int mid, int right) {
	T *tmp = new T[right-left+1];
	int i = left, j = mid, k = 0;
	while (i < mid && j <= right) {
		if (a[i] <= a[j]) tmp[k++] = a[i++];
		else tmp[k++] = a[j++];
	}
	while (i < mid) tmp[k++] = a[i++];
	while (j <= right) tmp[k++] = a[j++];
	for (i=0, k=left; k <= right; k++, i++) a[k] = tmp[i];
	delete[] tmp;
}

template <class T>
void mSort(T a[], int left, int right) {
	int mid = (left + right) / 2;
	if (left == right) return;
	mSort(a, left, mid);
	mSort(a, mid+1, right);
	merge(a, left, mid+1, right);
}

template <class T>
void mergeSort(T a[], int size) {
	mSort(a, 0, size-1);
}

//=========================================================

/*
int main() {
	int s[] = {7,4,2,4,8,2,74,21,43,21,65,34,23};
	mergeSort(s, sizeof(s) / sizeof(s[0]));
	for (int i = 0; i < sizeof(s) / sizeof(s[0]); ++i) {
		cout << s[i] << ' ';
	}
	cout << endl;
}
*/

#include <iostream>
using namespace std;

int sentinelLinearSearch(int a[], int n, int k) {
	int last = a[n - 1];
	a[n - 1] = k;

	int i = 0;
	while (a[i] != k) {
		i++;
	}
	a[n - 1] = last;
	if (i < n - 1 || a[n - 1] == k) {
		return i;
	}
	return -1;
}

int main() {
	int n, k;
	cout << "Nhap so luong phan tu cua mang: ";
	cin >> n;
	int* arr = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	cout << "Nhap so muon tim: ";
	cin >> k;
	int s = sentinelLinearSearch(arr, n, k);
	cout << s;

	delete[] arr;
}
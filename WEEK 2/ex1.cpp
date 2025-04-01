#include <iostream>
using namespace std;

int linearSearch(int a[], int n, int k) {
	for (int i = 0; i < n; i++) {
		if (a[i] == k) {
			return i;
		}
	}
	return -1;
}

int main() {
	int n, k;
	cout << "Nhap so phan tu cua mang: ";
	cin >> n;
	int* arr = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	cout << "Nhap so muon tim : ";
	cin >> k;
	int s = linearSearch(arr, n, k);
	cout << s << endl;
	delete[] arr;
}
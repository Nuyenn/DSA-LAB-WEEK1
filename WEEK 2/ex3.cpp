#include <iostream> 
using namespace std;

int findMin(int nums[], int n) {
	int left = 0, right = n - 1;
	while (left < right) {
		int mid = left + (right - left) / 2;
		if (nums[mid] > nums[right]) {
			left = mid + 1;
		}
		right = mid;
	}
	return nums[left];
}

int main() {
	int n;
	cin >> n;
	int* arr = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	int s = findMin(arr, n);
	cout << s;
	delete[] arr;
	return 0;
}
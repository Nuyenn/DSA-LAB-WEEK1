#include <iostream>
using namespace std;

// Hàm kiểm tra có thể vận chuyển tất cả hàng trong số ngày cho trước với trọng tải quy định sẵn 
bool canShipInDays(int weights[], int n, int days, int capacity) {
	int currentWeight = 0;
	int requiredDays = 1;
	for (int i = 0; i < n; i++) {
		if (currentWeight + weights[i] > capacity) {
			requiredDays++;		//thêm ngày nếu quá tải
			currentWeight = 0;	// trọng lượng về 0
		}
		currentWeight += weights[i];
	}

	return requiredDays <= days;		//kiểm tra số ngày có thỏa mãn không 
}


// Hàm tìm trọng tải tối thiểu bằng nhị phân
int findMinCap(int weights[], int n, int days) {
	int left = 0, right = 0;
	for (int i = 0; i < n; i++) {
		if (weights[i] > left) {
			left = weights[i];		//kiện hàng nặng nhất
			right += weights[i];	// tổng trọng lượng
		}
	}
	int result = right;
	while (left <= right) {
		int mid = (left + right) / 2;
		if (canShipInDays(weights, n, days, mid)) {
			result = mid;
			right = mid - 1;
		}
		else {
			left = mid + 1;
		}
	}
	return result;
}



int main() {
	int n;
	cin >> n;
	int* weights = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> weights[i];
	}

	int days;
	cin >> days;

	cout << findMinCap(weights, n, days) << endl;
	delete[] weights;
	return 0;
}


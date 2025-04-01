#include <iostream>

using namespace std;

// Hàm hoán đổi hai số
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Hàm Quick Sort
int partition(int nums[], int low, int high) {
    int pivot = nums[high];  // Chọn phần tử cuối làm chốt
    int i = low - 1;  // Vị trí của phần tử nhỏ hơn pivot

    for (int j = low; j < high; j++) {
        if (nums[j] < pivot) {  // Đưa các phần tử nhỏ hơn pivot về bên trái
            i++;
            swap(nums[i], nums[j]);
        }
    }
    swap(nums[i + 1], nums[high]);  // Đưa pivot vào đúng vị trí
    return i + 1;
}

void quickSort(int nums[], int low, int high) {
    if (low < high) {
        int pi = partition(nums, low, high);
        quickSort(nums, low, pi - 1);  // Sắp xếp mảng bên trái pivot
        quickSort(nums, pi + 1, high); // Sắp xếp mảng bên phải pivot
    }
}

// Tìm tất cả bộ ba có tổng bằng 0
void threeSum(int nums[], int n) {
    quickSort(nums, 0, n - 1);  // Sắp xếp mảng bằng Quick Sort
    bool found = false;

    for (int i = 0; i < n - 2; i++) {
        if (i > 0 && nums[i] == nums[i - 1]) continue;  // Bỏ qua số trùng lặp
        int left = i + 1, right = n - 1;
        while (left < right) {
            int sum = nums[i] + nums[left] + nums[right];

            if (sum == 0) {
                cout << "[" << nums[i] << "," << nums[left] << "," << nums[right] << "]" << endl;
                found = true;

                // Bỏ qua số trùng nhau
                while (left < right && nums[left] == nums[left + 1]) left++;
                while (left < right && nums[right] == nums[right - 1]) right--;

                left++; right--;  // Tiếp tục tìm bộ ba khác
            }
            else if (sum < 0) left++;   // Cần tổng lớn hơn → tăng left
            else right--;               // Cần tổng nhỏ hơn → giảm right
        }
    }
    if (!found) cout << "Không có bộ ba nào." << endl;
}

int main() {
    int n;
    cin >> n;

    int* nums = new int[n];
    for (int i = 0; i < n; i++) cin >> nums[i];

    threeSum(nums, n);

    delete[] nums;
    return 0;
}

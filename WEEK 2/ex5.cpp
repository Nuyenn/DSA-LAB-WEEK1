#include <iostream>
using namespace std;

int minSubArrLen(int target, int nums[], int n) {
    int left = 0, sum = 0, minLength = n + 1;

    for (int right = 0; right < n; right++) {
        sum += nums[right];
        while (sum >= target) {
            int length = right - left + 1;
            if (length < minLength) minLength = length;
            sum -= nums[left];
            left++;
        }
    }
    return (minLength == n + 1) ? 0 : minLength;
}

int main() {
    int target;
    cin >> target;

    int n;
    cin >> n;

    int* nums = new int[n];
    for (int i = 0; i < n; i++) cin >> nums[i];

    cout << minSubArrLen(target, nums, n) << endl;

    delete[] nums;
    return 0;
}

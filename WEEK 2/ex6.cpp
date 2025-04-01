#include <iostream>

using namespace std;

string hasPairWithSum(int nums[], int n, int target) {
    int left = 0, right = n - 1;

    while (left < right) {
        int sum = nums[left] + nums[right];

        if (sum == target) {
            return "YES";
        }
        else if (sum < target) {
            left++;
        }
        else right--;
    }
    return "NO";
}

int main() {
    int n;
    cin >> n;
    int* nums = new int[n];  
    for (int i = 0; i < n; i++) cin >> nums[i];
    int target;
    cin >> target;
    cout << hasPairWithSum(nums, n, target) << endl;
    delete[] nums;
    return 0;
}

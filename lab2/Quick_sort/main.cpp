#include <iostream>
#include <vector>

using namespace std;



int partition(vector<int>& nums, int low, int high) {
    int pivot = nums[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (nums[j] <= pivot) {
            i++;
            swap(nums[i], nums[j]);
        }
    }
    swap(nums[i + 1], nums[high]);
    return i + 1;
}

void quick_sort(vector<int>& nums, int low, int high) {
    if (low < high) {
        int index = partition(nums, low, high);
        quick_sort(nums, low, index - 1);
        quick_sort(nums, index + 1, high);
    }
}

int main() {
    vector<int> nums = { -2, 1, -3, 4, -1, 2, 1, -5, 4 };

    quick_sort(nums, 0, nums.size() - 1);

    for (int i = 0; i < nums.size(); i++) {
        cout << nums[i] << " ";
    }
    cout << endl;

    return 0;
}


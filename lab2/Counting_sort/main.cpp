#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void counting_sort(vector<int>& nums);

int main(){
    vector<int> nums = { 95, 94, 91, 98, 99, 90, 99, 93, 91, 92 };
    counting_sort(nums);
    for (int i = 0; i < nums.size(); i++) {
        cout << nums[i] << " ";
    }
    cout << endl;

    return 0;
}

void counting_sort(vector<int>& nums) {
    if (nums.empty()) return;

    int min = *min_element(nums.begin(), nums.end());
    int max = *max_element(nums.begin(), nums.end());

    vector<int> count(max - min + 1, 0);
    vector<int> sorted(nums.size());

    for (int i = 0; i < nums.size(); i++) {
        count[nums[i] - min]++;
    }

	for (int i = 0; i < count.size(); i++) {
        cout << count[i] << " ";
    }

	cout << endl;

    for (int i = 1; i < count.size(); i++) {
        count[i] += count[i - 1];
    }

    for (int i = nums.size() - 1; i >= 0; i--) {
        sorted[count[nums[i] - min] - 1] = nums[i];
        count[nums[i] - min]--;
    }

    for (int i = 0; i < nums.size(); i++) {
        nums[i] = sorted[i];
    }
}

#include<bits/stdc++.h>
using namespace std;

int findRepeatedNTimes(const vector<int>& nums) {
    int target = nums.size() / 2;
    unordered_map<int, int> freq;

    for (int x : nums) {
        freq[x]++;
        if (freq[x] == target)
            return x;
    }
    return -1; // guaranteed to exist by problem statement
}
int main() {
    int N;
    cin >> N;

    vector<int> nums(N);
    for (int i = 0; i < N; i++)
        cin >> nums[i];

    int result = findRepeatedNTimes(nums);
    cout << result << "\n";

    return 0;
}
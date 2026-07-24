#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        priority_queue<int> pq;
        unordered_map<int, int> mp;

        for (int i = 0; i < k; i++) {
            pq.push(nums[i]);
            mp[nums[i]]++;
        }

        vector<int> result;
        result.push_back(pq.top());

        for (int i = k; i < nums.size(); i++) {
            mp[nums[i - k]]--;
            if (mp[nums[i - k]] == 0) {
                mp.erase(nums[i - k]);
            }
            pq.push(nums[i]);
            mp[nums[i]]++;
            while (!pq.empty() && mp.find(pq.top()) == mp.end()) {
                pq.pop();
            }
            result.push_back(pq.top());
        }

        return result;
    }
};




int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;
    
    return 0;
}
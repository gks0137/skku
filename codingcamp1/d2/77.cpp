#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> ans;
        vector<int> cur;
        function<void(vector<int>&, int)> track = [&](vector<int>& current, int k_cur){
            if (k_cur == 0) {
                ans.push_back(current);
                return;
            }
            for (int i = (current.empty() ? 1 : current.back()+1); i <= n+1-k_cur; i++) {
                current.push_back(i);
                track(current, k_cur-1);
                current.pop_back();
            }
        };
        track(cur, k);
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "Hello, World!" << endl;

    return 0;
}
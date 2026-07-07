#include <bits/stdc++.h>
using namespace std;




class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        stack<int> st;
        int ans = 0;

        for (int i = 0; i <= n; ++i) {
            while (!st.empty() && (i == n || heights[st.top()] >= heights[i])) {
                int h = heights[st.top()];
                st.pop();
                int w = st.empty() ? i : i - st.top() - 1;
                ans = max(ans, h * w);
            }
            st.push(i);
        }
        return ans;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;

    
    vector<int> heights = {18, 8, 8};
    cout << sol.largestRectangleArea(heights) << endl;



    return 0;
}
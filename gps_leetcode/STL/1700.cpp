#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countStudents(vector<int>& students, vector<int>& sandwiches) {
        queue<int> q;
        for (int i = 0; i < students.size(); i++) {
            q.push(students[i]);
        }
        stack<int> st;
        for (int i = sandwiches.size() - 1; i >= 0; i--) {
            st.push(sandwiches[i]);
        }

        int count = 0;
        while (!q.empty() && !st.empty()) {
            if (q.front() == st.top()) {
                q.pop();
                st.pop();
                count = 0;
            } else {
                int temp = q.front();
                q.pop();
                q.push(temp);
                count++;
            }
            if (count == q.size()) {
                break;
            }
        }
        return q.size();
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);


    vector<int> students = {1,1,0,0};
    vector<int> sandwiches = {0,1,0,1};
    Solution sol;
    cout << sol.countStudents(students, sandwiches) << "\n";



    return 0;
}
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int timeRequiredToBuy(vector<int>& tickets, int k) {
        int time = 0;
        int target = tickets[k];
        for (int i = 0; i < tickets.size(); ++i) {
            if (i <= k) {
                time += min(tickets[i], target);
            } else {
                time += min(tickets[i], target - 1);
            }
        }
        return time;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);


    vector<int> tickets = {2, 3, 2};
    int k = 2;
    Solution sol;
    cout << sol.timeRequiredToBuy(tickets, k) << "\n";



    return 0;
}
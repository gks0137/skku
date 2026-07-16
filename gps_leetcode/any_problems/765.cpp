#include <bits/stdc++.h>
using namespace std;




class Solution {
public:
    int minSwapsCouples(vector<int>& row) {
        int n = row.size();
        for (int i = 0; i < n; ++i) {
            row[i] /= 2;
        }
        int swaps = 0;
        for (int i = 0; i < n; i += 2) {
            if (row[i] != row[i + 1]) {
                swaps++;
                for (int j = i + 1; j < n; ++j) {
                    if (row[j] == row[i]) {
                        swap(row[i + 1], row[j]);
                        break;
                    }
                }
            }
        }
        return swaps;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;


    return 0;
}
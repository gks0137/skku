#include <bits/stdc++.h>
using namespace std;

class Solution {
    public:
    unordered_map<int, vector<vector<int>>>dp;
    int r;

    vector<vector<int>> calc_matrix_square(vector<vector<int>>& a, vector<vector<int>>& b) {
        vector<vector<int>> mtrx(r, vector<int>(r, 0));
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < r; j++) {
                for (int k = 0; k < r; k++) {
                    long long temp = (long long)a[i][k] * b[k][j];
                    temp %= 1000000007;
                    mtrx[i][j] += temp;
                    mtrx[i][j] %= 1000000007;
                }
            }
        }
        return mtrx;
    }

    int zigZagArrays(int n, int l, int r) {
        r -= l;
        l = 0;
        this->r = r;
        dp[1] = vector<vector<int>>(r, vector<int>(r, 0));
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < r; j++) {
                if (i+j+1 >= r) {
                    dp[1][i][j] = 1;
                }
            }
        }

        int i;
        for (i = 2; i < n; i <<= 1) {
            dp[i] = calc_matrix_square(dp[i >> 1], dp[i >> 1]);
        }
        n -= 1;
        int s = n & -n;
        vector<vector<int>> mtrx = dp[s];
        //
        // cout << "i: " << i << ", n: " << n << ", s: " << s << "\n";
        // for (int j = 0; j < r; j++) {
        //     for (int k = 0; k < r; k++) {
        //         cout << mtrx[j][k] << " ";
        //     }
        //     cout << "\n";
        // }

        //
        n -= s;
        while (n) {
            i >>= 1;
            if (n & i) {
                n -= i;
                mtrx = calc_matrix_square(dp[i], mtrx);
            }
        }
        int sum = 0;
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < r; j++) {
                sum += mtrx[i][j];
                sum %= 1000000007;
            }
        }
        return sum;
    }
};



int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;

    int n = 3, l = 1, r = 3;
    cout << sol.zigZagArrays(n, l, r) << "\n";



    return 0;
}
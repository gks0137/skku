#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int totalNQueens(int n) {
        int solutions_count = 0;
        unsigned short N = (1 << n) - 1;

        std::function<void(unsigned short, short, short, short)> backtrack;
        backtrack = [&](unsigned short row, short cols, short diag1, short diag2) {
            row--; //move to the next row
            
            short available = N & ~(cols | diag1 | diag2);
            
            while (available) {
                if (!row) { 
                    solutions_count++;
                    return;
                }
                short pos = available & -available; //rightmost set bit
                backtrack(row, cols | pos, (diag1 | pos) >> 1, (diag2 | pos) << 1);
                available ^= pos; //remove the rightmost set bit
            }
        };
        backtrack(n, 0, 0, 0);

        return solutions_count;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;


    int n = 8; // Example for 8 queens
    int result = sol.totalNQueens(n);
    cout << "Number of solutions for " << n << "-Queens: " << result << "\n";
    return 0;
}
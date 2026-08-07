#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int n = obstacleGrid.size(), m = obstacleGrid[0].size();
        if (obstacleGrid[0][0] == 1 || obstacleGrid[n - 1][m - 1] == 1) {
            return 0;
        }
        obstacleGrid[0][0] = 1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (obstacleGrid[i][j] == 1 && (i != 0 || j != 0)) {
                    obstacleGrid[i][j] = 0;
                    continue;
                }
                if (i > 0) {
                    obstacleGrid[i][j] += obstacleGrid[i - 1][j];
                }
                if (j > 0) {
                    obstacleGrid[i][j] += obstacleGrid[i][j - 1];
                }
            }
        }
        return obstacleGrid[n - 1][m - 1];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;


    return 0;
}
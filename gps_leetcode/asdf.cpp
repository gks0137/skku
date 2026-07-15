#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        vector<int> parent(n + 1);
        for (int i = 1; i <= n; ++i) {
            parent[i] = i;
        }

        function<int(int)> find = [&](int x) {
            if (parent[x] != x) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        };
        
        vector<int> result;

        for (const auto& edge : edges) {
            int u = edge[0], v = edge[1];
            int pu = find(u), pv = find(v);
            if (pu == pv) {
                result = edge;
            }
            parent[pu] = pv;
        }

        return result;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;

    
    vector<vector<int>> edges = {{1, 2}, {1, 3}, {2, 3}};
    vector<int> result = sol.findRedundantConnection(edges);
    cout << "[" << result[0] << ", " << result[1] << "]" << endl;




    return 0;
}
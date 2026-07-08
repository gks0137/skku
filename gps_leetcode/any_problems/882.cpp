#include <bits/stdc++.h>
using namespace std;




class Solution {
public:
    int reachableNodes(vector<vector<int>>& edges, int maxMoves, int n) {
        vector<vector<pair<int, int>>> edgesList(n);
        for (auto &edge : edges) {
            edgesList[edge[0]].push_back({edge[1], edge[2]});
            edgesList[edge[1]].push_back({edge[0], edge[2]});
        }
        vector<int> nodes(n, -1); // remaining moves
        nodes[0] = maxMoves;

        priority_queue<pair<int, int>> pq; // remaining moves, node
        pq.push({maxMoves, 0});

        while (!pq.empty()) {
            auto [moves, node] = pq.top();
            pq.pop();

            if (moves < nodes[node]) continue; // already visited

            for (auto [neighbor, weight] : edgesList[node]) {
                if (moves >= weight) {
                    int remainingMoves = moves - weight - 1;
                    if (remainingMoves > nodes[neighbor]) {
                        nodes[neighbor] = remainingMoves;
                        pq.push({remainingMoves, neighbor});
                    }
                }
            }
        }
        int ans = 0;
        for (auto move : nodes) {
            if (move >= 0) ans++;
        }
        for (auto &edge : edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            int uMoves = nodes[u] >= 0 ? nodes[u] : 0;
            int vMoves = nodes[v] >= 0 ? nodes[v] : 0;
            ans += min(w, uMoves + vMoves);

        }
        return ans;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;

    
    vector<vector<int>> edges = {{0,1,10},{0,2,1},{1,2,2}};
    int maxMoves = 6;
    int n = 3;
    cout << sol.reachableNodes(edges, maxMoves, n) << endl;

    return 0;
}
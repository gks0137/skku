#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    // bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
    //     vector<int> nodes(n+1);
    //     for (int i = 0; i < n; i++) {
    //         nodes[i] = i;
    //     }
    //     function<int(int)> find = [&](int x) {
    //         if (nodes[x] != x) {
    //             nodes[x] = find(nodes[x]);
    //         }
    //         return nodes[x];
    //     };
    //     function<void(int, int)> merge = [&](int a, int b) {
    //         nodes[find(a)] = find(b);
    //     };
    //     for (const auto& edge : edges) {
    //         merge(edge[0], edge[1]);
    //     }
    //     return find(source) == find(destination);
    // }
    int *p;
    int find(int x) {
        if (p[x] != x) {
            p[x] = find(p[x]);
        }
        return p[x];
    }
    void merge(int a, int b) {
        p[find(a)] = find(b);
    }

    bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
        int *p = new int[n];
        this->p = p;
        for (int i = 0; i < n; i++) {
            p[i] = i;
        }
        for (const auto& edge : edges) {
            merge(edge[0], edge[1]);
        }
        bool result = find(source) == find(destination);
        delete[] p;
        return result;
    }
};




int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    Solution sol;


    return 0;
}
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int TC; cin >> TC;
    while (TC--) {
        int n, k;
        cin >> n >> k;
        vector<int> nodes(n+1, -1);
        vector<vector<int>> adj(k);
        for (int i = 0; i < k; i++) {
            int c; cin >> c;
            adj[i] = vector<int>(c);
            for (int j = 0; j < c; j++) {
                cin >> adj[i][j];
            }
            sort(adj[i].begin(), adj[i].end());
        }

        int ans = 1;
        for (int i = 1; i <= n; i++) {
            vector<int*> pointers(k, nullptr);
            for (int j = 0; j < k; j++) {
                if (binary_search(adj[j].begin(), adj[j].end(), i)) {
                    pointers[j] = &adj[j][0];
                }
            }
            int min_not_in = 1;
            while (1) {
                bool found = false;
                for (int j = 0; j < k; j++) {
                    int *ptr = pointers[j];
                    if (ptr == nullptr) continue;

                    while (*ptr < i && nodes[*ptr] < min_not_in) {
                        if (ptr == &adj[j][adj[j].size() - 1]) break;
                        ptr++;
                    }
                    if (nodes[*ptr] == min_not_in) {
                        found = true;   
                        break;
                    }
                }
                if (!found) break;
                min_not_in++;
            }

            nodes[i] = min_not_in;
            
            ans = max(ans, min_not_in);

        }
        cout << ans << "\n";


    }



    return 0;
}
#include <iostream>
#include <deque>
#include <vector>




int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
    
    int n, m;
    std::cin >> n >> m;
    
    std::vector<std::vector<int>> adj(n);
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            adj[i].push_back(-1);
        }
    }
    for (int i=0; i<m; i++) {
        int a, b, c;
        std::cin >> a >> b >> c;
        adj[a-1][b-1] = std::max(adj[a-1][b-1], c);
        adj[b-1][a-1] = std::max(adj[b-1][a-1], c);
    }

    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            for (int k=0; k<n; k++) {

                if (adj[j][i]==-1) continue;
                if (adj[i][k]==-1) continue;

                adj[j][k] = std::max(adj[j][k], std::min(adj[j][i], adj[i][k]));
            }
        }
    }




    int q;
    std::cin >> q;
    for (int i=0; i<q; i++) {
        int start, end;
        std::cin >> start >> end;

        
        
        std::cout << adj[start-1][end-1] << "\n";

    }



    return 0;
}
    #include <iostream>
    #include <vector>
    using namespace std;

    int main() {
        std::ios::sync_with_stdio(false);
        std::cin.tie(NULL);
        std::cout.tie(NULL);


        int n, m;
        cin >> n >> m;
        vector<vector<int>> period_sum(n + 1, vector<int>(n + 1, 0));
        vector<int> column_sum(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                int num;
                cin >> num;
                column_sum[j] += num;
                period_sum[i][j] = column_sum[j] + period_sum[i][j-1];
            }
        }

        // for (int i = 1; i <= n; i++) {
        //     for (int j = 1; j <= n; j++) {
        //         cout << period_sum[i][j] << " ";
        //     }
        //     cout << "\n";
        // }

        while (m--) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            
            cout << period_sum[x2][y2] - period_sum[x2][y1-1] - period_sum[x1-1][y2] + period_sum[x1-1][y1-1] << "\n";
        }

        

        return 0;
    }

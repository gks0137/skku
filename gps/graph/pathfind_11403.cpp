#include <iostream>
#include <vector>
using namespace std;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);


    int n;
    std::cin >> n;
    vector<vector<int>> adjacency_matrix(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> adjacency_matrix[i][j];
        }
    }

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (adjacency_matrix[i][j] == 1 || (adjacency_matrix[i][k] == 1 && adjacency_matrix[k][j] == 1)) {
                    adjacency_matrix[i][j] = 1;
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << adjacency_matrix[i][j] << " ";
        }
        std::cout << "\n";
    }

    return 0;
}

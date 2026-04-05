#include <iostream>
#include <vector>
#include <algorithm>

char dir[4] = {'U', 'R', 'D', 'L'};

void snake(int x, const int dir1_idx, const int dir2_idx) {
    const char dir1_opp = dir[(dir1_idx + (x%2==0 ? 2 : 0))%4];
    const char dir1 = dir[dir1_idx], dir2 = dir[dir2_idx];



}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int n, m, min=1000;
    int min_ij[2];
    std::cin >> n >> m;
    int array[n][m];
    

    for (int i = 0; i<n; i++) {
        for (int j = 0; j<m; j++) {
            int aij;
            std::cin >> aij;
            array[i][j] = aij;

            if ((i+j)%2 == 1) {
                if (aij < min) {
                    min = aij;
                    min_ij[0] = i;
                    min_ij[1] = j;
                }
            }
        }
    }

    std::cout << min << std::endl << min_ij[0] << min_ij[1];


    return 0;
}

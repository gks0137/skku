#include <iostream>
#include <vector>
#include <cmath>


std::vector<std::vector<char>> arr;
int N;
int max_x, max_y;

void make_pattern(int cur_length, int x, int y, int updown) {
    if (cur_length == 1) {
        return;
    }

    if (updown==1) {
        for (int i=0; i<)

    }
    


}


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N;

    max_y = pow(2, N) - 1;
    max_x = pow(2, N+1) - 3;

    arr.resize(max_y + 1, std::vector<char>(max_x, ' '));
    make_pattern(max_y, N-1, 0);

    for (int i=0; i <= max_y; i++) {
        for (int j=0; j <= max_x; j++) {
            std::cout << arr[i][j];
        }
        std::cout << "\n";
    }
















    return 0;
}
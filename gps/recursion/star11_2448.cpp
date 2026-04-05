#include <iostream>
#include <vector>


std::vector<std::vector<char>> arr;
int max_length, N;

void make_pattern(int cur_length, int x, int y) {
    if (cur_length == 0) {
        arr[y][x] = '*';
        if (y%3==1) {
            arr[y+1][x] = '*';
            arr[y+1][x-1] = '*';
            arr[y+1][x+1] = '*';
        }
        return;
    }
    
    
    arr[y][x] = '*';



    make_pattern(cur_length/2, x, y);
    make_pattern(cur_length/2, x - cur_length/4, y + cur_length/4);
    make_pattern(cur_length/2, x + cur_length/4, y + cur_length/4);
}


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N;

    max_length = 2*N;

    arr.resize(N, std::vector<char>(2*N, ' '));
    make_pattern(max_length, N-1, 0);

    for (int i=0; i < N; i++) {
        for (int j=0; j < 2*N; j++) {
            std::cout << arr[i][j];
        }
        std::cout << "\n";
    }
















    return 0;
}
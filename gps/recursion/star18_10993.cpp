#include <iostream>
#include <vector>


std::vector<std::vector<char>> arr;
int N;
int max_x, max_y;

int pow(int a, int b) {
    int result = 1;
    for (int i=0; i < b; i++) {
        result *= a;
    }
    return result;
}

void make_pattern(int cur_length, int x, int y, int updown) {
    if (cur_length == 1) {
        arr[y][x] = '*';
        return;
    }

    if (updown==1) {
        for (int i=0; i < cur_length; i++) {
            arr[y+i][x+i] = '*';
            arr[y+i][x-i] = '*';
            arr[y+cur_length-1][x+i] = '*';
            arr[y+cur_length-1][x-i] = '*';
        }
        make_pattern(cur_length/2, x, y+cur_length-2, -1);
    } else {
        for (int i=0; i < cur_length; i++) {
            arr[y-i][x+i] = '*';
            arr[y-i][x-i] = '*';
            arr[y-cur_length+1][x+i] = '*';
            arr[y-cur_length+1][x-i] = '*';
        }
        make_pattern(cur_length/2, x, y-cur_length+2, 1);
    }
    
    
    


}


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N;

    max_y = pow(2, N) - 1;
    max_x = pow(2, N+1) - 3;

    arr.resize(max_y, std::vector<char>(max_x, ' '));
    make_pattern(max_y, max_x/2, N%2==0 ? max_y-1 : 0, N%2==0 ? -1 : 1);

    for (int i=0; i < max_y; i++) {
        int end = 1+max_x/2 + (N%2==0 ? max_x/2 - i : i);
        for (int j=0; j < end; j++) {
            std::cout << arr[i][j];
        }
        std::cout << "\n";
    }
















    return 0;
}
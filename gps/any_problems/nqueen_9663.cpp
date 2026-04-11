#include <iostream>
#include <vector>
using namespace std;

int N;

vector<unsigned short> place_queen(vector<unsigned short> cur_board, pair<int, int> pos) {

    for (int i = 0; i < N; i++) {
        int attacked_pos[] = {
            -1, 
            pos.second, // vertical
            -1, -1
        };
        if (pos.second - pos.first + i >= 0 && pos.second - pos.first + i < N) {
            attacked_pos[2] = pos.second - pos.first + i; // diagonal right down
        }
        if (pos.second + pos.first - i >= 0 && pos.second + pos.first - i < N) {
            attacked_pos[3] = pos.second + pos.first - i; // diagonal left down
        }
        for (int j = 0; j < 4; j++) {
            if (attacked_pos[j] != -1) {
                cur_board[i] |= (1U << attacked_pos[j]);
            }
        }
    }
    return cur_board;
}

int n_queens(int n, int row, const vector<unsigned short>& board) {
    int count = 0;
    unsigned short temp_pos = 1U;
    
    if (n == 1) {
        for (int i = 0; i < N; i++) {
            if ((board[row] & temp_pos) == 0) {
                count++;
            }
            if (i % N == N - 1) {
                break;
            }
            temp_pos <<= 1;
        }
        
        return count;
    }
    for (int i = 0; i < N; i++) {
        if ((board[row] & temp_pos) == 0) {
            vector<unsigned short> new_board = place_queen(board, {row, i});
            count += n_queens(n - 1, row + 1, new_board);
        }
        if (i % N == N - 1) {
            break;
        }
        temp_pos <<= 1;
    }
    return count;
}



int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);


    cin >> N;
    cout << n_queens(N, 0, vector<unsigned short>(N, 0)) << "\n";
    
    


    return 0;
}

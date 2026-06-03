#include <iostream>
#include <deque>
#include <vector>

int N;
std::vector<std::vector<int>> map;
//x, y, 학점, stress, 문풀, 탈출
std::vector<std::vector<int>> student;




int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int K, L, R, S, P, Q, D;
    std::cin >> N >> K >> L >> R >> S >> P >> Q >> D;

    std::cout << "\n123412342134\n";
    
    for (int i; i<N; i++) {
        map.push_back({});
        for (int j; j<N; j++) {
            int temp;
            std::cin >> temp;
            map[i].push_back(temp);
        }
    }

    return 0;

}
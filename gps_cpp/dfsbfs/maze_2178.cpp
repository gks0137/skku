#include <iostream>
#include <deque>
#include <vector>
#include <string>

int n, m;

void push_valid(std::deque<std::pair<std::pair<int, int>, int>>& queue, std::vector<std::vector<int>>& map, std::pair<int, int> xy, int c) {
    int col=xy.second;
    for (int row : {xy.first-1, xy.first+1}) {
        if (0<=row && row<n) {
                if (map[row][col]==1) {
                    queue.push_back({{row, col}, c+1});
                    map[row][col] = 0;
            }
        }
    }
    int row = xy.first;
    for (int col : {xy.second+1, xy.second-1}){
        if (0<=col && col<m) {
            if (map[row][col]==1) {
                queue.push_back({{row, col}, c+1});
                map[row][col] = 0;
            }
        }
    }
}


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> n >> m;
    std::vector<std::vector<int>> map(n); 
    std::pair<int, int> destin = {n-1, m-1};

    for (int i = 0; i < n; i++) {
        std::string t;
        std::cin >> t;
        for (int j = 0; j < m; j++) {
            map[i].push_back(t[j] == '0' ? 0 : 1);
        }
    }

    // // Print output
    // for(int i = 0; i < n; i++){
    //     for(int j = 0; j < m; j++){
    //         std::cout << map[i][j];
    //     }
    //     std::cout << "\n";
    // }


    //bfs

    std::deque<std::pair<std::pair<int, int>, int>> queue;

    map[0][0] = 0;
    push_valid(queue, map, {0, 0}, 1);
    
    while (!queue.empty())
    {
        auto v = queue.front();
        queue.pop_front();

        //std::cout << v.first.first << v.first.second << ' ' << v.second << "\n";

        if (v.first == destin) {
            std::cout << v.second;
            return 0;
        } else {
            push_valid(queue, map, v.first, v.second);
        }
    }

    return 0;
}
#include <iostream>
#include <deque>
#include <vector>
#include <tuple>

int m, n, h;
std::vector<int> box = {};
std::vector<int> visited = {};

int get_val(std::vector<int>& box, std::tuple<int, int, int> pos){
    int i = std::get<0>(pos) + std::get<1>(pos)*m + std::get<2>(pos)*n*m;
    return box[i];
}

void set_val(std::vector<int>& box, std::tuple<int, int, int> pos, int val){
    int i = std::get<0>(pos) + std::get<1>(pos)*m + std::get<2>(pos)*n*m;
    box[i] = val;
}

std::vector<std::tuple<int, int, int>> get_adjacent(std::tuple<int, int, int> pos);

void push_valid(std::deque<std::pair<std::tuple<int, int, int>, int>>& queue, std::tuple<int, int, int> pos, int c);

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> m >> n >> h;
    std::deque<std::pair<std::tuple<int, int, int>, int>> queue;


    for(int _=0; _<m*n*h; _++) {
        int temp;

        std::cin >> temp;
        box.push_back(temp);
        visited.push_back(temp==0 ? 0 : 1);
    }

    


    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            for (int k=0; k<h; k++) {
                if (get_val(box, {i, j, k})==1) {
                    push_valid(queue, {i, j, k}, 0);
                }
            }
        }
    }
    
    int c = 0;
    while (!queue.empty())
    {
        auto v = queue.front();
        queue.pop_front();
        c = v.second;

        //std::cout << v.first.first << v.first.second << ' ' << v.second << "\n";

        push_valid(queue, v.first, v.second);
    }

    for(int i=0; i<m*n*h; i++) {
        if (box[i]==0 && visited[i]==0) {
            std::cout << -1;
            return 0;
        }
    }
    std::cout << c;



    return 0;
}

std::vector<std::tuple<int, int, int>> get_adjacent(std::tuple<int, int, int> pos) {
    std::vector<std::tuple<int, int, int>> adjacents;
    
    // 현재 좌표 추출
    int x = std::get<0>(pos);
    int y = std::get<1>(pos);
    int z = std::get<2>(pos);

    // 6방향 탐색을 위한 방향 배열 (상, 하, 좌, 우, 앞, 뒤)
    int dx[] = {1, -1, 0, 0, 0, 0};
    int dy[] = {0, 0, 1, -1, 0, 0};
    int dz[] = {0, 0, 0, 0, 1, -1};

    // 6방향을 돌며 유효한 좌표인지 검사
    for (int i = 0; i < 6; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        int nz = z + dz[i];

        // 좌표가 n * m * h 범위 내에 있는지 확인 (0-based index 기준)
        if (nx >= 0 && nx < m && ny >= 0 && ny < n && nz >= 0 && nz < h) {
            adjacents.push_back({nx, ny, nz});
        }
    }

    return adjacents;
}

void push_valid(std::deque<std::pair<std::tuple<int, int, int>, int>>& queue, std::tuple<int, int, int> pos, int c){
    auto temp = get_adjacent(pos);
    for (auto where : temp) {
        if (get_val(visited, where)==0){
            set_val(visited, where, 1);
            queue.push_back({where, c+1});
        }
    }
}
#include <iostream>
#include <deque>
#include <vector>

int N, K;
std::vector<std::vector<int>> map;
//x, y, 학점, stress, 문풀, 탈출
std::vector<std::vector<int>> student;

std::vector<std::pair<int, int>> get_adj(std::pair<int, int> pos){
    std::vector<std::pair<int, int>> adj;

    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, 1, 0, -1};

    for (int i=0; i<4; i++) {
        int x = pos.first + dx[i];
        int y = pos.second + dy[i];

        if (0<=x && x<N && 0<=y && y<N) {
            adj.push_back({x, y});
        }
    }
    return adj;
}

void push_valid(std::deque<std::pair<int, int>>& queue, std::vector<std::vector<bool>>& visited, std::pair<int, int> pos, bool finding_samsumg = false) {
    std::vector<std::pair<int, int>> adj = get_adj(pos);

    for (std::pair<int, int> xy : adj) {
        if ((finding_samsumg ? (map[xy.first][xy.second]!=-1) : (map[xy.first][xy.second]>=0))) {
            if (!visited[xy.first][xy.second]) {
                queue.push_back(xy);
                visited[xy.first][xy.second] = true;

            }
        }
    }
}

std::pair<int, int> bfs(std::pair<int, int> pos, int what) {
    std::deque<std::pair<int, int>> queue;
    std::vector<std::vector<bool>> visited;
    for (int i=0; i<N; i++) {
        std::vector<bool> temp(N);
        visited.push_back(temp);
    }

    push_valid(queue, visited, pos, what==-2);
    visited[pos.first][pos.second] = true;
    while (!queue.empty())
    {   
        std::pair<int, int> v = queue.front();
        queue.pop_front();

        if (map[v.first][v.second] == what) return v;

        push_valid(queue, visited, v);
    }
    return pos;
}

std::pair<int, int> bfs_assign(std::pair<int, int> pos) {
    std::deque<std::pair<int, int>> queue;
    std::vector<std::vector<bool>> visited(N);
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            visited[i].push_back(false);
        }
    }

    push_valid(queue, visited, pos);
    visited[pos.first][pos.second] = true;
    while (!queue.empty())
    {   
        std::pair<int, int> v = queue.front();
        queue.pop_front();

        if (0<map[v.first][v.second] && map[v.first][v.second]<=100) return v;

        push_valid(queue, visited, v);
    }
    return pos;
}

std::vector<std::pair<int, int>>  bfs_all(std::pair<int, int> pos, int dist_max) {
    std::vector<std::pair<int, int>> all;
    std::deque<std::pair<int, int>> queue;
    std::vector<std::vector<bool>> visited;
    for (int i=0; i<N; i++) {
        std::vector<bool> temp(N);
        visited.push_back(temp);
    }

    push_valid(queue, visited, pos);
    visited[pos.first][pos.second] = true;


    for (int i=0; i<dist_max; i++) {
        int len = queue.size();
        for (int j=0; j<len; j++) {

            std::pair<int, int> v = queue.front();
            queue.pop_front();
            all.push_back(v);

            push_valid(queue, visited, v);

        }


    }
    return all;
}

int get_student(std::pair<int, int> pos) {

    
    for (int i=0; i<K; i++){
        if (student[i][0] == pos.first && student[i][1] == pos.second){
            return i;
        }
    }
    return -1;
}



int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int L, R, S, P, Q, D;
    std::cin >> N >> K >> L >> R >> S >> P >> Q >> D;

    int escaped;

    for (int i=0; i<N; i++) {
        map.push_back({});
        for (int j=0; j<N; j++) {
            int temp;
            std::cin >> temp;
            map[i].push_back(temp);
        }
    }
    int prof_x, prof_y;
    std::cin >> prof_x >> prof_y;
    std::pair<int, int> prof_pos = {prof_x-1, prof_y-1};
    for (int i=0; i<K; i++) {
        int x, y, g;
        std::cin >> x >> y >> g;
        x--;
        y--;
        student.push_back({x, y, g, 0, 0, 0, 0});
        map[x][y] = 200;
    }

    std::pair<int, int> temp_pos;


    //sdghjfsghuwijjihkbfjewkjk


    for (int asdf=0; asdf<L; asdf++){
    //1. prof move
    prof_pos = bfs(prof_pos, 200);

    //2. assign
    std::vector<std::pair<int, int>> assigning = bfs_all(prof_pos, R);
    for (std::pair<int, int> xy : assigning) {
        if (map[xy.first][xy.second]==0) {
            map[xy.first][xy.second] = D;
        }
    }

    //3. contact
    int dx[] = {0, -1, 0, 1, 0};
    int dy[] = {0, 0, 1, 0, -1};

    for (int i=0; i<5; i++) {
        int x = prof_pos.first + dx[i];
        int y = prof_pos.second + dy[i];

        if (x==prof_pos.first && y==prof_pos.second) continue;

        if (x<0 || N<=x || y<0 || N<=y) continue;

        if (map[x][y] == 200) {
            int idx = get_student(prof_pos);
            //if (idx==-1) continue;
            if (student[idx][4]==0) {
                if (student[idx][2] < 30) {
                    student[idx][5] = -1;
                } else {
                    student[idx][3] += P;
                    if (student[idx][3] > S) {
                        student[idx][5] = -1;
                    }
                }
            }
        }
    }

    //4. stress
    for (std::vector<int> stud : student) {
        stud[3] += 1;
        if (stud[3] > S) {
            stud[5] = -1;
        }
    }

    //5. student move
    bool print = true;
    std::vector<float> print_queue;
    for (int i=0; i<K; i++) {

        if (student[i][5] == -1)continue;

        if (student[i][4] == 0) {
            std::pair<int, int> stud_pos = {student[i][0], student[i][1]};
            if (student[i][2] >= 40) {
                temp_pos = bfs(stud_pos, -2);
                map[student[i][0]][student[i][1]] = 0;
                if (map[temp_pos.first][temp_pos.second] != -2) {
                    map[student[i][0]][student[i][1]] = 200;
                    continue;
                }
                student[i][0] = temp_pos.first;
                student[i][1] = temp_pos.second;
                escaped ++;
                student[i][5] = escaped;
                print = false;
                print_queue.push_back((float)student[i][2]/10);
            } else {
                temp_pos = bfs_assign(stud_pos);
                student[i][0] = temp_pos.first;
                student[i][1] = temp_pos.second;
                student[i][6] = map[temp_pos.first][temp_pos.second];
                student[i][4] = map[temp_pos.first][temp_pos.second];
                map[temp_pos.first][temp_pos.second] = 200;

                
            }
        }
        if (student[i][4]!=0) {
            map[student[i][0]][student[i][1]] = 201;
            student[i][4] -= 10;
            if (student[i][4] <= 0) {
                student[i][4] = 0;
                int acc = (student[i][6] * (100 - student[i][3])) / 100;
                student[i][2] = std::min(45, student[i][2] + acc);
                student[i][3] = std::max(0, student[i][3] - Q);
                map[student[i][0]][student[i][1]] = 200;
            }
        }
    }

    //7. run

    //8. print
    if (!print) {
        std::cout << print_queue.size();
        for (float v : print_queue) {
            std::cout << ' ';
            std::cout.width(3);
            std::cout << v;
        }
    } else {
        std::cout << 0 << "\n";
    }

    }

    return 0;
}
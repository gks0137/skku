#include <bits/stdc++.h>
#define Wall 999999
using namespace std;



vector<vector<int>> grid; // -1 wall 0 empty 
int n;

int dx[] = {0, 0, -1, 1};
int dy[] = {1, -1, 0, 0};

class virus {
public:
    int strength;
    int virus_i;
    deque<pair<int, int>> q;
    deque<pair<int, int>> replace_q;
    vector<vector<bool>> visited;


    void replace_all() {
        for (auto [x, y] : replace_q) {
            grid[x][y] = this->strength;
        }
        replace_q.clear();
    }

    bool spread_bfs_1() {
        bool spreaded = false;
        int qq = q.size();
        for (int i = 0; i < qq; i++) {
            auto [x, y] = q.front();
            q.pop_front();
            if (grid[x][y] != this->strength) continue;

            for (int _ = 0; _ < 4; _++) {
                int nx = x+2*dx[_], wx = x+dx[_];
                int ny = y+2*dy[_], wy = y+dy[_];
                if (nx < 0 || n <= nx || ny < 0 || n <= ny) continue;
                if (grid[wx][wy] == 0 && !visited[nx][ny]) {
                    visited[nx][ny] = true;
                    int g = grid[nx][ny];
                    if (g < this->strength) {
                        replace_q.push_back({nx, ny});
                        q.push_back({nx, ny});
                        if (g == 0) spreaded = true;
                    }
                }
            }
        }
        return spreaded;
    }


};

virus *make_virus(int strength, int x, int y, int virusnum) {
    virus *nvirus = new virus;
    nvirus->strength = strength;
    nvirus->virus_i = virusnum;
    nvirus->visited.resize(n, vector<bool>(n, false));
    x = 2*x-1;
    y = 2*y-1;
    nvirus->visited[x][y] = true;
    nvirus->q.push_back({x, y});
    grid[x][y] = strength;
    return nvirus;
}


pair<int, int> get_dir(char c) {
    switch (c) {
        case 'U':
            return {-1, 0};
        case 'D':
            return {1, 0};
        case 'R':
            return {0, 1};
        case 'L':
            return {0, -1};
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int k, m;
    cin >> n >> k >> m;
    n = 2*n+1;
    grid.resize(n, vector<int>(n, 0));


    vector<virus*> viruses(k);
    for (int i = 0; i < k; i++) {
        int s, x, y;
        cin >> x >> y >> s;
        viruses[i] = make_virus(s, x, y, i);
    }
    sort(viruses.begin(), viruses.end(), [](virus *a, virus *b){return a->strength < b->strength;});

    while (m--) {
        int x, y;
        cin >> x >> y;
        x = 2*x-1;
        y = 2*y-1;
        grid[x][y] = Wall;
    }

    int q;
    cin >> q;

    deque<pair<int, pair<int, int>>> queue;
    while (q--) {
        int t, r, c; char d;
        cin >> t >> r >> c >> d;
        auto [x, y] = get_dir(d);
        r = 2*r-1+x;
        c = 2*c-1+y;
        queue.push_back({t, {r, c}});
    }
    ////////////////////////////////////////////////////////////////////////////////////////////

    int t = 0;
    while (true) {
        t++;
        while (!queue.empty() && queue.front().first == t) {
            auto [x, y] = queue.front().second;
            queue.pop_front();
            grid[x][y] = Wall;
        }

        for (virus *v : viruses) {
            v->replace_all();
        }
        
        bool cur_flag = false;

        for (virus* v : viruses) {
            bool tmp;
            tmp = v->spread_bfs_1();
            if (tmp) cur_flag = true;
        }




        if (!cur_flag) break;
        
    }

    vector<int> res(k+1, 0);
    for (int i = 1; i < n; i+=2) {
        for (int j = 1; j < n; j+=2) {
            int g = grid[i][j];
            // cout << g << ' ';
            if (g == 0 || g == Wall) continue;
            res[g]++;
        }
        // cout << "\n";
    }
    sort(viruses.begin(), viruses.end(), [](virus *a, virus *b){return a->virus_i < b->virus_i;});

    for (virus* v : viruses) {
        cout << res[v->strength] << "\n";
    }













    return 0;
}
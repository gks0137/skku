#include <iostream>
#include <deque>
#include <vector>
using namespace std;

int n, m;
vector<vector<int>> world;
vector<deque<int>> dice = {
    {-1, 0, -1}, 
    {0, 0, 0}, 
    {-1, 0, -1},
    {-1, 0, -1}
};
int dice_x, dice_y;

void roll_dice(const int dir) {
    int temp;
    switch (dir)
    {
    case 2:
        dice[1].push_back(dice[3][1]);
        dice[3][1] = dice[1][0];
        dice[1].pop_front();
        dice_y--;
        break;
    case 1:
        dice[1].push_front(dice[3][1]);
        dice[3][1] = dice[1][3];
        dice[1].pop_back();
        dice_y++;
        break;
    case 3:
        temp = dice[0][1];
        for (int i = 0; i < 3; i++) {
            dice[i][1] = dice[i+1][1];
        }
        dice[3][1] = temp;
        dice_x--;
        break;
    case 4:
        temp = dice[3][1];
        for (int i = 3; i > 0; i--) {
            dice[i][1] = dice[i-1][1];
        }
        dice[0][1] = temp;
        dice_x++;
        break;
    default:
        cout << "error\n";
        break;
    }
}



int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int K;
    cin >> n >> m >> dice_x >> dice_y >> K;
    world.resize(n, vector<int>(m, 0));

    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            int temp;
            cin >> temp;
            world[i][j] = temp;
        }
    }


    while (K--) {
        int dir;
        cin >> dir;
        
        int nx = dice_x, ny = dice_y;
        if (dir == 1) ny++;
        else if (dir == 2) ny--;
        else if (dir == 3) nx--;
        else if (dir == 4) nx++;

        if (nx < 0 || nx >= n || ny < 0 || ny >= m) {
            continue;
        }

        roll_dice(dir);

        if (world[dice_x][dice_y] == 0) {
            world[dice_x][dice_y] = dice[3][1];
        } else {
            dice[3][1] = world[dice_x][dice_y];
            world[dice_x][dice_y] = 0;
            //cout << dice[3][1];
        }

        cout << dice[1][1] << "\n";

    }
    

    return 0;
}

#include <iostream>
#include <vector>
#include <deque>
using namespace std;

int n;
//0 : empty, 1 : snake, 2 : apple
vector<vector<int>> world;
deque<pair<int, int>> snake;

int snake_dx = 0, snake_dy = 1;

//time, dir
deque<pair<int, char>> snake_moving_queue;

void turn_left() {
    if (snake_dx == 0) {
        snake_dx = -snake_dy;
        snake_dy = 0;
    } else {
        snake_dy = snake_dx;
        snake_dx = 0;
    }
}

void turn_right() {
    turn_left();
    turn_left();
    turn_left();
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    world.resize(n, vector<int>(n, 0));
    world[0][0] = 1;
    snake.push_back({0, 0});
    int K, L;
    cin >> K;
    while (K--) {
        int x, y;
        cin >> x >> y;
        world[--x][--y] = 2;
    }
    cin >> L;
    while (L--) {
        int t;
        char dir;
        cin >> t >> dir;
        snake_moving_queue.push_back({t, dir});
    }

    int time = 0;

    while (1) {
        time++;

        auto snake_new = snake.back();
        snake_new.first += snake_dx;
        snake_new.second += snake_dy;
        if (snake_new.first < 0 || n <= snake_new.first || snake_new.second < 0 || n <= snake_new.second) {
            cout << time;
            return 0;
        } 
        snake.push_back(snake_new);
        if (world[snake_new.first][snake_new.second] == 0) {
            world[snake.front().first][snake.front().second] = 0;
            snake.pop_front();
        } else if (world[snake_new.first][snake_new.second] == 1) {
            cout << time;
            return 0;
        }
        world[snake_new.first][snake_new.second] = 1;

        if (!snake_moving_queue.empty() && snake_moving_queue.front().first == time) {
            char dir = snake_moving_queue.front().second;
            snake_moving_queue.pop_front();
            if (dir == 'L') {
                turn_left();
            } else {
                turn_right();
            }
        }
    }










    return 0;
}



















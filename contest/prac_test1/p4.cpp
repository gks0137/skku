#include <iostream>
#include <deque>

int main(){
    int n;
    std::cin >> n;
    std::deque<int> submit;
    for(int i=0; i<n; i++) {
        int _;
        std::cin >> _;
        submit.push_front(_);
    }

    std::deque<std::pair<int, std::pair<int, int>>> queue;
    queue.push_back({submit.front(), {1, 0}});
    submit.pop_front();

    for (int i=0; i<n-1; i++) {
        int len = queue.size();
        for (int j=0; j<len; j++) {
            int v_sum = queue.front().first, v_t = queue.front().second.first, v_s = queue.front().second.second;
            queue.pop_front();

            if (v_t != 2) {
                queue.push_back({v_sum+submit.front(), {v_t+1, v_s}});
            } 
            if (v_s > (n-2)/2) continue;
            queue.push_back({v_sum, {0, v_s+1}});
            
        }
        submit.pop_front();
    }

    int max=0;
    for (std::pair<int, std::pair<int, int>> v : queue) {
        if (v.first > max) max = v.first;
    }
    std::cout << max;





    return 0;
}
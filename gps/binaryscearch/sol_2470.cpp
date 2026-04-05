#include <iostream>
#include <deque>
#include <algorithm>


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int n;
    std::cin >> n;

    std::deque<int> sol(n);
    for (int i=0; i<n; i++) std::cin >> sol[i];

    std::sort(sol.begin(), sol.end());

    //다 음수
    if (sol.back() < 0) {
        std::cout << sol[n-2] << ' ' << sol[n-1];
        return 0;
    }
    //다 양수
    if (sol.front() > 0) {
        std::cout << sol[0] << ' ' << sol[1];
        return 0;
    }

    

    std::deque<std::pair<int, std::pair<int, int>>> added;

    for (int idx=0; idx<n; idx++){
        int solution = sol[idx];

        int low=0, high=n-1, search;

        while (low <= high)
        {
            search = (low + high) / 2;
            
            
            if (sol[search] < -solution) {
                low = search+1;
            } else if (sol[search] > -solution) {
                high = search-1;
            } else {
                std::cout << -std::abs(solution) << ' ' << std::abs(solution);
                return 0;
            }
            
        }

        for (int i : {-2, -1, 0, 1, 2}) {
            if (search+i >= 0 && search+i < n &&  search+i != idx) {
                added.push_back({solution+sol[search+i], {solution, sol[search+i]}});
            }
        }
       
    }

    
    std::sort(added.begin(), added.end(), [](const auto& a, const auto& b){return std::abs(a.first) < std::abs(b.first);});
    
    int a, b;
    a = added.front().second.first;
    b = added.front().second.second;
    std::cout << std::min(a, b) << ' ' << std::max(a, b);
    

    return 0;
}
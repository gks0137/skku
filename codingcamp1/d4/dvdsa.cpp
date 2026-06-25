#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {

        for (int i = 2; i < cost.size(); i++) {
            cost[i] += min(cost[i - 1], cost[i - 2]);
        }
        return min(cost[cost.size() - 1], cost[cost.size() - 2]);
    }
};
int speedUp = [] {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    return 0;
}();

int digit(char c) { return c & 15; }

bool isDigit(char c) { return '0' <= c && c <= '9'; }

int in = [] {
    std::ofstream out("user.out");
    std::cout.rdbuf(out.rdbuf());

    int ans, prev1_ans, prev2_ans;
    for (std::string s; std::getline(std::cin, s); std::cout << '\n') {
        ans = 0; prev1_ans = 0; prev2_ans = 0;

        for (int _i = 1, _n = s.length(), v; _i < _n; ++_i) {
            prev2_ans = prev1_ans; prev1_ans = ans;
            
            v = digit(s[_i]);

            while (isDigit(s[++_i]))
                v = v * 10 + digit(s[_i]);

            ans = v + std::min(prev1_ans, prev2_ans);
        }

        std::cout << min(ans, prev1_ans);
    }

    exit(0);
    return 0;
}();



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    

    return 0;
}
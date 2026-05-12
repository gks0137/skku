#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int romanToInt(string s) {
        unordered_map<char, int> roman_values = {
            {'I', 1},
            {'V', 5},
            {'X', 10},
            {'L', 50},
            {'C', 100},
            {'D', 500},
            {'M', 1000}
        };
        int total = 0;
        for (size_t i = 0; i < s.size(); ++i) {
            int value = roman_values[s[i]];
            if (i + 1 < s.size() && value < roman_values[s[i + 1]]) {
                total -= value;
            } else {
                total += value;
            }
        }
        return total;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;


    string s = "MCMXC";
    cout << sol.romanToInt(s) << "\n";



    return 0;
}
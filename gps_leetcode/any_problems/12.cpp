#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string intToRoman(int num) {
        string roman = "";
        vector<pair<int, string>> values = {
            {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},
            {100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"},
            {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}
        };
        for (const auto& pair : values) {
            while (num >= pair.first) {
                roman += pair.second;
                num -= pair.first;
            }
        }
        return roman;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;


    int s = 1994;
    cout << sol.intToRoman(s) << "\n";



    return 0;
}
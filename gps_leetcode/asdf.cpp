#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    string multiply(string num1, string num2) {
        string result(num1.size() + num2.size(), '0');
        for (int i = num1.size() - 1; i >= 0; --i) {
            for (int j = num2.size() - 1; j >= 0; --j) {
                int mul = (num1[i] - '0') * (num2[j] - '0');
                int sum = mul + (result[i + j + 1] - '0');
                result[i + j + 1] = (sum % 10) + '0';
                result[i + j] += sum / 10;
            }
        }
        // Remove leading zeros
        int start = 0;
        while (start < result.size() && result[start] == '0') {
            ++start;
        }
        if (start == result.size()) {
            return "0";
        }
        return result.substr(start);
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;

    string num1 = "498828660196", num2 = "840477629533";
    cout << sol.multiply(num1, num2) << endl;
    
    return 0;
}
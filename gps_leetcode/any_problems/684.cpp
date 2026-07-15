#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        sort(people.begin(), people.end());
        int left = 0, right = people.size() - 1;
        int boats = 0;
        while (left <= right) {
            if (people[left] + people[right] <= limit) {
                ++left;
            }
            --right;
            ++boats;
        }
        return boats;
    }
};



int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;





    return 0;
}
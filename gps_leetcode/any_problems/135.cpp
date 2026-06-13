#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    int candy(vector<int>& ratings) {
        vector<int> candies(ratings.size(), 1);

        for (int i = 1; i < ratings.size(); i++) {
            if (ratings[i] > ratings[i - 1]) {
                candies[i] = candies[i - 1] + 1;
            }
        }
        for (int i = ratings.size() - 2; i >= 0; i--) {
            if (ratings[i] > ratings[i + 1]) {
                candies[i] = max(candies[i], candies[i + 1] + 1);
            }
        }
        return accumulate(candies.begin(), candies.end(), 0);
    }
};



int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;

    
    vector<int> ratings = {1, 0, 2};
    cout << sol.candy(ratings) << endl;



    return 0;
}
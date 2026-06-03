
#include <iostream>
#include <bits/stdc++.h>
using namespace std;



class Solution {
public:
    int maxSatisfaction(vector<int>& satisfaction) {
        vector<int> positives;
        vector<int> negatives;
        int zeros = 0;
        for (int x : satisfaction) {
            if (x > 0) {
                positives.push_back(x);
            } else if (x < 0) {
                negatives.push_back(x);
            } else {
                zeros++;
            }
        }
        sort(positives.begin(), positives.end());
        sort(negatives.begin(), negatives.end(), [](int a, int b){return a > b;});
        
        int ans = 0, arr_sum = 0;
        for (int i = 0; i < positives.size(); i++) {
            ans += (i + 1) * positives[i];
            arr_sum += positives[i];
        }
        ans += zeros*arr_sum;
        for (int i = 0; i < negatives.size(); i++) {
            arr_sum += negatives[i];
            if (arr_sum > 0) {
                ans += arr_sum;
            } else {
                break;
            }
        }
        return ans;
        
    }
};




int main()
{
    Solution sol;
    
    vector<int> satisfaction = {-1,-8,0,5,-9};
    cout << sol.maxSatisfaction(satisfaction) << endl;

    return 0;
}
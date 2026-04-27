#include <iostream>
#include <vector>
using namespace std;

vector<int> twoSum(vector<int>& nums, int target) {
        int a_idx = 0, b_idx = 0;
        for (int i = 0; i < nums.size(); i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                if (nums[i] + nums[j] == target) {
                    a_idx = i;
                    b_idx = j;
                    break;
                }
            }
        }
        return {a_idx, b_idx};
    }


int main() {
    
    vector<int> nums = {2, 7, 11, 15};
    int target = 9;

    
    cout << "Two Sum Indices: " << twoSum(nums, target)[0] << ", " << twoSum(nums, target)[1] << endl;

        
    
}
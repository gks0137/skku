#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> nums;
int nums_size;

void backtracking(int n, int m, vector<int>& selected) {
    if (selected.size() == m) {
        for (int i = 0; i < selected.size(); i++) {
            cout << nums[selected[i]] << (i == selected.size() - 1 ? "" : " ");
        }
        cout << "\n";
        return;
    }

    int last_picked = -1; // 현재 깊이에서 마지막으로 고른 숫자를 기억
    for (int i = 0; i < nums_size; i++) {
        
        bool flag = false;
        for (int selectedNum : selected) {
            if (selectedNum > i) {
                flag = true;
                break;
            }
        }
    
        if (flag || last_picked == nums[i]) {
            continue;
        }

        last_picked = nums[i];
        selected.push_back(i);
        backtracking(n, m, selected);
        selected.pop_back();
    }
}


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);


    int n, m;
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int num;
        std::cin >> num;
        nums.push_back(num);
    }
    nums_size = nums.size();
    sort(nums.begin(), nums.end());


    // for (int num : nums) {
    //     cout << num << " ";
    // } cout << "\n";
    


    vector<int> selected;
    
    backtracking(n, m, selected);

    return 0;
}

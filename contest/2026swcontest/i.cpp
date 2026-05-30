#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q, d;
    cin >> n >> q >> d;
    vector<int> nums(n+1);
    for (int i = 1; i <= n; i++) {
        cin >> nums[i];
    }

    while (q--) {
        int l, r, k;
        cin >> l >> r >> k;
        int ans = 0;
        for (int i = l; i < r-2 || k > 0;) {
            if (nums[i+2] - nums[i] == 2*d) {
                ans += 2;
                i += 2;
                if (nums[i+1] - nums[i] != d) k--;
            } else if (nums[i+1] = nums[i] == d) {
                ans++;
                i++;
            }
        }

        cout << min(r-l, ans+k);
    }


    return 0;
}
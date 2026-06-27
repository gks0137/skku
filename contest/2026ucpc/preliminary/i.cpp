#include <bits/stdc++.h>
using namespace std;

int main () {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> nums(n+1);
        vector<int> numss(n+1);
        
        for (int i = 1; i <= n; i++) {
            cin >> nums[i];
        }

        if (n == 1) goto YES;

        if (n%2 == 1) {
            numss=nums;

            for (int i = 1; i <= n; i++) {
                nums[i] = 10000001 - nums[i];
            }
            for (int i = 1; i < n; i++) {
                nums[i + 1] -= nums[i];

            }

            int k = 10000001 - nums[n];

            if (*max_element(numss.begin(),numss.end())>k) goto NO;

            for (int i = 1; i <= n; i++) {
                numss[i] = k - numss[i];
            }
            for (int i = 1; i < n; i++) {
                numss[i + 1] -= numss[i];
                if (numss[i+1]<0) goto NO;
            }
            if (numss[n]==0) goto YES;
            goto NO;
        }

        {
            for (int i = 1; i <= n; i++) {
                nums[i] = 10000001 - nums[i];
            }
            for (int i = 1; i < n; i++) {
                nums[i + 1] -= nums[i];
            }
            if (nums[n] == 0) {
                goto YES;
            } else {
                goto NO;
            }
        }


        YES:
        cout << "Yes\n";
        continue;

        NO:
        cout << "NO\n";
        continue;
    }



    return 0;
}
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    if (t == 1) {
        int a, b;
        cin >> a >> b;
        a += b;

        string s;
        while (a) {
            s.push_back(a%26 + 'a');
            a /= 26;
        }
        while (s.size() < 13) {
            s.push_back('a');
        }
        reverse(s.begin(), s.end());

        cout << s;
    } else {
        string s;
        cin >> s;

        int ans = 0;
        for (char c : s) {
            int x = c - 'a';
            ans *= 26;
            ans += x;
        }

        cout << ans;
    }


    return 0;
}
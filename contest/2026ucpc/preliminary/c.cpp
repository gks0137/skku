#include <bits/stdc++.h>
using namespace std;

int main () {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    int n;
    string a;
    cin >> s >> n >> a;

    for (char& c : a) {
        if (c == 'R') {
            c = 'B';
        } else {
            c = 'R';
        }
    }
    cout << a;


    return 0;
}
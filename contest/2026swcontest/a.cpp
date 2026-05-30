#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    if (n%2==0) {
        cout << 0;
    } else if (n == 1) {
        cout << 1;
    } else {
        cout << 2;
    }


    return 0;
}
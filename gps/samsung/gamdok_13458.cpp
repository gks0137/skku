#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, b, c;
    std::cin >> n;
    vector<int> a(n);
    while(n) {
        cin >> a[--n];
    }
    cin >> b >> c;
    long long count = 0;
    for (int& num : a) {
        num -= b;
        count++;
        if (num>0) {
            count += (num + c - 1) / c;
        }
    }
    cout << count;
}
#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int a;
    int sum;
    int coins[10];
    int result = 0;

    cin >> a;
    cin >> sum;
    for (int i = 0; i<a; i++) {
        cin >> coins[i];
        
    }
    for (int i = a-1; i>-1; i--) {
        result += sum/coins[i];
        sum = sum%coins[i];
    }
    cout << result;


    return 0;
}
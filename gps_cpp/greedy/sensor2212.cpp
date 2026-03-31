#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, k;
    cin >> n >> k;

    vector<int> sensors;
    vector<int> diff;

    for (int i = 0; i<n; i++) {
        int s;
        cin >> s;
        sensors.push_back(s);
    }

    sort(sensors.begin(), sensors.end());

    int prev = sensors.back();
    int cur;
    sensors.pop_back();

    while (!sensors.empty())
    {
        cur = sensors.back();

        diff.push_back(prev - cur);

        prev = cur;
        sensors.pop_back();

    }

    sort(diff.begin(), diff.end());



    long long int result = 0;
    for(int i=0; i<n-k; i++){
        result += diff[i];
    }

    

    cout << result;


    return 0;
}
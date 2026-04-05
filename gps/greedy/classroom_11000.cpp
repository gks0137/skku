#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int N;
    cin >> N;

    vector<pair<int, int>> time;
    for(int i=0; i<N; i++)
    {
        int start, end;
        cin >> start >> end;
        time.push_back({start, 1});
        time.push_back({end, -1});
    }
    sort(time.begin(), time.end(), 
    [](pair<int, int>&a, pair<int, int> &b){if(a.first == b.first) return a.second < b.second; return a.first < b.first;});

    int occupant = 0, max_occupant = 0;

    for(const auto& cur : time)
    {
        occupant += cur.second;
        max_occupant = max(max_occupant, occupant);
    }

    cout << max_occupant;
    return 0;
}
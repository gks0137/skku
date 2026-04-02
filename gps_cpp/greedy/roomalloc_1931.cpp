#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    
    int N;
    cin >> N;

    vector<pair<int, int>> time;
    
    for(int i=0; i<N; i++)
    {
        int start, end;
        cin >> start >> end;

        time.push_back({start, end});
    }

    sort(time.begin(), time.end(), [](pair<int, int> a, pair<int, int> b) {
        if(a.second == b.second)
            return a.first < b.first;
        return a.second < b.second;
    });

    int max_occupied = 0, end_time = 0;
    for(int i=0; i<N; i++)
    {
        if(end_time <= time[i].first)
        {
            end_time = time[i].second;
            max_occupied++;
        }
    }
    

    cout << max_occupied << "\n";

    





    return 0;
}
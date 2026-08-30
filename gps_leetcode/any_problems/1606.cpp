#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        vector<int> request_count(k, 0);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> time_to_servers;
        set<int> avaliable_servers;

        for (int i = 0; i < k; i++) {
            avaliable_servers.insert(i);
        }
        
        
        for (int i = 0; i < arrival.size(); i++) {
            while (!time_to_servers.empty() && time_to_servers.top().first <= arrival[i]) {
                avaliable_servers.insert(time_to_servers.top().second);
                time_to_servers.pop();
            }
            
            if (avaliable_servers.empty()) {
                continue;
            }
            int server_id = i % k;
            auto it = avaliable_servers.lower_bound(server_id);
            if (it == avaliable_servers.end()) {
                it = avaliable_servers.begin();
            }
            server_id = *it;
            request_count[server_id]++;
            avaliable_servers.erase(it);
            time_to_servers.push({arrival[i] + load[i], server_id});

            
        }

        priority_queue<pair<int, int>> pq;
        for (int i = 0; i < k; i++) {
            pq.push({request_count[i], i});
        }
        vector<int> result;
        int max_requests = pq.top().first;
        while (!pq.empty() && pq.top().first == max_requests) {
            result.push_back(pq.top().second);
            pq.pop();
        }
        return result;
    }
};



int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;

    int k = 3;
    vector<int> arrival = {1, 2, 3, 4, 5};
    vector<int> load = {5, 2, 3, 3, 3};

    vector<int> result = sol.busiestServers(k, arrival, load);
    for (int server_id : result) {
        cout << server_id << " ";
    }
    cout << endl;

    return 0;
}
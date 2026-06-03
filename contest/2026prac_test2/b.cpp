#include <bits/stdc++.h>
using namespace std;


int main () {

    int num = 0, q, hsize = 0, lsize = 0;
    cin >> q;
    priority_queue<int, vector<int>, greater<int>> highers;
    unordered_map<int, bool> highers_removed;
    priority_queue<int> lowers;
    unordered_map<int, bool> lowers_removed;
    
    while (q--) {
        int query, tmp, move;
        cin >> query;

        switch (query)
        {
        case 1:
            cin >> tmp;
            num++;
            if (hsize >= lsize) {
                lsize++;
                while (!highers.empty()) {
                    move = highers.top();
                    if (highers_removed.find(move) != highers_removed.end()) {
                        highers.pop();
                        highers_removed.erase(move);
                        continue;
                    }
                    break;
                }
                if (!highers.empty() && move < tmp) {
                    lowers.push(move);
                    highers.pop();
                    highers.push(tmp);
                } else {
                    lowers.push(tmp);
                }

            } else {
                hsize++;
                while (!lowers.empty()) {
                    move = lowers.top();
                    if (lowers_removed.find(move) != lowers_removed.end()) {
                        lowers.pop();
                        lowers_removed.erase(move);
                        continue;
                    }
                    break;
                }
                if (!lowers.empty() && move > tmp) {
                    highers.push(move);
                    lowers.pop();
                    lowers.push(tmp);
                } else {
                    highers.push(tmp);
                }

            }
            break;
        case 2:
            cin >> tmp;
            num--;
            if (hsize >= lsize) {
                hsize--;
                while (!highers.empty()) {
                    move = highers.top();
                    if (highers_removed.find(move) != highers_removed.end()) {
                        highers.pop();
                        highers_removed.erase(move);
                        continue;
                    }
                    break;
                }
                if (move <= tmp) {
                    highers_removed[tmp] = true;
                } else {
                    highers.pop();
                    lowers.push(move);
                    lowers_removed[tmp] = true;
                }
                



            } else {
                lsize--;
                while (!lowers.empty()) {
                    move = lowers.top();
                    if (lowers_removed.find(move) != lowers_removed.end()) {
                        lowers.pop();
                        lowers_removed.erase(move);
                        continue;
                    }
                    break;
                }
                if (move >= tmp) {
                    lowers_removed[tmp] = true;
                } else {
                    lowers.pop();
                    highers.push(move);
                    highers_removed[tmp] = true;
                }
            }
            break;

        case 3:
            while(1) {
                move = lowers.top();
                if (lowers_removed.find(move) != lowers_removed.end()) {
                    lowers.pop();
                    lowers_removed.erase(move);
                    continue;
                }
                break;
            }

            cout << move << "\n";
            break;
        
        }

    }





    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>

long long int get_lan(const int length, std::vector<long long int>& wires) {
    long long int val=0;
    for(const auto& wire : wires) {
        val += wire / length;
    }
    return val;
}



int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int k, n;
    std::cin >> k >> n;

    std::vector<long long int> wires(k);

    
    for(int _=0; _<k; _++) {
        std::cin >> wires[_];
    }
    long long int lan = 0x100000000 / 2;
    long long int scearch = lan/2;
    long long int count=0, max_lan=0;

    while (1)
    {
        count = get_lan(lan, wires);
        if (n <= count) {
            if (max_lan < lan) max_lan = lan;

            lan += scearch;
            scearch /= 2;

        } else {
            lan -= scearch;
            scearch /= 2;
            
        }
        if (scearch==0) {
            count = get_lan(lan, wires);
            if (n <= count && max_lan < lan) max_lan = lan;
            break;
        }
    }
    
    

    std::cout << max_lan;

    return 0;
}
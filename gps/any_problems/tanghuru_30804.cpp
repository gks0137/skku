#include <iostream>
#include <vector>
#include <deque>
using namespace std;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);


    int n;
    std::cin >> n;
    
    
    int last_fruit = -1, last_last_fruit = -1;
    int last_length = 0, current_length = 0;

    

    int max_length = 0;

    

    for (int i = 0; i < n; i++) {
        int fruit;
        std::cin >> fruit;

        if (fruit == last_fruit) {
            last_length++;
            current_length++;
        } else if (fruit == last_last_fruit) {
            current_length++;
            last_length = 1;
            last_last_fruit = last_fruit;
            last_fruit = fruit;
        } else {
            current_length = last_length + 1;
            last_length = 1;
            last_last_fruit = last_fruit;
            last_fruit = fruit;
        }
        
        max_length = max(max_length, current_length);
    }

    cout << max_length << "\n";

    return 0;
}


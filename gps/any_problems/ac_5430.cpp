#include <iostream>
#include <deque>
using namespace std;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);


    int t;
    std::cin >> t;
    while (t--) {
        string p, arr_str;
        int n;
        std::cin >> p >> n >> arr_str;

        deque<int> arr;
        string num_str = "";
        for (char c : arr_str) {
            if (isdigit(c)) {
                num_str += c;
            } else if (!num_str.empty()) {
                arr.push_back(stoi(num_str));
                num_str = "";
            }
        }
        if (!num_str.empty()) {
            arr.push_back(stoi(num_str));
        }

        bool is_reversed = false;
        bool is_error = false;

        for (char cmd : p) {
            if (cmd == 'R') {
                is_reversed = !is_reversed;
            } else if (cmd == 'D') {
                if (arr.empty()) {
                    is_error = true;
                    break;
                }
                if (is_reversed) {
                    arr.pop_back();
                } else {
                    arr.pop_front();
                }
            }
        }

        if (is_error) {
            std::cout << "error\n";
        } else {
            std::cout << "[";
            if (is_reversed) {
                for (auto it = arr.rbegin(); it != arr.rend(); ++it) {
                    std::cout << *it;
                    if (it + 1 != arr.rend()) std::cout << ",";
                }
            } else {
                for (size_t i = 0; i < arr.size(); ++i) {
                    std::cout << arr[i];
                    if (i + 1 != arr.size()) std::cout << ",";
                }
            }
            std::cout << "]\n";
        }
    }

    

    return 0;
}

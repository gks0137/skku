#include <iostream>
#include <vector>

int N;

void print_line(std::vector<int> divisors) {

    bool is_space = false;

    for (int i = 0; i < N; i++) {
        for (int& divisor : divisors) {
            if (i / divisor % 3 == 1) {
                std::cout << " ";
                is_space = true;
                break;;
            }
            
        }
        if (!is_space) {
            std::cout << "*";
        }
        is_space = false;
    }
    std::cout << "\n";
}

void print_pattern(int size, std::vector<int> divisors) {
    if (size == 1) {
        print_line(divisors);
        return;
    }

    std::vector<int> new_divisors = divisors;
    new_divisors.push_back(size/3);
    print_pattern(size/3, divisors);
    print_pattern(size/3, new_divisors);
    print_pattern(size/3, divisors);
}


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N;

    print_pattern(N, {});
    




    return 0;
}
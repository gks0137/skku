#include <iostream>

int main() {

    int money[] = {500, 100, 50, 10, 5, 1};
    int n, count = 0;
    std::cin >> n;
    n = 1000 - n;

    for (int i = 0; i < 6; i++) {
        count += n / money[i];
        n %= money[i];
    }
    std::cout << count << std::endl;



    return 0;
}
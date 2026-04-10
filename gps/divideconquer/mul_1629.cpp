#include <iostream>
#include <vector>
using namespace std;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);


    int a, b, c;
    std::cin >> a >> b >> c;
    vector<int> n_pow2_pow_mod_c = {a%c};
    for (int i = 1; i <= 30; i++) {
        n_pow2_pow_mod_c.push_back((int)(((long long)n_pow2_pow_mod_c[i-1] * n_pow2_pow_mod_c[i-1]) % c));
    }
    int result = 1;
    for (int i = 0; i < 31; i++) {
        if (b & 1) {
            result = (int)((long long)result * n_pow2_pow_mod_c[i] % c);
        }
        b >>= 1;
    }
    std::cout << result;
    


    

    return 0;
}

#include <bits/stdc++.h>
using namespace std;

int solutions_count = 0;
unsigned short n = (1 << 15) - 1;

void backtrack(unsigned short row, short cols, short diag1, short diag2) {
    row--; //move to the next row
    
    short available = n & ~(cols | diag1 | diag2);
    
    while (available) {
        if (!row) { 
            solutions_count++;
            return;
        }
        short pos = available & -available; //rightmost set bit
        backtrack(row, cols | pos, (diag1 | pos) >> 1, (diag2 | pos) << 1);
        available ^= pos; //remove the rightmost set bit
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);


    backtrack(15, 0, 0, 0);

    cout << "Number of solutions for " << n << "-Queens: " << solutions_count << "\n";
    return 0;
}
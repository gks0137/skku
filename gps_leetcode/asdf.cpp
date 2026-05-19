#include <bits/stdc++.h>
using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);


    int a[] = {1, 2}, b = 5;
    int *p1 = a;
    int (*arrptr)[3] = (int (*)[3])&a;
    int *arrofptr[3] = {&a[0], &a[1], &b};
    int *(*arrofptrptr)[3] = &arrofptr;
    int (**arrptrptr)[3] = (int (**)[3])&arrptr;

    for (int i = 0; i < 3; i++) {
        cout << *(*arrofptrptr)[i] << " ";
    } cout << endl;
    for (int i = 0; i < 3; i++) {
        cout << (**arrptrptr)[i] << " ";
    }





    return 0;
}
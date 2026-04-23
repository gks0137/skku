#include <stdio.h>

#define add(x, y) x+y

int main() {

    short int a = -1;
    unsigned int b = a;

    printf("a: %d, b: %u\n", a, b);

    return 0;
}
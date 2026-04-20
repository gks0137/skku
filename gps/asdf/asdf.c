#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int main() {

    srand(time(NULL));
    int a = rand() % 100;
    printf("Random number: %d\n", a);

    return 0;
}
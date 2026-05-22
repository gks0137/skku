#include <stdio.h>
#include <stdlib.h>

struct Temp {
    int a;
    float b;
};

struct Temp createTemp(int a, float b) {
    struct Temp temp;
    temp.a = a;
    temp.b = b;
    return temp;
}


int main() {
    
    struct Temp a = createTemp(5, 3.14);
    


    
    return 0;
}

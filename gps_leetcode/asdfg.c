#include <stdio.h>


int main() {
    
    struct code {
        char *country;
        int code;
    };

    struct code code1 = {"USA", 1};

    printf("%d %d %d\n", sizeof(code1), sizeof(code1.country), sizeof(code1.code));
    
    union data {
        int i;
        double f;
    };

    union data d;
    d.i = 10;
    printf("%d %d\n", sizeof(d), sizeof(d.i));
    d.f = 3.14;
    printf("%d %d\n", sizeof(d), sizeof(d.f));

    
    typedef enum {
        MONDAY = -5,
        TUESDAY,
        WEDNESDAY,
        THURSDAY = -4,
        FRIDAY,
        SATURDAY,
        SUNDAY
    } Day;
    Day today = WEDNESDAY;
    printf("%d\n", today);

    


    return 0;
}

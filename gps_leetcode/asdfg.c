#include <stdio.h>
#include <string.h> 


int main() {
    
    char str[4] = "abc";
    if (str[3] == '\0') {
        puts("The string is null-terminated.");
    } else {
        puts("The string is not null-terminated.");
    }
    puts(str);
    
    return 0;
}

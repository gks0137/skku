#include <stdio.h>

int counter(int num) {
    static int count = 0; // Static variable to retain its value across function calls
    count += num; // Increment the count by the input number
    return count; // Return the current count
}

int main() {

    int a = counter(5); // First call, count becomes 5
    int b = counter(10); // Second call, count becomes 15
    int c = counter(15); // Third call, count becomes 30

    printf("%d %d %d\n", a, b, c); // Output the results
    


    return 0;
}
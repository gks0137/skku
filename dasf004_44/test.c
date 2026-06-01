#include <stdio.h>
// #include <stdlib.h>





int main() {

    FILE* file = fopen("test.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        // exit(EXIT_FAILURE);
         return 1;
    }

    fprintf(file, "Hello, World!\n");
    fwrite("Hello, World!\n", sizeof(char), 14, file);
    fputc('\n', file);





    fclose(file);
    return 0;
}
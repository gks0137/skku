#include <stdio.h>

// examples of fprintf, fscanf, fputc, fgetc, fwrite, fread,

int main() {
    
    FILE *file = fopen("example.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    // examples of fprintf, fputc, fwrite
    fprintf(file, "1Hello, World!\n2Hello, World!\n3Hello, World%.1f!\n4Hello, World!\n", 42.0);
    fputc('A', file);
    putc('B', file);
    fwrite("CDEFGHIJKL", sizeof(char), 10, file);
    fclose(file);
    
    
    FILE *file_read = fopen("example.txt", "r");
    if (file_read == NULL) {
        perror("Error opening file for reading");
        return 1;
    }
    // examples of fscanf, fgetc, fread with ferror and feof
    char buffer[5];
    while (fscanf(file_read, "%c%c%c%c", &buffer[0], &buffer[1], &buffer[2], &buffer[3]) == 4) {
        buffer[4] = '\0'; // Null-terminate the string
        printf("Read string: %s\n", buffer);
    }
    printf("what happened to buffer: %s\n", buffer);
    if (ferror(file_read)) {
        perror("Error reading from file");
    } else if (feof(file_read)) {
        printf("End of file reached\n");
    }


    enum {
        MONDAY = 1,
        TUESDAY,
        WEDNESDAY = -1,
        THURSDAY,
        FRIDAY,
    } day;

    day = MONDAY;
    


    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void process_file(const char *src_filename, const char *dst_filename) {
    FILE *src_file = fopen(src_filename, "r");
    if (src_file == NULL) {
        perror("Error opening source file");
        return;
    }

    FILE *dst_file = fopen(dst_filename, "w");
    if (dst_file == NULL) {
        perror("Error opening destination file");
        fclose(src_file);
        return;
    }

    char buffer[1000];
    int invalid_count = 0;
    float value;

    while (fscanf(src_file, "%255s", buffer) == 1) {
        if (sscanf(buffer, "%f", &value) == 1) {
            fprintf(dst_file, "%.2f\n", value);
        } else {
            invalid_count++;
        }
    }

    if (ferror(src_file)) {
        perror("Error reading from source file");
    }

    fclose(src_file);
    fclose(dst_file);

    printf("Number of invalid float values: %d\n", invalid_count);
}

int main() {
    const char *src_filename = "C:\\Users\\Salman\\Desktop\\data.txt"; // Source file with float values
    const char *dst_filename = "C:\\Users\\Salman\\Desktop\\correct_floats.txt"; // Destination file for valid floats

    process_file(src_filename, dst_filename);
    
    return 0;
}

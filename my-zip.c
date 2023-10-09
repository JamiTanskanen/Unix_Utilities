// Jami Tanskanen 612705
#include <stdio.h>
#include <stdlib.h>

// Compress a file using run-length encoding.
void zip_file(FILE *fp) {
    int count = 1;
    char curr, prev;
    
    // Read the first character from the file.
    if ((prev = fgetc(fp)) == EOF) {
        return;
    }

    while (1) {
        curr = fgetc(fp);
        // If current character matches previous, increment count.
        if (curr == prev && curr != EOF) {
            count++;
        } else {
            // Write the count and character to stdout.
            fwrite(&count, sizeof(int), 1, stdout);
            fputc(prev, stdout);

            // Exit loop if end of file.
            if (curr == EOF) {
                break;
            }
            count = 1;
            prev = curr;
        }
    }
}

int main(int argc, char *argv[]) {
    // Ensure a file is provided as input.
    if (argc < 2) {
        printf("my-zip: file1 [file2 ...]\n");
        exit(1);
    }
    // Process each provided file.
    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL) {
            printf("my-zip: cannot open file\n");
            exit(1);
        }
        zip_file(fp);
        fclose(fp);
    }
    
    return 0;
}

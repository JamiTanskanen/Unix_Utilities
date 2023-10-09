// Jami Tanskanen 612705
#include <stdio.h>
#include <stdlib.h>

// Decompress a file using run-length encoding.
void unzip_file(FILE *fp) {
    int count;
    char ch;
    
    // Read in blocks of data, and output decompressed content.
    while (fread(&count, sizeof(int), 1, fp)) {
        ch = fgetc(fp);
        for (int i = 0; i < count; i++) {
            fputc(ch, stdout);
        }
    }
}

int main(int argc, char *argv[]) {
    // Ensure a file is provided as input.
    if (argc < 2) {
        printf("my-unzip: file1 [file2 ...]\n");
        exit(1);
    }
    // Process each provided file.
    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL) {
            printf("my-unzip: cannot open file\n");
            exit(1);
        }
        unzip_file(fp);
        fclose(fp);
    }

    return 0;
}

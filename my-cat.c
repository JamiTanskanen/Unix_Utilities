// Jami Tanskanen 612705
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // Check if no file arguments are provided and exit immediately.
    if (argc == 1) {
        return 0;
    }

    // Loop through each provided file name.
    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        
        // If fopen() fails, print an error message and exit with status 1.
        if (fp == NULL) {
            printf("my-cat: cannot open file\n");
            exit(1);
        }

        char buffer[1024]; // Buffer to temporarily hold data from the file for processing.

        // Read each line and print its contents.
        while (fgets(buffer, sizeof(buffer), fp) != NULL) {
            printf("%s", buffer);
        }

        // Close the file after reading.
        fclose(fp);
    }

    return 0;
}

// Jami Tanskanen 612705
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> //I had to get help from the following: https://pubs.opengroup.org/onlinepubs/009604499/basedefs/sys/types.h.html


int grep_file(FILE *fp, const char *search_term) {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, fp)) != -1) {
        // Check if the current line contains the search term.
        if (strstr(line, search_term) != NULL) {
            printf("%s", line);
        }
    }
    // Free the memory allocated for the line buffer.
    free(line);
    return 0;
}

int main(int argc, char *argv[]) {
    // Check if the search term is provided.
    if (argc < 2) {
        printf("my-grep: searchterm [file ...]\n");
        exit(1);
    }
    // Get the search term from the command line arguments.
    const char *search_term = argv[1];
    
    // If no file is provided, read input from stdin.
    if (argc == 2) {
        grep_file(stdin, search_term);
    } else {
        // Loop through each provided file name.
        for (int i = 2; i < argc; i++) {
            FILE *fp = fopen(argv[i], "r");
            if (fp == NULL) {
                printf("my-grep: cannot open file\n");
                exit(1);
            }

            grep_file(fp, search_term);
            fclose(fp);
        }
    }

    return 0;
}

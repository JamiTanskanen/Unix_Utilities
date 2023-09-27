// for that "POSIX_C_SOURCE..." I got help from the following: 
// https://stackoverflow.com/questions/59014090/warning-implicit-declaration-of-function-getline
// The reason for defining it here is to make the getline function available.
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE *input, *output;
    char **lines = NULL;
    char *line = NULL;
    size_t len = 0;
    int read;
    int count = 0;

    // If more than 3 arguments are given, print usage message and exit.
    if (argc > 3) {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }

    // Check if input and output file are the same, if so, print error and exit.
    if (argc == 3 && strcmp(argv[1], argv[2]) == 0) {
        fprintf(stderr, "Input and output file must differ\n");
        exit(1);
    }

    // If an input file is provided, open it for reading. Otherwise, read from stdin.
    if (argc >= 2) {
        input = fopen(argv[1], "r");
        if (input == NULL) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
            exit(1);
        }
    } else {
        input = stdin;
    }

    // If an output file is provided, open it for writing. Otherwise, write to stdout.
    if (argc == 3) {
        output = fopen(argv[2], "w");
        if (output == NULL) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[2]);
            exit(1);
        }
    } else {
        output = stdout;
    }

    // Read lines from the input source and store them in the lines dynamic array.
    while ((read = getline(&line, &len, input)) != -1) {
        // Resize the lines array to accommodate the new line.
        char **temp = realloc(lines, (count + 1) * sizeof(char *));
        if (temp == NULL) {
            fprintf(stderr, "malloc failed\n");
            exit(1);
        }
        lines = temp;

        // Allocate memory for the new line and store it in the array.
        lines[count] = malloc(read + 1);
        if (lines[count] == NULL) {
            fprintf(stderr, "malloc failed\n");
            exit(1);
        }
        strcpy(lines[count], line);
        count++;
    }

    // Write the lines to the output source in reverse order.
    for (int i = count - 1; i >= 0; i--) {
        fprintf(output, "%s", lines[i]);
        free(lines[i]);
    }

    // Cleanup: free dynamically allocated memory.
    free(line);
    free(lines);

    // Close the input and output files if they are not stdin and stdout respectively.
    if (input != stdin) {
        fclose(input);
    }
    if (output != stdout) {
        fclose(output);
    }

    return 0;
}

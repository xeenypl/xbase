#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SET_COLOR_RED "\x1b[91m"
#define RESET_COLOR   "\x1b[39m"

static void error(const char* msg);
static void using(void);
static void cat(FILE* file);

static void error(const char* msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

static void using(void) {
    fputs(
        "using:\n"
        "\tcat [-nsEeh] <string>...\n",
        stderr
    );
    exit(EXIT_FAILURE);
}

static void cat(FILE* file) {
    for (char c = getc(file); c != EOF; c = getc(file)) {
        putchar(c);
    }
}

int main(int argc, char** argv) {
    int opt;
    while ((opt = getopt(argc, argv, "")) != -1) {
        switch (opt) {
        default:
            using();
            break;
        }
    }
    argc -= optind;
    argv += optind;
    for (int i = 0; i < argc; i++) {
        FILE* file = fopen(argv[i], "r");
        if (file == NULL) {
            error(SET_COLOR_RED "File error" RESET_COLOR);
        }
        cat(file);
        fclose(file);
    }
    if (argc == 0) {
        cat(stdin);
    }
    return EXIT_SUCCESS;
}

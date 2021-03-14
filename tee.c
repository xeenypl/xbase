#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SET_COLOR_RED "\x1b[91m"
#define RESET_COLOR   "\x1b[39m"

static bool flag_a = false;

static void error(const char* msg);
static void using(void);
static void tee(int count, char** paths);

static void error(const char* msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

static void using(void) {
    fputs(
        "using:\n"
        "\ttee [-a] <string>...\n",
        stderr
    );
    exit(EXIT_FAILURE);
}

static void tee(int count, char** paths) {
    FILE* files[count];
    for (int i = 0; i < count; i++) {
        files[i] = fopen(paths[i], flag_a ? "w" : "a");
        if (files[i] == NULL) {
            error("File error");
        }
    }
    while (true) {
        char input = getchar();
        if (input == EOF) {
            break;
        }
        for (int i = 0; i < count; i++) {
            fputc(input, files[i]);
        }
        putchar(input);
    }
}

int main(int argc, char** argv) {
    int opt;
    while ((opt = getopt(argc, argv, "a")) != -1) {
        switch (opt) {
        case 'a':
            flag_a = true;
            break;
        default:
            using();
            break;
        }
    }
    argc -= optind;
    argv += optind;
    if (argc == 0) {
        using();
    }
    tee(argc, argv);
    return EXIT_SUCCESS;
}

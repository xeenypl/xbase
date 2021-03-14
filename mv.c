#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void using(void);

static void using(void) {
    fputs(
        "using:\n"
        "\tmv <src> <dst>\n",
        stderr
    );
    exit(EXIT_FAILURE);
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

    if (argc == 2) {
        rename(argv[0], argv[1]);
    } else {
        using();
    }
    return EXIT_SUCCESS;
}

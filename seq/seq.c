#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static char* flag_s = NULL;

static void using(void);
static void seq(double first, double increment, double last);

static void using(void) {
    fputs(
        "using:\n"
        "\tseq [-s] <last>\n"
        "\tseq [-s] <first> <last>\n"
        "\tseq [-s] <first> <increment> <last>\n",
        stderr
    );
    exit(EXIT_FAILURE);
}

static void seq(double first, double increment, double last) {
    while ((increment < 0) ? (first >= last) : (first <= last)) {
        printf("%g", first);
        first += increment;
        if ((increment < 0) ? (first >= last) : (first <= last)) {
            printf("%s", flag_s == NULL ? "\n" : flag_s);
        }
    }
}

int main(int argc, char** argv) {
    int opt;
    while ((opt = getopt(argc, argv, "s:")) != -1) {
        switch (opt) {
        case 's':
            flag_s = optarg;
            break;
        default:
            using();
            break;
        }
    }
    argc -= optind;
    argv += optind;

    double first = 1;
    double increment = 1;
    double last;

    if (argc == 1) {
        last = atof(argv[0]);
    } else if (argc == 2) {
        first = atof(argv[0]);
        last = atof(argv[1]);
    } else if (argc == 3) {
        first = atof(argv[0]);
        increment = atof(argv[1]);
        last = atof(argv[2]);
    } else {
        using();
    }

    seq(first, increment, last);

    putchar('\n');
    return EXIT_SUCCESS;
}

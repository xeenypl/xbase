#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

static bool flag_p = false;

static void using(void);

static void using(void) {
    fputs(
        "using:\n"
        "\tmkdir [-p] <string>...\n",
        stderr
    );
    exit(EXIT_FAILURE);
}

static void _mkdir(char* path) {
    if (flag_p) {
        char* end = strchr(path, '/');
        while (end != NULL) { 
            (*end) = 0;
            printf("%s\n", path);
            (*end) = '/';
            end = strchr(end, '/');
        }
    } else {
        mkdir(path, 0755);
    }
}

int main(int argc, char** argv) {
    int opt;
    while ((opt = getopt(argc, argv, "ph")) != -1) {
        switch (opt) {
        case 'p':
            flag_p = true;
            break;
        default:
            using();
            break;
        }
    }
    argc -= optind;
    argv += optind;
    for (int i = 0; i < argc; i++) {
        _mkdir(argv[i]);
    }
    return EXIT_SUCCESS;
}

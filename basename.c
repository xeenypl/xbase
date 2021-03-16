#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char* progname;

static void using(void) {
    fprintf(stderr, "using:\n\t%s [path] <sufix>\n", progname);
    exit(1);
}

static char* chop_sufix(char* str, const char* sufix) {
    size_t str_len = strlen(str);
    size_t sufix_len = strlen(sufix);
    if (strcmp(&str[str_len - sufix_len], sufix)  == 0)
        str[str_len - sufix_len] = 0;
    return str;
}

int main(int argc, char* argv[]) {
    progname = argv[0];
    if (argc == 2) {
        printf("%s\n", basename(argv[1]));
    } else if (argc == 3) {
        printf("%s\n", chop_sufix(basename(argv[1]), argv[2]));
    } else {
        using();
    }
    return 0;
}

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static bool flag_n = false;
static bool flag_s = false;
static bool flag_e = false;

static void using(void);
static char parse_hex_digit(char c);
static char parse_hex(const char* str);
static void print_escape(const char*);
static void print_no_escape(const char*);

static void using(void) {
    fputs(
        "using:\n"
        "\techo [-nsEeh] <string>...\n",
        stderr
    );
    exit(EXIT_FAILURE);
}

static char parse_hex_digit(char c) {
    if ('0' <= c && c <= '9') {
        return c - '0';
    } else if ('A' <= c && c <= 'F') {
        return c - 'A' + 10;
    } else if ('a' <= c && c <= 'f') {
        return c - 'a' + 10;
    }
    return 0;
}

static char parse_hex(const char* str) {
    char res = 0;
    res = res | parse_hex_digit(*str);
    res = res << 4;
    res = res | parse_hex_digit(*(str + 1));
    return res;
}

static void print_escape(const char* msg) {
    for (int i = 0; msg[i] != 0; i++) {
        if (msg[i] == '\\') {
            switch (msg[++i]) {
            case '\\':
                putchar('\\');
                break;
            case 'b':
                putchar('\b');
                break;
            case 'a':
                putchar('\a');
                break;
            case 'c':
                exit(EXIT_SUCCESS);
                break;
            case 'e':
                putchar(0x1b);
                break;
            case 'f':
                putchar('\f');
                break;
            case 'n':
                putchar('\n');
                break;
            case 'r':
                putchar('\r');
                break;
            case 't':
                putchar('\t');
                break;
            case 'v':
                putchar('\v');
                break;
            case 'x':
                putchar(parse_hex(msg + (++i)));
                i++;
                break;
            }
        } else {
            putchar(msg[i]);
        }
    }
}

static void print_no_escape(const char* msg) {
    for (int i = 0; msg[i] != 0; i++) {
        putchar(msg[i]);
    }
}

int main(int argc, char** argv) {
    int opt;
    while ((opt = getopt(argc, argv, "nsEeh")) != -1) {
        switch (opt) {
        case 'n':
            flag_n = true;
            break;
        case 's':
            flag_s = true;
            break;
        case 'E':
            flag_e = false;
            break;
        case 'e':
            flag_e = true;
            break;
        default:
            using();
            break;
        }
    }
    argc -= optind;
    argv += optind;
    for (int i = 0; i < argc; i++) {
        if (flag_e == false) {
            print_no_escape(argv[i]);
        } else {
            print_escape(argv[i]);
        }
        if (flag_s == false) {
            putchar(' ');
        }
    }
    if (flag_n == false) {
        putchar('\n');
    }
    return EXIT_SUCCESS;
}

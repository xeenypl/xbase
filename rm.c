#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <getopt.h>

static const char* progname = NULL;
static bool flag_i = false;
static bool flag_f = false;
static bool flag_r = false;
static bool flag_d = false;
static bool flag_v = false;
static struct option opts[] = {
   {"help",         no_argument, 0, 'h' },
   {"recursive",    no_argument, 0, 'r' },
   {"verbose",      no_argument, 0, 'v' },
   {"interactive",  no_argument, 0, 'i' },
   {"dir",          no_argument, 0, 'd' },
   {"force",        no_argument, 0, 'f' },
   {0,              0,           0, 0   }
};

static void using(void) {
    fprintf(stderr, "using:\n\t%s [-hifrRdv] <file...>\n", progname);
    exit(1);
}

static bool is_directory(const char* path) {
    struct stat st;
    if (stat(path, &st) < 0) {
        perror("stat");
        exit(1);
    }
    return st.st_mode & S_IFDIR;
}

static bool prmmpt(const char* path) {
    printf("do you want remove '%s': ", path);
    return getchar() == 'y';
}

static void rm(const char* path) {
    if (is_directory(path)) {
        if (!flag_i || flag_f || prmmpt(path)) {
            if (flag_r) {
                struct dirent *d;
                DIR *dir = opendir(path);
                if (dir == NULL) {
                    perror("opendir");
                    exit(1);
                }
                size_t path_len = strlen(path);
                while ((d = readdir(dir)) != NULL) {
                    if (strcmp(d -> d_name, ".")  == 0 ||
                        strcmp(d -> d_name, "..") == 0)
                        continue;
                    char path_next[path_len + strlen(d -> d_name) + 2];
                    // TODO strcat is slow.
                    strcpy(path_next, path);
                    strcat(path_next, "/");
                    strcat(path_next, d->d_name);
                    rm(path_next);
                }
                closedir(dir);
                if (remove(path) < 0) {
                    perror("remove");
                    exit(1);
                }
            } else if (flag_d) {
                if (remove(path) < 0) {
                    perror("remove");
                    exit(1);
                }
            }
        }
    } else {
        if (!flag_i || flag_f || prmmpt(path)) {
            if (remove(path) < 0) {
                perror("remove");
                exit(1);
            }
        }
    }
    if (flag_v) 
        printf("removed: %s\n", path);
}

int main(int argc, char* argv[]) {
    progname = argv[0];
    char ch;
    while ((ch = getopt_long(argc, argv, "hifrRdv", opts, NULL)) != -1) {
        switch(ch) {
        case 'i':
            flag_i = true;
            break;
        case 'f':
            flag_f = true;
            break;
        case 'r':
            flag_r = true;
            break;
        case 'd':
            flag_d = true;
            break;
        case 'v':
            flag_v = true;
            break;
        default:
            using();
        }
    }
    argc -= optind;
    argv += optind;

    if (argc == 0)
        using();

    for (int i = 0; i < argc; i++)
        rm(argv[i]);

    return 0;
}

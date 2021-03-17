#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <getopt.h>

static const char* progname = NULL;
static bool flag_f = false;
static bool flag_i = false;
static bool flag_r = false;
static bool flag_v = false;
static struct option opts[] = {
   {"help",         no_argument, 0, 'h' },
   {"recursive",    no_argument, 0, 'r' },
   {"verbose",      no_argument, 0, 'v' },
   {"interactive",  no_argument, 0, 'i' },
   {"force",        no_argument, 0, 'f' },
   {0,              0,           0, 0   }
};

static void using(void) {
    fprintf(stderr, "using:\n\t%s [-hifrRv] <file...>\n", progname);
    exit(1);
}

static bool file_exists(const char* path) {
    int file = open(path, O_RDONLY);
    if (file < 0) {
        return false;
    }
    close(file);
    return true;
}

static bool is_directory(const char* path) {
    struct stat st;
    if (stat(path, &st) < 0) {
        perror("stat");
        exit(1);
    }
    return st.st_mode & S_IFDIR;
}

//#define MMAP_WORK
#ifdef MMAP_WORK

static void copy_file(const char* path_src, const char* path_dst) {
    if ((flag_i && !flag_f) && file_exists(path_dst)) {
        printf("do you want remove '%s': ", path_dst);
        if (getchar() == 'y')
            return;
    }

    int input = open(path_src, O_RDONLY);
    if (input < 0) {
        perror("open");
        exit(1);
    }

    struct stat st;
    if (fstat(input, &st) < 0) {
        perror("fstat");
        exit(1);
    }

    void* buf = mmap(NULL, st.st_size, PROT_READ, MAP_SHARED, input, 0);
    if (buf == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    int output = open(path_dst, O_WRONLY | O_CREAT | O_TRUNC, st.st_mode);
    if (output < 0) {
        perror("open");
        exit(1);
    }

    write(output, buf, st.st_size);
    munmap(buf, st.st_size);
    close(input);
    close(output);

    if (flag_v)
        printf("copy %s to %s\n", path_src, path_dst);
}

#else

static void copy_file(const char* path_src, const char* path_dst) {
    if ((flag_i && !flag_f) && file_exists(path_dst)) {
        printf("do you want remove '%s': ", path_dst);
        if (getchar() == 'y')
            return;
    }

    FILE *file = fopen(path_src, "r");
    if (file == NULL) {
        perror("fopen");
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    void* buffer = malloc(file_size);
    if (buffer == NULL) {
        perror("malloc");
        exit(1);
    }

    FILE *file_save = fopen(path_dst, "w");
    if (file_save == NULL) {
        perror("fopen");
        exit(1);
    }

    fread(buffer, 1, file_size, file);
    fwrite(buffer, 1, file_size, file_save);
    free(buffer);
    fclose(file);
    fclose(file_save);

    if (flag_v)
        printf("copy %s to %s\n", path_src, path_dst);
}

#endif

//static void recurvece_copy(const char* path_src, const char* path_dst) {
//    // TODO copy folders.
//}

int main(int argc, char* argv[]) {
    progname = argv[0];
    char ch;
    while ((ch = getopt_long(argc, argv, "hifrRv", opts, NULL)) != -1) {
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
        case 'v':
            flag_v = true;
            break;
        default:
            using();
        }
    }
    argc -= optind;
    argv += optind;

    if (argc == 2) {
        copy_file(argv[0], argv[1]);
    } else if (argc > 2) {
        if (is_directory(argv[argc - 1])) {
            for (int i = 0; i < argc - 1; i++) {
                char buf[0x4000] = {0}; 
                // TODO fuster 
                strcat(buf, argv[argc - 1]);
                strcat(buf, "/");
                strcat(buf, argv[i]);
                printf("%s\n", buf);
                copy_file(argv[i], buf);
            }
        } else {
            fprintf(stderr, "Destnation must be a directory.\n");
        }
    } else {
        using();
    }
    return 0;
}

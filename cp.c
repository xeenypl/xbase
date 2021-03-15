#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

static bool flag_n = false;
static bool flag_f = false;

static bool file_exists(const char* path) {
    int file = open(path, O_RDONLY);
    if (file < 0)
        return false;
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

static void copy_file(const char* path_src, const char* path_dst) {
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
    if ((!flag_n && flag_f) && file_exists(path_dst)) {
        // TODO ask to confurm
    }
    int output = open(path_dst, O_WRONLY | O_CREAT | O_TRUNC, st.st_mode);
    if (output < 0) {
        perror("fopen");
        exit(1);
    }
    write(output, buf, st.st_size);
    close(input);
    close(output);
}

int main(int argc, char* argv[]) {
    if (argc == 3) {
        copy_file(argv[1], argv[2]);
    }
    if (argc > 3) {
        if (is_directory(argv[argc - 1])) {
            for (int i = 1; i < argc - 1; i++) {
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
    }
    return 0;
}

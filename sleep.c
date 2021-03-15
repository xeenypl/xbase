#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

static const char* progname = NULL;
static struct option opts[] = {
   {"help", no_argument, 0, 'h' },
   {0,      0,           0, 0   }
};

static void using(void) {
    fprintf(stderr, "using:\n\t%s <number>\n", progname);
    exit(1);
}

int main(int argc, char* argv[]) {
    progname = argv[0];
    char ch;
    while ((ch = getopt_long(argc, argv, "h", opts, NULL)) != -1) {
        switch(ch) {
	    default:
		    using();
	    }
    }
    argc -= optind;
    argv += optind;
    if (argc != 1)
        using();
    sleep(atoi(argv[0]));
    return 0;
}

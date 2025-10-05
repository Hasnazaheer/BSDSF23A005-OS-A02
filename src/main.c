#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>

void list_directory(const char *path, int long_listing, int horizontal);

int main(int argc, char *argv[]) {
    int opt;
    int long_listing = 0;
    int horizontal = 0;

    while ((opt = getopt(argc, argv, "lx")) != -1) {
        if (opt == 'l')
            long_listing = 1;
        else if (opt == 'x')
            horizontal = 1;
        else
            return 1;
    }

    const char *path = (optind < argc) ? argv[optind] : ".";
    list_directory(path, long_listing, horizontal);
    return 0;
}


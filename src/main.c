#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void list_directory_long_listing(const char *path);
void list_directory_column_display(const char *path);
void list_directory_horizontal_display(const char *path);

int main(int argc, char *argv[]) {
    int opt;
    int display_mode = 0;  // 0 = default, 1 = long (-l), 2 = horizontal (-x)

    while ((opt = getopt(argc, argv, "lx")) != -1) {
        switch (opt) {
            case 'l':
                display_mode = 1;
                break;
            case 'x':
                display_mode = 2;
                break;
            default:
                fprintf(stderr, "Usage: %s [-l | -x] [directory]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    const char *path = (optind < argc) ? argv[optind] : ".";

    if (display_mode == 1)
        list_directory_long_listing(path);
    else if (display_mode == 2)
        list_directory_horizontal_display(path);
    else
        list_directory_column_display(path);

    return 0;
}

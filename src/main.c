#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>   // ✅ for getopt(), optind

// Function prototype
void do_ls(const char *dirname, int recursive_flag);

int main(int argc, char *argv[]) {
    int opt;
    int recursive_flag = 0;
    char *target_dir = "."; // Default directory

    // Parse command-line options (-R)
    while ((opt = getopt(argc, argv, "R")) != -1) {
        switch (opt) {
            case 'R':
                recursive_flag = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-R] [directory]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    // If user passed a directory name after options
    if (optind < argc)
        target_dir = argv[optind];

    // Call recursive ls implementation
    do_ls(target_dir, recursive_flag);

    return 0;
}

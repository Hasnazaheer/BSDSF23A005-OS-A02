#include "lsv1.2.0.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    const char *path = (argc > 1) ? argv[1] : ".";
    list_directory_column_display(path);
    return 0;
}


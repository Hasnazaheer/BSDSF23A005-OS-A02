#define _POSIX_C_SOURCE 200809L
#include "lsv1.2.0.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/ioctl.h>
#include <unistd.h>

void list_directory_column_display(const char *path) {
    DIR *dir = opendir(path);
    if (!dir) {
        perror("opendir");
        return;
    }

    struct dirent *entry;
    int capacity = 50, count = 0, max_len = 0;
    char **files = malloc(capacity * sizeof(char *));
    if (!files) return;

    // Read all filenames
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.') continue; // skip hidden
        if (count >= capacity) {
            capacity *= 2;
            files = realloc(files, capacity * sizeof(char *));
        }
        files[count] = strdup(entry->d_name);
        int len = strlen(entry->d_name);
        if (len > max_len) max_len = len;
        count++;
    }
    closedir(dir);

    // Sort filenames alphabetically
    qsort(files, count, sizeof(char *), (int (*)(const void *, const void *))strcmp);

    // Get terminal width
    struct winsize ws;
    int term_width = 80;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == 0)
        term_width = ws.ws_col;

    // Calculate columns and rows
    int spacing = 2;
    int col_width = max_len + spacing;
    int num_cols = term_width / col_width;
    if (num_cols < 1) num_cols = 1;
    int num_rows = (count + num_cols - 1) / num_cols;

    // Print in "down then across" order
    for (int r = 0; r < num_rows; r++) {
        for (int c = 0; c < num_cols; c++) {
            int idx = c * num_rows + r;
            if (idx < count)
                printf("%-*s", col_width, files[idx]);
        }
        printf("\n");
    }

    for (int i = 0; i < count; i++) free(files[i]);
    free(files);
}

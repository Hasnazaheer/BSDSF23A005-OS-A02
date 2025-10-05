#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

// ---------- Helper: Long Listing ----------
void list_directory_long_listing(const char *path) {
    DIR *dir = opendir(path);
    if (!dir) {
        perror("opendir");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        struct stat st;
        char fullpath[512];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

        if (stat(fullpath, &st) == -1) {
            perror("stat");
            continue;
        }

        printf("%10ld %s\n", st.st_size, entry->d_name);
    }

    closedir(dir);
}

// ---------- Helper: Down-Then-Across (default) ----------
void list_directory_column_display(const char *path) {
    struct dirent **namelist;
    int n = scandir(path, &namelist, NULL, alphasort);
    if (n < 0) {
        perror("scandir");
        return;
    }

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int term_width = w.ws_col;

    int maxlen = 0;
    for (int i = 0; i < n; i++) {
        int len = strlen(namelist[i]->d_name);
        if (len > maxlen) maxlen = len;
    }

    int col_width = maxlen + 2;
    int cols = term_width / col_width;
    if (cols == 0) cols = 1;

    int rows = (n + cols - 1) / cols;

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            int idx = c * rows + r;
            if (idx < n)
                printf("%-*s", col_width, namelist[idx]->d_name);
        }
        printf("\n");
    }

    for (int i = 0; i < n; i++)
        free(namelist[i]);
    free(namelist);
}

// ---------- Helper: Horizontal Display (-x) ----------
void list_directory_horizontal_display(const char *path) {
    struct dirent **namelist;
    int n = scandir(path, &namelist, NULL, alphasort);
    if (n < 0) {
        perror("scandir");
        return;
    }

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int term_width = w.ws_col;

    int maxlen = 0;
    for (int i = 0; i < n; i++) {
        int len = strlen(namelist[i]->d_name);
        if (len > maxlen) maxlen = len;
    }

    int col_width = maxlen + 2;
    int current_width = 0;

    for (int i = 0; i < n; i++) {
        int len = strlen(namelist[i]->d_name);

        if (current_width + col_width > term_width) {
            printf("\n");
            current_width = 0;
        }

        printf("%-*s", col_width, namelist[i]->d_name);
        current_width += col_width;
        free(namelist[i]);
    }

    free(namelist);
    printf("\n");
}

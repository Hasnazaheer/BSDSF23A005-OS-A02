#define _GNU_SOURCE   // ✅ enables strdup and other GNU extensions

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>    // ✅ for lstat()
#include <sys/stat.h>     // ✅ for S_ISDIR, S_ISLNK, S_ISSOCK
#include <unistd.h>
#include <limits.h>       // ✅ for PATH_MAX
#include <errno.h>

// === ANSI Color Codes ===
#define COLOR_RESET   "\033[0m"
#define COLOR_BLUE    "\033[1;34m"
#define COLOR_GREEN   "\033[0;32m"
#define COLOR_RED     "\033[0;31m"
#define COLOR_PINK    "\033[1;35m"
#define COLOR_REVERSE "\033[7m"

// === Function Prototypes ===
void do_ls(const char *dirname, int recursive_flag);
void print_colored_name(const char *path, const char *name);
int compare(const void *a, const void *b);

// === Compare Function for Sorting Filenames ===
int compare(const void *a, const void *b) {
    const char **str_a = (const char **)a;
    const char **str_b = (const char **)b;
    return strcmp(*str_a, *str_b);
}

// === Print Filename with Color Based on Type ===
void print_colored_name(const char *path, const char *name) {
    struct stat st;
    char fullpath[PATH_MAX];
    snprintf(fullpath, sizeof(fullpath), "%s/%s", path, name);

    if (lstat(fullpath, &st) == -1) {
        perror("stat");
        printf("%s\n", name);
        return;
    }

    // Apply color logic
    if (S_ISDIR(st.st_mode))
        printf(COLOR_BLUE "%s" COLOR_RESET "\n", name);
    else if (S_ISLNK(st.st_mode))
        printf(COLOR_PINK "%s" COLOR_RESET "\n", name);
    else if (st.st_mode & S_IXUSR)
        printf(COLOR_GREEN "%s" COLOR_RESET "\n", name);
    else if (strstr(name, ".tar") || strstr(name, ".gz") || strstr(name, ".zip"))
        printf(COLOR_RED "%s" COLOR_RESET "\n", name);
    else if (S_ISCHR(st.st_mode) || S_ISBLK(st.st_mode) || S_ISSOCK(st.st_mode))
        printf(COLOR_REVERSE "%s" COLOR_RESET "\n", name);
    else
        printf("%s\n", name);
}

// === Recursive LS Function ===
void do_ls(const char *dirname, int recursive_flag) {
    DIR *dirp;
    struct dirent *entry;
    struct stat st;
    char **filenames = NULL;
    int count = 0;

    printf("%s:\n", dirname);

    dirp = opendir(dirname);
    if (dirp == NULL) {
        perror(dirname);
        return;
    }

    // Step 1: Read all entries
    while ((entry = readdir(dirp)) != NULL) {
        filenames = realloc(filenames, sizeof(char*) * (count + 1));
        filenames[count] = strdup(entry->d_name);
        count++;
    }
    closedir(dirp);

    // Step 2: Sort alphabetically
    qsort(filenames, count, sizeof(char*), compare);

    // Step 3: Print entries
    for (int i = 0; i < count; i++) {
        print_colored_name(dirname, filenames[i]);
    }

    // Step 4: Recursive Descent
    if (recursive_flag) {
        for (int i = 0; i < count; i++) {
            if (strcmp(filenames[i], ".") == 0 || strcmp(filenames[i], "..") == 0)
                continue;

            char path[PATH_MAX];
            snprintf(path, sizeof(path), "%s/%s", dirname, filenames[i]);

            if (lstat(path, &st) == -1)
                continue;

            if (S_ISDIR(st.st_mode)) {
                printf("\n");
                do_ls(path, recursive_flag);
            }
        }
    }

    // Step 5: Free memory
    for (int i = 0; i < count; i++)
        free(filenames[i]);
    free(filenames);
}

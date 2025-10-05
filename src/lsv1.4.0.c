#define _GNU_SOURCE
#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

// ---------- Comparison function for qsort ----------
int compare_names(const void *a, const void *b) {
    const char *nameA = *(const char **)a;
    const char *nameB = *(const char **)b;
    return strcmp(nameA, nameB);
}

// ---------- Function to list directory ----------
void list_directory(const char *path, int long_listing, int horizontal) {
    struct dirent **namelist;
    int n = scandir(path, &namelist, NULL, NULL);
    if (n < 0) {
        perror("scandir");
        return;
    }

    // Allocate array for names
    char **filenames = malloc(n * sizeof(char *));
    if (!filenames) {
        perror("malloc");
        return;
    }

    int count = 0;
    for (int i = 0; i < n; i++) {
        if (namelist[i]->d_name[0] == '.')
            continue; // skip hidden
        filenames[count++] = strdup(namelist[i]->d_name);
    }

    // ---------- Sort the filenames ----------
    qsort(filenames, count, sizeof(char *), compare_names);

    // ---------- Display ----------
    for (int i = 0; i < count; i++) {
        if (long_listing) {
            struct stat st;
            if (stat(filenames[i], &st) == 0)
                printf("%-20s\t%ld bytes\n", filenames[i], st.st_size);
        } else if (horizontal) {
            printf("%-20s", filenames[i]);
        } else {
            printf("%s\n", filenames[i]);
        }
        free(filenames[i]);
    }

    if (horizontal)
        printf("\n");

    free(filenames);

    // Free scandir data
    for (int i = 0; i < n; i++)
        free(namelist[i]);
    free(namelist);
}

#ifndef LSV1_1_0_H
#define LSV1_1_0_H

#include <sys/types.h>

extern int long_listing;

void do_ls(const char *dir);
void do_ls_long(const char *dir);
void print_file_long(const char *path, const char *filename);
void print_permissions(mode_t mode);

#endif

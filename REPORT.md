1.Difference between stat() and lstat()

stat() follows symbolic links and returns information about the target file.

lstat() returns information about the link itself, not its target.
In an ls command, lstat() is more appropriate because ls -l should display link info rather than the file it points to.

2.Using st_mode and Bitwise Macros

st_mode contains both file type and permissions.
We use bitwise AND (&) with predefined macros to extract data:

if (info.st_mode & S_IFDIR)
    printf("This is a directory\n");

if (info.st_mode & S_IRUSR)
    printf("Owner has read permission\n");


Here:

S_IFDIR tests if it’s a directory

S_IRUSR, S_IWUSR, S_IXUSR represent read/write/execute for owner

Similarly for group (S_IRGRP, etc.) and others (S_IROTH, etc.)

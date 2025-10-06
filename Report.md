# REPORT.md

## Version 1.3.0 – Horizontal Column Display (-x)

### Comparison of Vertical vs Horizontal Logic
The **vertical “down-then-across”** layout requires pre-calculating rows and columns
based on terminal width, dividing filenames into column groups, and printing in
column-major order. This involves more logic and indexing complexity.

The **horizontal “across” layout** is simpler — it prints sequentially from left to right
and wraps lines when the next filename would exceed terminal width.  
Hence, the vertical logic is more complex because it requires two-dimensional
layout planning, whereas horizontal printing is a straightforward one-pass loop.

### Display Mode Management Strategy
A single integer variable `display_mode` was used to track output modes:
- `0` → Default “down-then-across”
- `1` → Long Listing (`-l`)
- `2` → Horizontal (`-x`)

The mode is set during `getopt()` parsing.  
After reading the directory entries, the program uses simple conditionals:
```c
if (display_mode == 1)
    list_directory_long_listing(path);
else if (display_mode == 2)
    list_directory_horizontal_display(path);
else
    list_directory_column_display(path);

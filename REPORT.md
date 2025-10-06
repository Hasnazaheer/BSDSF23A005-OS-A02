Q1. How do ANSI escape codes work to produce color in a standard Linux terminal? Show the specific code sequence for printing text in green.

ANSI escape codes are special sequences of characters that the terminal interprets as formatting instructions rather than normal text.
Each code starts with \033[ (escape character + [), followed by parameters, and ends with m.
For example, \033[0;32m sets text color to green, and \033[0m resets to default.
Example:

printf("\033[0;32mHello in Green!\033[0m\n");


Q2. To color an executable file, you need to check its permission bits. Explain which bits in the st_mode field you need to check to determine if a file is executable by the owner, group, or other.

The st_mode field of the stat structure stores file permissions.
To check if a file is executable:

Owner execute bit: S_IXUSR

Group execute bit: S_IXGRP

Others execute bit: S_IXOTH

If any of these bits are set, the file can be executed by that category of users.


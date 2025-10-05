Q1:
A single loop prints all filenames sequentially, but in “down-then-across” layout, each row contains items spaced evenly across columns.
To achieve this, we compute number of rows and columns, then use a nested loop: for each row, print elements at indexes separated by num_rows.
This ensures vertical (down) then horizontal (across) order.

Q2:
ioctl with TIOCGWINSZ retrieves the current terminal width.
If we only used a fixed width (e.g., 80 chars), the output would break alignment when users resize the window or use larger/smaller terminals — reducing flexibility and accuracy.

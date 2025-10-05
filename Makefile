CC = gcc
CFLAGS = -Wall -Wextra -std=c11
OBJDIR = obj
BINDIR = bin
SRCDIR = src

TARGET = $(BINDIR)/lsv1.2.0
OBJS = $(OBJDIR)/main.o $(OBJDIR)/lsv1.2.0.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(OBJDIR) $(BINDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(BINDIR)

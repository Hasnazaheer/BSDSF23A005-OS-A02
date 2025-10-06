CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = bin/ls
SRC = src/main.c src/lsv1.6.0.c

all:
	mkdir -p bin
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -rf bin

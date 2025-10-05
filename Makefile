CC = gcc
CFLAGS = -Wall -Wextra -std=c11
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/lsv1.1.0.c
OBJS = $(OBJ_DIR)/main.o $(OBJ_DIR)/lsv1.1.0.o
TARGET = $(BIN_DIR)/lsv1.1.0

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean


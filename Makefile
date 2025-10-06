# -----------------------------
# Makefile for ls-v1.5.0
# -----------------------------

CC = gcc
CFLAGS = -Wall -Wextra -std=c11

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

SRC = $(SRC_DIR)/main.c $(SRC_DIR)/lsv1.5.0.c
OBJ = $(OBJ_DIR)/main.o $(OBJ_DIR)/lsv1.5.0.o
TARGET = $(BIN_DIR)/ls

# Default target
all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

run: all
	./$(TARGET)

.PHONY: all clean run

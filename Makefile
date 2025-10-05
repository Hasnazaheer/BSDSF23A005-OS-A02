# Makefile for ls-v1.0.0
# Author: Your Name / Roll No
# Description: Builds the ls-v1.0.0 program and places the output in bin/

# Compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Directories
SRC_DIR = src
BIN_DIR = bin
OBJ_DIR = obj

# Target executable name
TARGET = $(BIN_DIR)/ls

# Source and object files
SRC = $(SRC_DIR)/ls-v1.0.0.c
OBJ = $(OBJ_DIR)/ls-v1.0.0.o

# Default target
all: directories $(TARGET)

# Rule to create required directories if missing
directories:
	@mkdir -p $(BIN_DIR) $(OBJ_DIR)

# Link object files to create the executable
$(TARGET): $(OBJ)
	@echo "Linking..."
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)
	@echo "Build complete! Executable -> $(TARGET)"

# Compile source file into object file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Compiling $< ..."
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	@echo "Cleaning up..."
	rm -f $(OBJ_DIR)/*.o $(TARGET)
	@echo "Clean complete."

# Run the program
run: all
	@echo "Running program..."
	./$(TARGET)


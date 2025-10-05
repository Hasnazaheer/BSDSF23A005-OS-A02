
CC = gcc
CFLAGS = -Wall -Wextra -std=c11
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TARGET = $(BIN_DIR)/lsv1.4.0

OBJS = $(OBJ_DIR)/main.o $(OBJ_DIR)/lsv1.4.0.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c
	mkdir -p $(OBJ_DIR) $(BIN_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.c -o $(OBJ_DIR)/main.o

$(OBJ_DIR)/lsv1.4.0.o: $(SRC_DIR)/lsv1.4.0.c
	mkdir -p $(OBJ_DIR) $(BIN_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/lsv1.4.0.c -o $(OBJ_DIR)/lsv1.4.0.o

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

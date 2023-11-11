CC = gcc
CFLAGS = -g

BIN_DIR = bin
OBJ_DIR = obj
SRC_DIR = src

.PHONY: all clean always

all: $(BIN_DIR)

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c
	$(CC) $< -c -o $@

$(BIN_DIR): always $(OBJ_DIR)/main.o
	$(CC) $(OBJ_DIR)/main.o -o $@/bin

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	clear

always:
	mkdir -p $(BIN_DIR) $(OBJ_DIR)

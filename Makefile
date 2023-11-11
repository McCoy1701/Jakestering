CC = gcc
CINC = -Iinclude
CFLAGS = -g

BIN_DIR = bin
OBJ_DIR = obj
SRC_DIR = src

.PHONY: all clean always

all: $(BIN_DIR)

$(OBJ_DIR)/jakestering.o: $(SRC_DIR)/jakestering.c
	$(CC) $< -c $(CINC) -o $@

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c
	$(CC) $< -c $(CINC) -o $@

$(BIN_DIR): always $(OBJ_DIR)/main.o $(OBJ_DIR)/jakestering.o
	$(CC) $(OBJ_DIR)/main.o $(OBJ_DIR)/jakestering.o -o $@/bin

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	clear

always:
	mkdir -p $(BIN_DIR) $(OBJ_DIR)

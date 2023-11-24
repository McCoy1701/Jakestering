CC = gcc
CINC = -Iinclude
CFLAGS = -g 

BIN_DIR = bin
OBJ_DIR = obj
SRC_DIR = src

.PHONY: all clean always

all: $(BIN_DIR)

$(OBJ_DIR)/keypad.o: $(SRC_DIR)/keypad.c
	$(CC) $< -c $(CINC) -o $@

$(OBJ_DIR)/lcd.o: $(SRC_DIR)/lcd.c
	$(CC) $< -c $(CINC) -o $@

$(OBJ_DIR)/lcd128x64.o: $(SRC_DIR)/lcd128x64.c
	$(CC) $< -c $(CINC) -o $@

$(OBJ_DIR)/jakestering.o: $(SRC_DIR)/jakestering.c
	$(CC) $< -c $(CINC) -o $@

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c
	$(CC) $< -c $(CINC) -o $@

$(BIN_DIR): always $(OBJ_DIR)/main.o $(OBJ_DIR)/jakestering.o $(OBJ_DIR)/keypad.o $(OBJ_DIR)/lcd.o
	$(CC) $(OBJ_DIR)/main.o $(OBJ_DIR)/jakestering.o $(OBJ_DIR)/keypad.o $(OBJ_DIR)/lcd.o $(CFLAGS) -o $@/bin

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	clear

always:
	mkdir -p $(BIN_DIR) $(OBJ_DIR)

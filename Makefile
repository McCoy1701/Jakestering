CC = gcc
CINC = -Iinclude
CFLAGS = -g -lm 

BIN_DIR = bin
OBJ_DIR = obj
SRC_DIR = src
JAKESTERING_DIR = jakestering

.PHONY: all clean always

all: $(BIN_DIR)

$(OBJ_DIR)/keypad.o: $(JAKESTERING_DIR)/keypad.c
	$(CC) $< -c $(CINC) -o $@

$(OBJ_DIR)/lcd.o: $(JAKESTERING_DIR)/lcd.c
	$(CC) $< -c $(CINC) -o $@

$(OBJ_DIR)/lcd128x64.o: $(JAKESTERING_DIR)/lcd128x64.c
	$(CC) $< -c $(CINC) -o $@

$(OBJ_DIR)/jakestering.o: $(JAKESTERING_DIR)/jakestering.c
	$(CC) $< -c $(CINC) -o $@

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c
	$(CC) $< -c $(CINC) -o $@

$(BIN_DIR): always $(OBJ_DIR)/main.o $(OBJ_DIR)/jakestering.o $(OBJ_DIR)/lcd128x64.o
	$(CC) $(OBJ_DIR)/main.o $(OBJ_DIR)/jakestering.o $(OBJ_DIR)/lcd128x64.o $(CFLAGS) -o $@/bin

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	clear

always:
	mkdir -p $(BIN_DIR) $(OBJ_DIR)

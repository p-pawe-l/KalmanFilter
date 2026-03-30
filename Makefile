CC = gcc
CFLAGS = -Wall -Wextra -I./include
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TARGET = $(BIN_DIR)/program
MAIN_SOURCE = main.c
MAIN_OBJECT = $(OBJ_DIR)/main.o

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o) $(MAIN_OBJECT)

all: $(TARGET)

$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(MAIN_OBJECT): $(MAIN_SOURCE) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

format:
	clang-format -i $(SRC_DIR)/*.c include/*.h

format-all:
	clang-format -i $(SRC_DIR)/*.c include/*.h $(MAIN_SOURCE)	

.PHONY: all clean format format-all

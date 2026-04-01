CC = gcc
CFLAGS = -Wall -Wextra -I./include
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TEST_DIR = tests
TEST_BIN_DIR = $(BIN_DIR)/tests
TARGET = $(BIN_DIR)/program
MAIN_SOURCE = main.c
MAIN_OBJECT = $(OBJ_DIR)/main.o

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o) $(MAIN_OBJECT)
HEADERS = $(wildcard include/*.h)

TEST_SOURCES = $(wildcard $(TEST_DIR)/*.c)
TEST_BINARIES = $(TEST_SOURCES:$(TEST_DIR)/%.c=$(TEST_BIN_DIR)/%)

all: $(TARGET)

$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(MAIN_OBJECT): $(MAIN_SOURCE) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(TEST_BIN_DIR)/%: $(TEST_DIR)/%.c $(SOURCES) $(HEADERS) | $(TEST_BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $(TEST_DIR)/$*.c $(SOURCES) -lm

test: $(TEST_BINARIES)
	@failed=0; \
	for t in $(TEST_BINARIES); do \
		echo "Running $$t..."; \
		$$t || failed=1; \
	done; \
	exit $$failed

$(BIN_DIR) $(OBJ_DIR) $(TEST_BIN_DIR):
	mkdir -p $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

format:
	clang-format -i $(SRC_DIR)/*.c include/*.h

format-all:
	clang-format -i $(SRC_DIR)/*.c include/*.h $(MAIN_SOURCE)

.PHONY: all clean format format-all test

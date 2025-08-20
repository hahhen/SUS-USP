CC = gcc
CFLAGS = -Wall -std=c99
INCLUDES = -I./pilha -I./no

BUILD_DIR = ./build
SRC_DIR = ./src
NO_DIR = ./no
PILHA_DIR = ./pilha

C_FILES = $(wildcard *.c) $(wildcard $(NO_DIR)/*.c) $(wildcard $(PILHA_DIR)/*.c)
OBJ_FILES = $(patsubst %.c, $(BUILD_DIR)/%.o, $(notdir $(C_FILES)))

TARGET = main

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ_FILES)

$(BUILD_DIR)/%.o: $(NO_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/%.o: $(PILHA_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

CC = g++
CFLAGS = -Wall -Iinclude -std=c++17

SRC_DIR = src
BIN_DIR = bin

# Use shell to find all .cpp files in SRC_DIR and its subdirectories
SRCS := $(shell find $(SRC_DIR) -name '*.cpp')

OUT = $(BIN_DIR)/wordle-solver

all: $(OUT)

$(OUT): $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(BIN_DIR)/*

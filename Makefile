CC = g++
CFLAGS = -Wall -Iinclude

SRC_DIR = src
BIN_DIR = bin

SRCS = $(SRC_DIR)/WordleSolver.cpp $(SRC_DIR)/Controller.cpp $(SRC_DIR)/main.cpp

OUT = $(BIN_DIR)/main

all: $(OUT)

$(OUT): $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(BIN_DIR)/*

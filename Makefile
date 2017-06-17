TARGET := main
BIN_DIR := bin
OBJ_DIR := obj
SRC_DIR := src
LIBS := -lpthread

CM_O_FILES := $(OBJ_DIR)/main.o $(OBJ_DIR)/data.o $(OBJ_DIR)/exp.o

.PHONY: all clean clean-data configure help

help:
	cat "info/Makefile_help"

all: 
	configure
	clean
	$(BIN_DIR)/$(TARGET)

clean-data:
	rm -r $(BIN_DIR)/data/*

configure:
	mkdir -p obj
	mkdir -p bin
	mkdir -p bin/data

clean:
	rm -r $(BIN_DIR)/$(TARGET) $(OBJ_DIR)/*.o

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c
	gcc -c -o $(OBJ_DIR)/main.o $(SRC_DIR)/main.c

$(OBJ_DIR)/data.o: $(SRC_DIR)/data.c
	gcc -c -o $(OBJ_DIR)/data.o $(SRC_DIR)/data.c
	
$(OBJ_DIR)/exp.o: $(SRC_DIR)/exp.c
	gcc -c -o $(OBJ_DIR)/exp.o $(SRC_DIR)/exp.c

$(BIN_DIR)/$(TARGET): $(CM_O_FILES)
	gcc -o $(BIN_DIR)/$(TARGET) $(CM_O_FILES) $(LIBS)
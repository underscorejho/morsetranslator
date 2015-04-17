
# Jared Henry Oviatt

# All C source projects should be in src/
# src/*.c
# src/obj/*.o
# inc/*.h

# project name
PROJ_NAME=

# choose a compiler
# gcc for C programs
CC=gcc

# choose compiler flags
# -Wall     # turns on most compiler warnings
# -Wextra   #
# -std=c99  # use c99 standard when compiling
CFLAGS= -Wall -Wextra -std=c99






# source directory
SRC_DIR=src

# object directory
OBJ_DIR=obj

# include directory
INC_DIR=inc

# binary directory
BIN_DIR=bin

# souce files
SRC=$(patsubst $(SRC_DIR)/%.c,%.c,$(wildcard $(SRC_DIR)/*.c))

# object files
OBJ=$(patsubst %.c,$(SRC_DIR)/$(OBJ_DIR)/%.o,$(SRC))

# dependencies on includes
DEPS=$(wildcard $(INC_DIR)/*.h)

# define TARGET
TARGET=$(BIN_DIR)/$(PROJ_NAME)


# rule that individual objects rely on .c versions and .h files
# needs to compile to .o files, then compile to executable
$(SRC_DIR)/$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# actual compile commands
$(PROJ_NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)






# rule to create obj and bin directories
.PHONY: dir
dir:
	test -d $(BIN_DIR) || mkdir $(BIN_DIR)
	test -d $(SRC_DIR)/$(OBJ_DIR) || mkdir $(SRC_DIR)/$(OBJ_DIR)

# clean command
#.PHONY prevents it from looking for file named clean
.PHONY : clean
clean :
	rm -r $(SRC_DIR)/$(OBJ_DIR) 

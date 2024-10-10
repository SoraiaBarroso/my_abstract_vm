# Compiler
C = g++

# Compiler flags
CFLAGS = -Wall -Wextra -std=c++17

# Executable name
TARGET = my_abstract_vm

# Source and Object directories
SRC_DIR = src
OBJ_DIR = obj

# Source files
SRCS = $(SRC_DIR)/MyAbstractVm.cpp $(SRC_DIR)/HelperFunctions.cpp $(SRC_DIR)/InstructionParser.cpp

# Object files
OBJS = $(OBJ_DIR)/MyAbstractVm.o $(OBJ_DIR)/HelperFunctions.o $(OBJ_DIR)/InstructionParser.o

# Default target
all: $(TARGET)

# Linking
$(TARGET): $(OBJS)
	$(C) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compiling
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
 	@mkdir -p $(OBJ_DIR) # Ensure obj directory exists 
	$(C) $(CFLAGS) -c $< -o $@

# Clean
clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)

# Phony targets
.PHONY: all clean

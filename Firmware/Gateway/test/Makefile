# Makefile for building the application
# Compiler
CC := g++

# Compiler flags
CFLAGS := -Wall -Wextra -std=c++11

# Include path
INCLUDES := -I../src

# Source files
SOURCES := $(filter-out ../src/LoRaHandler/% ../src/main.cpp, $(wildcard ../src/**/*.cpp ../src/*.cpp ./*.cpp ))

# Object files
BUILD_DIR := ../build
OBJECTS := $(patsubst ../src/%, $(BUILD_DIR)/%, $(SOURCES:.cpp=.o))

# Target executable
TARGET := $(BUILD_DIR)/main

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@

$(BUILD_DIR)/%.o: ../src/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
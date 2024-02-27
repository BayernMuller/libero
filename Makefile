CXX := g++
BUILD_DIR := build
SOURCE_DIR := .
LIBERO_DIR := libero

SOURCES := $(wildcard $(SOURCE_DIR)/*.cpp)
LIBERO_SOURCES := $(wildcard $(LIBERO_DIR)/*.cpp)
OBJECTS := $(patsubst $(SOURCE_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SOURCES))
LIBERO_OBJECTS := $(patsubst $(LIBERO_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(LIBERO_SOURCES))

CXXFLAGS := -std=c++11 -Wall -Wextra -I$(SOURCE_DIR) -I$(LIBERO_DIR)
LDFLAGS := 

EXECUTABLE := $(BUILD_DIR)/main

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) $(LIBERO_OBJECTS)
	$(CXX) $(LDFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(LIBERO_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean

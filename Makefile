# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror
BUILD_DIR = build

# Directories
CUSTOMER_DIR = customer
DELIVERY_DIR = delivery
SYSTEM_DIR = system

# Include directories
CUSTOMER_INC = -I$(CUSTOMER_DIR) -I$(SYSTEM_DIR)/include/public
DELIVERY_INC = -I$(DELIVERY_DIR) -I$(SYSTEM_DIR)/include/public
SYSTEM_INC = -I$(SYSTEM_DIR)/include
MAIN_INC = -I$(CUSTOMER_DIR) -I$(DELIVERY_DIR) -I$(SYSTEM_DIR)/include

# Source files
CUSTOMER_SRC = $(wildcard $(CUSTOMER_DIR)/*.cpp)
DELIVERY_SRC = $(wildcard $(DELIVERY_DIR)/*.cpp)
SYSTEM_SRC = $(wildcard $(SYSTEM_DIR)/src/*.cpp)
MAIN_SRC = main.cpp

# Object files
CUSTOMER_OBJ = $(patsubst $(CUSTOMER_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(CUSTOMER_SRC))
DELIVERY_OBJ = $(patsubst $(DELIVERY_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(DELIVERY_SRC))
SYSTEM_OBJ = $(patsubst $(SYSTEM_DIR)/src/%.cpp, $(BUILD_DIR)/%.o, $(SYSTEM_SRC))
MAIN_OBJ = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(MAIN_SRC))

# Binary
MAIN_BIN = locker_system

# Debug flag
DEBUG ?= 0
ifeq ($(DEBUG), 1)
    CXXFLAGS += -g
endif

# Targets
all: dir $(MAIN_BIN)

dir:
	mkdir -p $(BUILD_DIR)

$(MAIN_BIN): $(SYSTEM_OBJ) $(CUSTOMER_OBJ) $(DELIVERY_OBJ) $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(CUSTOMER_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(CUSTOMER_INC) -c $< -o $@

$(BUILD_DIR)/%.o: $(DELIVERY_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(DELIVERY_INC) -c $< -o $@

$(BUILD_DIR)/%.o: $(SYSTEM_DIR)/src/%.cpp
	$(CXX) $(CXXFLAGS) $(SYSTEM_INC) -c $< -o $@

$(BUILD_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(MAIN_INC) -c $< -o $@

# Clean up
clean:
	rm -f $(BUILD_DIR)/*.o $(MAIN_BIN)

.PHONY: all clean

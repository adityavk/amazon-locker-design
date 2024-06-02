# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror

# Directories
CUSTOMER_DIR = customer
DELIVERY_DIR = delivery
SYSTEM_DIR = system

# Include directories
CUSTOMER_INC = -I$(CUSTOMER_DIR) -I$(SYSTEM_DIR)/include/public
DELIVERY_INC = -I$(DELIVERY_DIR) -I$(SYSTEM_DIR)/include/public
SYSTEM_INC = -I$(SYSTEM_DIR)/include
MAIN_INC = -I$(CUSTOMER_DIR) -I$(DELIVERY_DIR) -I$(SYSTEM_DIR)/include/public -I$(SYSTEM_DIR)/include/admin

# Source files
CUSTOMER_SRC = $(CUSTOMER_DIR)/*.cpp
DELIVERY_SRC = $(DELIVERY_DIR)/*.cpp
SYSTEM_SRC = $(SYSTEM_DIR)/src/*.cpp
MAIN_SRC = main.cpp

# Object files
CUSTOMER_OBJ = $(CUSTOMER_SRC:.cpp=.o)
DELIVERY_OBJ = $(DELIVERY_SRC:.cpp=.o)
SYSTEM_OBJ = $(SYSTEM_SRC:.cpp=.o)
MAIN_OBJ = $(MAIN_SRC:.cpp=.o)

# Binary
MAIN_BIN = locker_system

# Targets
all: $(MAIN_BIN)

$(MAIN_BIN): $(SYSTEM_OBJ) $(CUSTOMER_OBJ) $(DELIVERY_OBJ) $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(CUSTOMER_OBJ): $(CUSTOMER_SRC)
	$(CXX) $(CXXFLAGS) -c $^ -I$(CUSTOMER_INC)

$(DELIVERY_OBJ): $(DELIVERY_SRC)
	$(CXX) $(CXXFLAGS) -c $^ -I$(DELIVERY_INC)

$(SYSTEM_OBJ): $(SYSTEM_SRC)
	$(CXX) $(CXXFLAGS) -c $^ -I$(SYSTEM_INC)

$(MAIN_OBJ): $(MAIN_SRC)
	$(CXX) $(CXXFLAGS) -c $^ -I$(MAIN_INC)

# Clean up
clean:
	rm -f $(CUSTOMER_DIR)/*.o $(DELIVERY_DIR)/*.o $(SYSTEM_DIR)/src/*.o $(MAIN_OBJ) $(MAIN_BIN)

.PHONY: all clean
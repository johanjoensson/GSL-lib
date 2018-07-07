################################################################################
# Makefile for building an implementation of the ASW method (someday this might#
# actually be a "full" DFT code)                                               #
################################################################################
################################################################################
# Author: Johan Jönsson                                                        #
# Email: johanjoensson@gmail.com                                               #
# Created: 2018-01-31                                                          #
# Last updated: 2018-02-25                                                     #
################################################################################

# Compilers to use
#CXX = clang++
CXX = g++
#CC  = clang
CC  = gcc

CXXCHECK = clang-tidy

# Source files directory
SRC_DIR = src

# Build directory
BUILD_DIR = build

# Flags for the above defined compilers
CXXFLAGS = -g -std=c++11 -Wall -Wextra -Werror -W -pedantic -fPIC -I $(SRC_DIR)
CFLAGS = -g -std=c11 -Wall -Wextra -Werror -W -pedantic -fPIC -I $(SRC_DIR)

CXXCHECKS =clang-analyzer-*,-clang-analyzer-cplusplus*,cppcoreguidelines-*,bugprone-* 
CXXCHECKFLAGS = -checks=$(CXXCHECKS) -header-filter=.* -- -std=c++11

# Libraries to link against
LDFLAGS = -lgsl -lgslcblas -lm -shared

# List of all executables in this project
LIB = libgsl-lib.so

LIB_OBJ = complex.o\
	  vector.o\
	  special_functions_bessel.o

OBJS = $(addprefix $(BUILD_DIR)/, $(LIB_OBJ))

# Targets to always execute, even if new files with the same names exists
.PHONY: all clean cleanall

# Build all executables
all: $(LIB)

# Create object files from c++ sources
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $? -o $@

# Create object files from c sources
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $? -o $@

# Link numerov_test
libgsl-lib.so: $(OBJS)
	$(CXX) $(LDFLAGS) $? -o $@

test: $(BUILD_DIR)/main.o libgsl-lib.so
	$(CXX)  -L./ -lgsl-lib -Wl,-rpath=. $< -o $@

checkall: $(addprefix $(SRC_DIR)/, $(OBJ:o=cpp))
	$(CXXCHECK) $^ $(CXXCHECKFLAGS) 

# Remove object files
clean:
	rm -f $(BUILD_DIR)/*.o

# Remove executables and object files
cleanall:
	rm -f $(LIB) test $(BUILD_DIR)/*.o

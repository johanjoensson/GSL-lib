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
CXX ?= g++
#CC  = clang
CC  ?= gcc

CXXCHECK = clang-tidy

# List of all executables in this project
LIB = GSLpp
# Source files directory
SRC_DIR = src
TEST_DIR = test

# Build directory
BUILD_DIR = build

# Library directory
LIB_DIR = lib

# include directory
INC_DIR = include

# Flags for the above defined compilers

WFLAGS = -Werror -Wall -Wextra -pedantic -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion -Wsign-conversion -Wnull-dereference -Wdouble-promotion -Wformat=2 -Weffc++
# -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op  -Wuseless-cast
CXXFLAGS = -std=c++11 $(WFLAGS) -I $(INC_DIR) -DHAVE_INLINE -DGSL_RANGE_CHECK_OFF -O3

CXXCHECKS =clang-analyzer-*,-clang-analyzer-cplusplus*,cppcoreguidelines-*,bugprone-* 
CXXCHECKFLAGS = -checks=$(CXXCHECKS) -header-filter=.* -- -std=c++11

# Libraries to link against
LDFLAGS =-lgsl -lopenblas -shared -Wl,-soname,lib$(LIB).so


LIB_OBJ = divided_difference.o\
	  permutation.o\
	  eigen.o\
	  linalg.o\
	  basic_math.o\
	  special_functions_bessel.o\
	  special_functions_legendre.o\
	  special_functions_coupling.o\
	  special_functions_exp.o\
	  special_functions_log.o\
	  special_functions_trig.o\
	  special_functions_erf.o\
	  special_functions_results.o\
	  error.o

TEST_OBJ =  main_tests.o\
 	    complex_test.o\

OBJS = $(addprefix $(BUILD_DIR)/, $(LIB_OBJ))
TEST_OBJS = $(addprefix $(BUILD_DIR)/, $(TEST_OBJ))

# Targets to always execute, even if new files with the same names exists
.PHONY: clean cleanall $(LIB_DIR) $(INC_DIR)

# Build all executables
all: $(LIB_DIR) $(INC_DIR) lib$(LIB).so $(TEST)

# Create object files from c++ sources
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -fPIC -c $? -o $@

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -fPIC -c $? -o $@

# Link numerov_test
lib$(LIB).so: $(OBJS)
	$(CXX) $^ -o $(LIB_DIR)/$(LIB)/$@ $(LDFLAGS)

lib$(LIB)cov.so: $(OBJS)
	$(CXX) $^ -o $(LIB_DIR)/$(LIB)/$@ $(LDFLAGS)

tester: $(BUILD_DIR)/main.o lib$(LIB).so
	$(CXX) $< -o $@ -L$(LIB_DIR)/$(LIB) -l$(LIB) -lgsl -Wl,-rpath=$(LIB_DIR)/$(LIB)

checkall: $(addprefix $(SRC_DIR)/, $(LIB_OBJ:o=cpp))
	$(CXXCHECK) $^ $(CXXCHECKFLAGS) 


tests: 	CXXFLAGS = -std=c++11 -I$(INC_DIR) -O0 -fprofile-arcs -ftest-coverage
tests:  LDFLAGS = -lgcov --coverage -lgsl -lopenblas -shared -Wl,-soname,lib$(LIB)cov.so
tests: 	clean $(TEST_OBJS) | lib$(LIB)cov.so
	$(CXX) $(TEST_OBJS) -o $@ -L$(LIB_DIR)/$(LIB) -lgtest -l$(LIB)cov -lgcov --coverage -lgsl -lgslcblas -lopenblas -Wl,-rpath=$(LIB_DIR)/$(LIB)


travis: CXXFLAGS = -std=c++11 -I$(INC_DIR) -O0
travis: $(BUILD_DIR) $(LIB_DIR) $(INC_DIR) lib$(LIB).so

$(BUILD_DIR) : 
	mkdir -p $(BUILD_DIR)

$(LIB_DIR) : 
	mkdir -p $(LIB_DIR)/$(LIB)

$(INC_DIR) : 
	mkdir -p $(INC_DIR)/$(LIB)
	cp $(SRC_DIR)/*.h $(INC_DIR)/$(LIB)
	cp $(SRC_DIR)/*.tpp $(INC_DIR)/$(LIB)

# Remove object files
clean:
	rm -f $(BUILD_DIR)/*.o $(BUILD_DIR)/*.gcda $(BUILD_DIR)/*.gcno

# Remove executables and object files
cleanall: clean
	rm -f $(LIB_DIR)/$(LIB)/lib$(LIB).so* $(LIB_DIR)/$(LIB)/lib$(LIB)cov.so* $(INC_DIR)/$(LIB)/*.h $(INC_DIR)/$(LIB)/*.tpp tests tester

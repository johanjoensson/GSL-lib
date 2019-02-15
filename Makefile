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
LIB_DIR = lib/GSLpp

# include directory
INC_DIR = include/GSLpp

# Flags for the above defined compilers

WFLAGS = -Werror -Wall -Wextra -pedantic -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion -Wsign-conversion -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wnull-dereference -Wuseless-cast -Wdouble-promotion -Wformat=2 -Weffc++

CXXFLAGS = -std=c++11 $(WFLAGS) -I $(INC_DIR) -DHAVE_INLINE -DGSL_RANGE_CHECK_OFF -O0 -g

CXXCHECKS =clang-analyzer-*,-clang-analyzer-cplusplus*,cppcoreguidelines-*,bugprone-* 
CXXCHECKFLAGS = -checks=$(CXXCHECKS) -header-filter=.* -- -std=c++11

# Libraries to link against
LDFLAGS =-lgsl -lopenblas_seq_lp64 -shared -Wl,-soname,lib$(LIB).so -L/software/sse/manual/OpenBLAS/0.3.4_skx/g73/lib/


LIB_OBJ = divided_difference.o\
	  complex.o\
	  vector.o\
	  matrix.o\
	  complex_vector.o\
	  complex_matrix.o\
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
.PHONY: all clean cleanall bin $(LIB_DIR) $(INC_DIR)

# Build all executables
all: bin $(LIB_DIR) $(INC_DIR) lib$(LIB).so $(TEST)

# Create object files from c++ sources
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -fPIC -c $? -o $@

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $? -o $@

# Create object files from c sources
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -fPIC -c $? -o $@

# Link numerov_test
lib$(LIB).so: $(OBJS)
	$(CXX) $^ -o $(LIB_DIR)/$@ $(LDFLAGS)

lib$(LIB)cov.so: $(OBJS)
	$(CXX) $^ -o $(LIB_DIR)/$@ $(LDFLAGS)

tester:   $(BUILD_DIR)/main.o | lib$(LIB).so
	$(CXX) $< -o $@ -L$(LIB_DIR) -l$(LIB) -lgsl -Wl,-rpath=$(LIB_DIR)

checkall: $(addprefix $(SRC_DIR)/, $(LIB_OBJ:o=cpp))
	$(CXXCHECK) $^ $(CXXCHECKFLAGS) 


tests: 	CXXFLAGS = -std=c++11 -I$(SRC_DIR) -I$(TEST_DIR) -O0 -fprofile-arcs -ftest-coverage
tests:  LDFLAGS = -lgcov -lgsl -lopenblas -shared -Wl,-soname,lib$(LIB)cov.so
tests: 	clean $(TEST_OBJS) | lib$(LIB)cov.so
	$(CXX) $(TEST_OBJS) -o $@ -L$(LIB_DIR) -l$(LIB)cov -lgcov -lgtest -Wl,-rpath=$(LIB_DIR)


travis: CXXFLAGS = -std=c++11 -I$(SRC_DIR) -O0
travis: $(BUILD_DIR) $(LIB_DIR) $(INC_DIR) lib$(LIB).so

$(BUILD_DIR) : 
	mkdir -p $(BUILD_DIR)

$(LIB_DIR) : 
	mkdir -p $(LIB_DIR)

$(INC_DIR) : 
	mkdir -p $(INC_DIR)
	cp $(SRC_DIR)/*.h $(INC_DIR)

# Remove object files
clean:
	rm -f $(BUILD_DIR)/*.o

# Remove executables and object files
cleanall:
	rm -f $(LIB_DIR)/lib$(LIB).so* $(INC_DIR)/*.h tests tester $(BUILD_DIR)/*.o

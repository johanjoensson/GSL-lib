################################################################################
# Makefile for building an implementation of the ASW method (someday this might#
# actually be a "full" DFT code)                                               #
################################################################################
################################################################################
# Author: Johan Jönsson                                                        #
# Email: johanjoensson@gmail.com                                               #
# Created: 2018-01-31                                                          #
# Last updated: 2019-07-08                                                     #
################################################################################

CXXCHECK = clang-tidy

# List of all executables in this project
LIB = GSLpp
# Source files directory
SRC_DIR = src
TEST_DIR = tests

# Build directory
BUILD_DIR = build

# Library directory
LIB_DIR = lib

# include directory
INC_DIR = include

# Flags for the above defined compilers

WFLAGS = -Werror -Wall -Wextra -pedantic -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion -Wsign-conversion -Wnull-dereference -Wdouble-promotion -Wformat=2 -Weffc++ -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op  -Wuseless-cast
#CXXFLAGS = -std=c++11 $(WFLAGS) -I $(INC_DIR) -DHAVE_INLINE -DGSL_RANGE_CHECK_OFF -fPIC -g -pg -O3 -flto
CXXFLAGS = -std=c++11 $(WFLAGS) -I$(SRC_DIR) -DHAVE_INLINE -DGSL_RANGE_CHECK_OFF -fPIC -O0 -flto -DDEBUG -g

CXXCHECKS =clang-analyzer-*,-clang-analyzer-cplusplus*,cppcoreguidelines-*,bugprone-*
CXXCHECKFLAGS = -checks=$(CXXCHECKS) -header-filter=.* -- -std=c++11

# Libraries to link against
LDFLAGS = -lgsl -lopenblas -fPIC -Ofast -fuse-ld=gold -flto


LIB_OBJ = complex_impl.o\
	  matrix_impl.o\
	  vector_impl.o\
	  divided_difference.o\
	  permutation.o\
	  eigen.o\
	  linalg.o\
	  basic_math.o\
	  special_functions_bessel.o\
	  special_functions_legendre.o\
	  special_functions_laguerre.o\
	  special_functions_hermite.o\
	  special_functions_coupling.o\
	  special_functions_exp.o\
	  special_functions_log.o\
	  special_functions_trig.o\
	  special_functions_erf.o\
	  special_functions_gamma_beta.o\
	  special_functions_results.o\
	  interp.o\
	  ode.o\
	  error.o

TEST_OBJ =  main_tests.o\
 	    complex_test.o\
	    complex_base_math_test.o\
 	    complex_ld_test.o\
	    complex_ld_base_math_test.o\
 	    complex_f_test.o\
	    complex_f_base_math_test.o\
	    vector_test.o\
	    vector_c_test.o\
	    vector_uc_test.o\
	    vector_f_test.o\
	    vector_ld_test.o\
	    vector_i_test.o\
	    vector_ui_test.o\
	    vector_l_test.o\
	    vector_ul_test.o\
	    vector_s_test.o\
	    vector_us_test.o\
	    vector_cx_test.o\
	    vector_cxf_test.o\
	    vector_cxld_test.o\
	    matrix_test.o\
	    matrix_f_test.o\
	    matrix_ld_test.o\
	    matrix_c_test.o\
	    matrix_uc_test.o\
	    matrix_s_test.o\
	    matrix_us_test.o\
	    matrix_i_test.o\
	    matrix_ui_test.o\
	    matrix_cx_test.o\
	    matrix_cxf_test.o\
	    matrix_cxld_test.o\
	    interp_test.o\
	    ode_test.o\

OBJS = $(addprefix $(BUILD_DIR)/, $(LIB_OBJ))
TEST_OBJS = $(addprefix $(BUILD_DIR)/, $(TEST_OBJ))

# Targets to always execute, even if new files with the same names exists
.PHONY: clean cleanall $(LIB_DIR) $(INC_DIR)

# Build all executables
all: $(LIB_DIR) $(INC_DIR) $(BUILD_DIR) lib$(LIB).so $(TEST)

# Create object files from c++ sources
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $? -o $@

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $? -o $@

lib$(LIB).so: $(OBJS)
	$(CXX) $^ -o $(LIB_DIR)/$(LIB)/$@ $(LDFLAGS) -shared -Wl,-soname,$@
	cp $(SRC_DIR)/$(LIB)/*.h $(INC_DIR)/$(LIB)

lib$(LIB)cov.so: $(OBJS)
	$(CXX) $^ -o $(LIB_DIR)/$(LIB)/$@ $(LDFLAGS) -shared -Wl,-soname,$@

checkall: $(addprefix $(SRC_DIR)/, $(LIB_OBJ:o=cpp))
	$(CXXCHECK) $^ $(CXXCHECKFLAGS)


test:  CXXFLAGS += --coverage
test:  LDFLAGS += --coverage -lgtest
test:  lib$(LIB)cov.so
test: 	$(INC_DIR) $(BUILD_DIR) $(LIB_DIR) $(TEST_OBJS)
	$(CXX) $(TEST_OBJS) -o $@ -L $(LIB_DIR)/$(LIB) -Wl,-rpath=$(LIB_DIR)/$(LIB) -l$(LIB)cov $(LDFLAGS)

travis : -std=c++11 -I $(SRC_DIR) -DHAVE_INLINE -DGSL_RANGE_CHECK_OFF -Ofast -flto -fPIC
travis: $(BUILD_DIR) $(LIB_DIR) $(INC_DIR) lib$(LIB).so

$(BUILD_DIR) :
	mkdir -p $(BUILD_DIR)

$(LIB_DIR) :
	mkdir -p $(LIB_DIR)/$(LIB)

$(INC_DIR) :
	mkdir -p $(INC_DIR)/$(LIB)
#	cp $(SRC_DIR)/$(LIB)/*.h $(INC_DIR)/$(LIB)

# Remove object files
clean:
	rm -f $(BUILD_DIR)/*.o $(BUILD_DIR)/*.gcda $(BUILD_DIR)/*.gcno

# Remove executables and object files
cleanall: clean
	rm -f $(LIB_DIR)/$(LIB)/lib$(LIB).so* $(LIB_DIR)/$(LIB)/lib$(LIB)cov.so* $(INC_DIR)/$(LIB)/*.h $(INC_DIR)/$(LIB)/*.tpp test tester

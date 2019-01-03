cmake_minimum_required(VERSION 3.0)

project(GSLpp)

set(WFLAGS " -Werror -Wall -Wextra -pedantic -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion -Wsign-conversion -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wnull-dereference -Wuseless-cast -Wdouble-promotion -Wformat=2 -Weffc++")

set(CXXFLAGS  "-g -std=c++11 ${WFLAGS} -DDEBUG")
set(CFLAGS  "-g -std=c11 ${WFLAGS} -DDEBUG")

set(SOURCE_FILES   src/divided_difference.cpp
		   src/complex.cpp 
                   src/vector.cpp 
                   src/complex_vector.cpp 
		   src/permutation.cpp
                   src/matrix.cpp
                   src/complex_matrix.cpp 
		   src/eigen.cpp
		   src/linalg.cpp
                   src/basic_math.cpp 
                   src/special_functions_results.cpp 
                   src/special_functions_bessel.cpp 
                   src/special_functions_legendre.cpp 
                   src/special_functions_coupling.cpp
                   src/special_functions_exp.cpp 
                   src/special_functions_log.cpp
                   src/special_functions_trig.cpp 
                   src/special_functions_erf.cpp
		   src/error.cpp)

	    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXXFLAGS}")
	    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CFLAGS}")

add_library(GSLpp SHARED ${SOURCE_FILES})
target_link_libraries(GSLpp gsl openblas m)

add_executable(test src/main.cpp)
target_link_libraries(test GSLpp)


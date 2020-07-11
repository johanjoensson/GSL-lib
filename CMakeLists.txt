cmake_minimum_required(VERSION 3.9)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT DEFINED CMAKE_BUILD_TYPE)
	message(STATUS "CMAKE_BUILD_TYPE not set by user, setting to Release")
	set(CMAKE_BUILD_TYPE "Release")
endif()

message(STATUS "CMAKE_BUILD_TYPE : ${CMAKE_BUILD_TYPE}")

project(GSLpp CXX)
find_package(GSL REQUIRED)
include_directories(${GSL_INCLUDE_DIRS})

set(WFLAGS " -Werror -Wall -Wextra -pedantic -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion -Wsign-conversion -Wmisleading-indentation -Wnull-dereference -Wdouble-promotion -Wformat=2 -Weffc++")
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	set(WFLAGS "${WFLAGS} -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wuseless-cast")
endif()

set(CMAKE_CXX_FLAGS ${WFLAGS})
set(CMAKE_CXX_FLAGS_RELEASE "-Ofast")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")


set(SOURCE_FILES	src/complex_impl.cpp
	  				src/matrix_impl.cpp
	  				src/vector_impl.cpp
	  				src/divided_difference.cpp
	  				src/permutation.cpp
	  				src/eigen.cpp
	  				src/linalg.cpp
	  				src/basic_math.cpp
	  				src/special_functions_bessel.cpp
	  				src/special_functions_legendre.cpp
	  				src/special_functions_laguerre.cpp
	  				src/special_functions_hermite.cpp
	  				src/special_functions_coupling.cpp
	  				src/special_functions_exp.cpp
	  				src/special_functions_log.cpp
	  				src/special_functions_trig.cpp
	  				src/special_functions_erf.cpp
	  				src/special_functions_gamma_beta.cpp
	  				src/special_functions_results.cpp
	  				src/interp.cpp
	  				src/ode.cpp
	  				src/error.cpp)

set(TEST_FILES 	tests/matrix_cx_test.cpp
				tests/vector_cx_test.cpp
				tests/complex_base_math_test.cpp
				tests/matrix_f_test.cpp
				tests/vector_f_test.cpp
				tests/complex_f_base_math_test.cpp
				tests/matrix_i_test.cpp
				tests/vector_i_test.cpp
				tests/complex_f_test.cpp
				tests/matrix_ld_test.cpp
				tests/vector_ld_test.cpp
				tests/complex_ld_base_math_test.cpp
				tests/matrix_s_test.cpp
				tests/vector_l_test.cpp
				tests/complex_ld_test.cpp
				tests/matrix_test.cpp
				tests/vector_s_test.cpp
				tests/complex_test.cpp
				tests/matrix_uc_test.cpp
				tests/vector_test.cpp
				tests/interp_test.cpp
				tests/matrix_ui_test.cpp
				tests/vector_uc_test.cpp
				tests/main_tests.cpp
				tests/matrix_us_test.cpp
				tests/vector_ui_test.cpp
				tests/matrix_c_test.cpp
				tests/vector_c_test.cpp
				tests/vector_ul_test.cpp
				tests/matrix_cxf_test.cpp
				tests/vector_cxf_test.cpp
				tests/vector_us_test.cpp
				tests/matrix_cxld_test.cpp
				tests/vector_cxld_test.cpp
				tests/main_tests.cpp
				)

add_library(GSLpp SHARED ${SOURCE_FILES})
target_include_directories(GSLpp PUBLIC src)
target_link_libraries(GSLpp ${GSL_LIBRARIES} openblas m)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
	include(CheckIPOSupported)
	check_ipo_supported(RESULT result)
	if(result)
		set_property(TARGET GSLpp PROPERTY INTERPROCEDURAL_OPTIMIZATION True)
	endif()
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
	enable_testing()
	find_package(GTest REQUIRED)
	include_directories(${GTEST_INCLUDE_DIRS})
	add_executable(GSLppUnitTest ${TEST_FILES})
	target_link_libraries(GSLppUnitTest GSLpp ${GTEST_LIBRARIES})
	GTEST_ADD_TESTS(GSLppUnitTest "" ${TEST_FILES})
	message(STATUS "CXX flags : ${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG}")
endif()

install(TARGETS GSLpp
		LIBRARY DESTINATION lib/GSLpp)
install(DIRECTORY src/GSLpp DESTINATION include)


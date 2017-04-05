cmake_minimum_required(VERSION 2.8.11)
project(testcpuinfo)

enable_testing()

# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)

# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(${CMAKE_SOURCE_DIR}/../../src)

find_package(Qt5Test REQUIRED)

SET(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
SET(CMAKE_C_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")


add_executable(testcpuinfo testcpuinfo.cpp ${CMAKE_SOURCE_DIR}/../../src/cpuinfo.cpp)
add_test(testcpuinfo testcpuinfo)

target_link_libraries(testcpuinfo Qt5::Test)

INCLUDE(CodeCoverage.cmake)

SETUP_TARGET_FOR_COVERAGE(
			test_with_coverage  # Name for custom target.
			testcpuinfo         # Name of the test driver executable that runs the tests.
			# NOTE! This should always have a ZERO as exit code
			# otherwise the coverage generation will not complete.
			coverage            # Name of output directory.
			)

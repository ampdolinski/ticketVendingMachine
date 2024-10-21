cmake_minimum_required(VERSION 3.10)
project(ticketVendingMachine)

set(CMAKE_CXX_STANDARD 20)

# Enable gcov coverage
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} --coverage")

# Set CMake Prefix Path to where GTest is installed
set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/test/external/googletest/googletest/googletest")

# Add include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Find GTest
set(GTEST_LIBRARY "${CMAKE_SOURCE_DIR}/test/external/googletest/googletest/googletest/libgtest.a")
set(GTEST_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/test/external/googletest/googletest/googletest/include")
set(GTEST_MAIN_LIBRARY "${CMAKE_SOURCE_DIR}/test/external/googletest/googletest/googletest/libgtest_main.a")

find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIR})

# Add source directories
add_subdirectory(src)

# # Add test directories
# enable_testing()
# add_subdirectory(test)

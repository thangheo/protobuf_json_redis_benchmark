cmake_minimum_required(VERSION 3.12)
project(redis_test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# <------------ add hiredis dependency --------------->
find_path(HIREDIS_HEADER hiredis)
find_library(HIREDIS_LIB hiredis)
find_library(REDIS_PLUS_PLUS_LIB redis++)

# Locate and include Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add your project source files and include directories
# ...

# Add the executable for your unit tests
add_executable(redis_test
    test1.cpp
)


# <------------ add redis-plus-plus dependency -------------->
# NOTE: this should be *sw* NOT *redis++*
find_path(REDIS_PLUS_PLUS_HEADER sw)
target_include_directories(redis_test PUBLIC ${REDIS_PLUS_PLUS_HEADER})



target_include_directories(redis_test PUBLIC ${HIREDIS_HEADER})

# Link against the Google Test library
target_link_libraries(redis_test PRIVATE gtest ${HIREDIS_LIB} ${REDIS_PLUS_PLUS_LIB})

# Set the C++ standard
target_compile_features(redis_test PRIVATE cxx_std_17)

# Enable testing with CTest
enable_testing()

# Add a test for running the unit tests
add_test(NAME redis_test COMMAND redis_test)

cmake_minimum_required(VERSION 3.12)
project(DS)

set(CMAKE_CXX_STANDARD 17)
set(RAPIDJSON_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/../../Libs/rapidjson/include)
include_directories(${RAPIDJSON_INCLUDE_DIR})

# Locate and include Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
# <------------ add hiredis dependency --------------->
find_path(HIREDIS_HEADER hiredis)
find_library(HIREDIS_LIB hiredis)
find_library(REDIS_PLUS_PLUS_LIB redis++)
find_package(Protobuf REQUIRED)
INCLUDE_DIRECTORIES(${Protobuf_INCLUDE_DIRS})

# Add your project source files and include directories
# ...

# Add the executable for your unit tests
add_executable(RedisDBTest
    RedisDBTest.cpp
    ../src/RedisDatabase.cpp
)
add_executable(DataStorageAppTest
    DataStorageAppTest.cpp
    ../src/RedisDatabase.cpp
    ../src/DataStorage_protobuf.cpp
    ../src/protobuf/DataStorage.pb.cc
)
add_executable(JsonDataStorageTest
    DataStorageApp_jsonTest.cpp
    ../src/RedisDatabase.cpp
    ../src/DataStorage_json.cpp
)
target_include_directories(DataStorageAppTest PRIVATE ${RAPIDJSON_INCLUDE_DIR})
target_include_directories(JsonDataStorageTest PRIVATE ${RAPIDJSON_INCLUDE_DIR})

# Link against the Google Test library and hiredis & redis++
target_link_libraries(RedisDBTest PRIVATE gtest ${HIREDIS_LIB} ${REDIS_PLUS_PLUS_LIB})
target_link_libraries(DataStorageAppTest PRIVATE gtest ${HIREDIS_LIB} ${REDIS_PLUS_PLUS_LIB} ${Protobuf_LIBRARIES})
target_link_libraries(JsonDataStorageTest PRIVATE gtest ${HIREDIS_LIB} ${REDIS_PLUS_PLUS_LIB})

# Set the C++ standard
target_compile_features(RedisDBTest PRIVATE cxx_std_17)
target_compile_features(DataStorageAppTest PRIVATE cxx_std_17)
target_compile_features(JsonDataStorageTest PRIVATE cxx_std_17)

# Enable testing with CTest
enable_testing()

# Add a test for running the unit tests
add_test(NAME InMemoryDbTests COMMAND RedisDBTest)
add_test(NAME DataStorageDSTests COMMAND DataStorageAppTest)
add_test(NAME JsonDataStorageTests COMMAND JsonDataStorageTest)

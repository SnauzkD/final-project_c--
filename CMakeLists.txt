cmake_minimum_required(VERSION 3.14)
project(FinalProject)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(external/googletest)

add_executable(FinalProject main.cpp
        converterJson.cpp
        converterJson.h
        InvertedIndex.cpp
        InvertedIndex.h
)
add_executable(FinalProject_tests
        test.cpp
        InvertedIndex.cpp
)

target_link_libraries(FinalProject_tests gtest_main)
enable_testing()
include(GoogleTest)
gtest_discover_tests(FinalProject_tests)

target_include_directories(FinalProject_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(FinalProject PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

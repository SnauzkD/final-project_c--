cmake_minimum_required(VERSION 3.10)
project(FinalProject)

set(CMAKE_CXX_STANDARD 20)

add_executable(FinalProject main.cpp)

target_include_directories(FinalProject PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

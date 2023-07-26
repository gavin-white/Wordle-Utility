cmake_minimum_required(VERSION 3.10)
project(wordle-utility)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3")

include_directories(include)

# recursively collect all source files from the src directory
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(wordle-utility ${SOURCES})

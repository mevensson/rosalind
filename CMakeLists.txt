cmake_minimum_required(VERSION 3.9)
project(rosalind)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_CLANG_TIDY "clang-tidy")

find_package(Boost COMPONENTS program_options REQUIRED)
find_package(Threads)

enable_testing()

add_subdirectory(lib/catch2)

add_subdirectory(src/options)

add_subdirectory(src/dna)

add_subdirectory(src/main)

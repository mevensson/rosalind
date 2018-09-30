cmake_minimum_required(VERSION 3.9)
project(rosalind)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost COMPONENTS program_options iostreams REQUIRED)
find_package(Threads)

include(CTest)
enable_testing()

add_subdirectory(lib/catch2)

add_subdirectory(src/options)

add_subdirectory(src/dna)
add_subdirectory(src/rna)
add_subdirectory(src/revc)

add_subdirectory(src/main)

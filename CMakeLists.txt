cmake_minimum_required(VERSION 3.9)
project(rosalind)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.65 COMPONENTS program_options REQUIRED)

enable_testing()
add_subdirectory(dna)

add_library(
        dna_lib
        dna.cpp
        dna.hpp
)

target_include_directories(
        dna_lib
        PUBLIC .
)

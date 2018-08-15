add_library(
        dna_lib
        dna.cpp
        dna.hpp
)

target_include_directories(
        dna_lib
        INTERFACE .
)

add_executable(
        dna
        main.cpp
)

target_link_libraries(
        dna
        dna_lib
        Boost::program_options
)
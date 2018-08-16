add_executable(
        rosalind
        main.cpp
)

target_link_libraries(
        rosalind
        dna_lib
        Boost::program_options
        Threads::Threads
)

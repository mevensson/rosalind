add_executable(
        rosalind
        src/main.cpp
)

target_link_libraries(
        rosalind
        options_lib
        dna_lib
        rna_lib
        revc_lib
        subs_lib
        Boost::iostreams
)

install(TARGETS rosalind DESTINATION bin)

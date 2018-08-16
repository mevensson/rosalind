add_library(
        dna_lib
        src/dna.cpp
        include/dna.hpp
)

target_include_directories(
        dna_lib
        PUBLIC include
        PRIVATE src
)

target_link_libraries(
        dna_lib
        Threads::Threads
)

# Unit tests
add_executable(
        dna_test
        test/dna_test.cpp)

target_link_libraries(
        dna_test
        dna_lib
        catch2_lib
)

add_test(NAME DnaTest COMMAND dna_test)

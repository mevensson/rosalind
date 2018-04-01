add_executable(
        dna_test
        main_test.cpp
        catch.hpp
        dna_test.cpp)

target_link_libraries(
        dna_test
        dna_lib
)

add_test(NAME DnaTest COMMAND dna_test)
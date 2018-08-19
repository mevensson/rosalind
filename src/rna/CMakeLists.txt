add_library(
        rna_lib
        src/rna.cpp
        include/rna.hpp
)

target_include_directories(
        rna_lib
        PUBLIC include
        PRIVATE src
)

target_link_libraries(
        rna_lib
        Threads::Threads
)

# Unit tests
add_executable(
        rna_test
        test/rna_test.cpp)

target_link_libraries(
        rna_test
        rna_lib
        catch2_lib
)

add_test(NAME RnaTest COMMAND rna_test)

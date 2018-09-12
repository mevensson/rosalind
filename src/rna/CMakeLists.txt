add_library(rna_lib INTERFACE)

target_include_directories(
        rna_lib
        INTERFACE include
)

target_sources(
        dna_lib
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include/rna.hpp
)

target_link_libraries(
        rna_lib
        INTERFACE Threads::Threads
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

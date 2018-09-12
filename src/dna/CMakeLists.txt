add_library(dna_lib INTERFACE)

target_include_directories(
        dna_lib
        INTERFACE include
)

target_sources(
        dna_lib
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include/dna.hpp
)

target_link_libraries(
        dna_lib
        INTERFACE Threads::Threads
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

add_library(subs_lib INTERFACE)

target_include_directories(
        subs_lib
        INTERFACE include
)

target_sources(
        subs_lib
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include/subs.hpp
)

target_link_libraries(
        subs_lib
        INTERFACE Threads::Threads
)

# Unit tests
add_executable(
        subs_test
        test/subs_test.cpp)

target_link_libraries(
        subs_test
        subs_lib
        catch2_lib
)

add_test(NAME SubsTest COMMAND subs_test)

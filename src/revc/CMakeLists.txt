add_library(revc_lib INTERFACE)

target_include_directories(
        revc_lib
        INTERFACE include
)

target_sources(
        revc_lib
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include/revc.hpp
)

target_link_libraries(
        revc_lib
        INTERFACE Threads::Threads
)

# Unit tests
add_executable(
        revc_test
        test/revc_test.cpp)

target_link_libraries(
        revc_test
        revc_lib
        catch2_lib
)

add_test(NAME RevcTest COMMAND revc_test)

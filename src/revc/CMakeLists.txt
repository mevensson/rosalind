add_library(
        revc_lib
        src/revc.cpp
        include/revc.hpp
)

target_include_directories(
        revc_lib
        PUBLIC include
        PRIVATE src
)

target_link_libraries(
        revc_lib
        Threads::Threads
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

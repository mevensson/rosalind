project(catch2 VERSION 2.2.1)

add_library(
        catch2_lib
        src/main_test.cpp
)

target_include_directories(
        catch2_lib
        PUBLIC include
        PRIVATE src
)

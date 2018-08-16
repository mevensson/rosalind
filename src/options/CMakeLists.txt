add_library(
        options_lib
        src/options.cpp
        include/options.hpp
)

target_include_directories(
        options_lib
        PUBLIC include
        PRIVATE src
)

target_link_libraries(
        options_lib
        Boost::program_options
)

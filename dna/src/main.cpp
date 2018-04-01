#include "dna.hpp"

#include <iostream>

static std::string readAllInput()
{
    const std::istreambuf_iterator<char> begin(std::cin);
    const std::istreambuf_iterator<char> end;
    const std::string input(begin, end);
    return input;
}

int main()
{
    auto input = readAllInput();
    auto result = dna(input);
    std::cout << std::get<0>(result) << " "
              << std::get<1>(result) << " "
              << std::get<2>(result) << " "
              << std::get<3>(result) << "\n";

    return 0;
}

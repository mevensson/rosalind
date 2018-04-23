#include "dna.hpp"

#include <iostream>

static auto readAllInput()
{
    const std::istreambuf_iterator<char> begin(std::cin);
    const std::istreambuf_iterator<char> end;
    const std::string input(begin, end);
    return input;
}

int main()
{
    auto input = readAllInput();
    auto [a, c, g, t] = dna(input);
    std::cout << a << " " << c << " " << g << " " << t << "\n";

    return 0;
}

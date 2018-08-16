#include "dna.hpp"
#include "options.hpp"

#include <iostream>

static auto readAllInput()
{
    const std::istreambuf_iterator<char> begin(std::cin);
    const std::istreambuf_iterator<char> end;
    const std::string input(begin, end);
    return input;
}

int main(const int argc, const char* const argv[])
{
    auto options = parse_options(argc, argv);

    auto executionType = options.executionType();
    auto input = readAllInput();
    auto [a, c, g, t] = executionType.type() == ExecutionType::Type::Parallel
        ? dna_par(input, executionType.numThreads())
        : dna_ser(input);
    std::cout << a << " " << c << " " << g << " " << t << "\n";

    return 0;
}

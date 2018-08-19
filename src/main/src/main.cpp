#include "dna.hpp"
#include "options.hpp"
#include "rna.hpp"

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
    auto options = parseOptions(argc, argv);

    auto executionType = options.executionType();
    auto input = readAllInput();
    switch (options.problem())
    {
    case Problem::Dna:
    {
        auto [a, c, g, t] = // NOLINT
            executionType.type() == ExecutionType::Type::Parallel
            ? dna_par(input, executionType.numThreads())
            : dna_ser(input);
        std::cout << a << " " << c << " " << g << " " << t << "\n";
        break;
    }
    case Problem::Rna:
    {
        auto result = rna(input);
        std::cout << result << "\n";
        break;
    }
    }

    return 0;
}

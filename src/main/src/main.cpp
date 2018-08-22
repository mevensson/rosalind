#include "dna.hpp"
#include "options.hpp"
#include "revc.hpp"
#include "rna.hpp"

#include <iostream>

static auto readAllInput()
{
    const auto begin = std::istreambuf_iterator<char>{std::cin};
    const auto end = std::istreambuf_iterator<char>{};
    const auto input = std::string{begin, end};
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
        auto result = executionType.type() == ExecutionType::Type::Parallel
            ? rna_par(input, executionType.numThreads())
            : rna_ser(input);
        std::cout << result << "\n";
        break;
    }
    case Problem::Revc:
    {
        auto result = executionType.type() == ExecutionType::Type::Parallel
            ? revc_par(input, executionType.numThreads())
            : revc_ser(input);
        std::cout << result << "\n";
        break;
    }
    }

    return 0;
}

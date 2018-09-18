#include "dna.hpp"
#include "options.hpp"
#include "revc.hpp"
#include "rna.hpp"

#include <boost/iostreams/device/mapped_file.hpp>
#include <fstream>
#include <iostream>
#include <stdexcept>

using namespace boost::iostreams;

template<class SerFunc, class ParFunc>
static auto execute(
    const ExecutionType executionType,
    const SerFunc serial,
    const ParFunc parallel)
{
    switch (executionType.type())
    {
    case ExecutionType::Type::Serial:
        return serial();
    case ExecutionType::Type::Parallel:
        return parallel();
    default:
        throw std::domain_error("Unknown excution type");
    }
}

int main(const int argc, const char* const argv[])
{
    const auto options = parseOptions(argc, argv);

    const auto executionType = options.executionType();
    const auto mappedFile = mapped_file_source{options.filename()};
    const auto first = mappedFile.begin();
    const auto last = mappedFile.end();
    const auto numThreads = executionType.numThreads();
    switch (options.problem())
    {
    case Problem::Dna:
    {
        auto [a, c, g, t] = execute( // NOLINT
            executionType,
            [&]() { return dna_ser(first, last); },
            [&]() { return dna_par(first, last, numThreads); });
        std::cout << a << " " << c << " " << g << " " << t << "\n";
        break;
    }
    case Problem::Rna:
    {
        auto result = execute(
            executionType,
            [&]() { return rna_ser(first, last); },
            [&]() { return rna_par(first, last, numThreads); });
        std::cout << result << "\n";
        break;
    }
    case Problem::Revc:
    {
        auto result = execute(
            executionType,
            [&]() { return revc_ser(first, last); },
            [&]() { return revc_par(first, last, numThreads); });
        std::cout << result << "\n";
        break;
    }
    }

    return 0;
}

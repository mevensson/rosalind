#include "dna.hpp"
#include "options.hpp"
#include "revc.hpp"
#include "rna.hpp"

#include <boost/iostreams/device/mapped_file.hpp>
#include <fstream>
#include <iostream>

using namespace boost::iostreams;

int main(const int argc, const char* const argv[])
{
    const auto options = parseOptions(argc, argv);

    const auto executionType = options.executionType();
    const auto mappedFile = mapped_file_source{options.filename()};
    const auto first = mappedFile.begin();
    const auto last = mappedFile.end();
    switch (options.problem())
    {
    case Problem::Dna:
    {
        auto [a, c, g, t] = // NOLINT
            executionType.type() == ExecutionType::Type::Parallel
            ? dna_par(first, last, executionType.numThreads())
            : dna_ser(first, last);
        std::cout << a << " " << c << " " << g << " " << t << "\n";
        break;
    }
    case Problem::Rna:
    {
        auto result = executionType.type() == ExecutionType::Type::Parallel
            ? rna_par(first, last, executionType.numThreads())
            : rna_ser(first, last);
        std::cout << result << "\n";
        break;
    }
    case Problem::Revc:
    {
        auto result = executionType.type() == ExecutionType::Type::Parallel
            ? revc_par(first, last, executionType.numThreads())
            : revc_ser(first, last);
        std::cout << result << "\n";
        break;
    }
    }

    return 0;
}

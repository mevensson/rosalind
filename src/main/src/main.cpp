#include "dna.hpp"
#include "options.hpp"
#include "revc.hpp"
#include "rna.hpp"
#include "subs.hpp"

#include <boost/iostreams/device/mapped_file.hpp>
#include <fstream>
#include <iostream>
#include <stdexcept>

using namespace boost::iostreams;

template<class SerFunc, class ParFunc, class Iterator>
static auto execute(
    const ExecutionType executionType,
    const SerFunc serial,
    const ParFunc parallel,
    const Iterator first,
    const Iterator last)
{
    switch (executionType.type())
    {
    case ExecutionType::Type::Serial:
        return serial(first, last);
    case ExecutionType::Type::Parallel:
        return parallel(first, last, executionType.numThreads());
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
    switch (options.problem())
    {
    case Problem::Dna:
    {
        const auto ser = &dna_ser<decltype(first)>;
        const auto par = &dna_par<decltype(first)>;
        const auto [a, c, g, t] = // NOLINT
            execute(executionType, ser, par, first, last);
        std::cout << a << " " << c << " " << g << " " << t << "\n";
        break;
    }
    case Problem::Rna:
    {
        const auto ser = &rna_ser<decltype(first)>;
        const auto par = &rna_par<decltype(first)>;
        const auto result = execute(executionType, ser, par, first, last);
        std::cout << result << "\n";
        break;
    }
    case Problem::Revc:
    {
        const auto ser = &revc_ser<decltype(first)>;
        const auto par = &revc_par<decltype(first)>;
        const auto result = execute(executionType, ser, par, first, last);
        std::cout << result << "\n";
        break;
    }
    case Problem::Subs:
    {
        const auto ser = &subs_ser<decltype(first)>;
        const auto par = &subs_par<decltype(first)>;
        const auto result = execute(executionType, ser, par, first, last);
        for (const auto& i : result)
        {
            std::cout << i << " ";
        }
        break;
    }
    }

    return 0;
}

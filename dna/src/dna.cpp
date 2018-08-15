#include "dna.hpp"

#include <future>
#include <vector>

auto dna_ser(const std::string_view& symbols) -> DnaSymbolCount
{
    auto result = DnaSymbolCount{0, 0, 0, 0};

    for (auto&& symbol : symbols)
    {
        switch (symbol)
        {
        case 'A':
            result.a += 1;
            break;
        case 'C':
            result.c += 1;
            break;
        case 'G':
            result.g += 1;
            break;
        case 'T':
            result.t += 1;
            break;
        }
    }

    return result;
}

auto dna_par(const std::string_view& symbols, const int nthreads)
    -> DnaSymbolCount
{
    const auto threadSize = (symbols.size() - 1) / nthreads + 1; // Round up
    auto futures = std::vector<std::future<DnaSymbolCount>>{};
    for (auto i = 0; i < nthreads; ++i)
    {
        const auto threadStart = i * threadSize;
        const auto threadSymbols = symbols.substr(threadStart, threadSize);
        futures.emplace_back(std::async(dna_ser, threadSymbols));
    }

    auto result = DnaSymbolCount{0, 0, 0, 0};
    for (auto& future : futures)
    {
        const auto& newResult = future.get();
        result.a += newResult.a;
        result.c += newResult.c;
        result.g += newResult.g;
        result.t += newResult.t;
    }
    return result;
}

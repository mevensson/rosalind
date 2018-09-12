#include "dna.hpp"

#include <future>
#include <vector>

auto dna_par(const std::string_view& symbols, const int nthreads)
    -> DnaSymbolCount
{
    const auto threadSize = (symbols.size() - 1) / nthreads + 1; // Round up
    auto futures = std::vector<std::future<DnaSymbolCount>>{};
    for (auto i = 0; i < nthreads; ++i)
    {
        const auto threadStart = i * threadSize;
        const auto threadSymbols = symbols.substr(threadStart, threadSize);
        futures.emplace_back(std::async(
            [](const auto& first, const auto& last) {
                return dna_ser(first, last);
            },
            threadSymbols.begin(),
            threadSymbols.end()));
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

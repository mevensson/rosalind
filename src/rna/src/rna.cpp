#include "rna.hpp"

#include <future>
#include <string>
#include <vector>

auto rna_par(const std::string_view& symbols, const int nthreads) -> std::string
{
    auto result = std::string{};
    result.resize(symbols.size());

    const auto threadSize = (symbols.size() - 1) / nthreads + 1; // Round up
    auto futures = std::vector<std::future<void>>{};
    for (auto i = 0; i < nthreads; ++i)
    {
        const auto threadStart = i * threadSize;
        const auto threadSymbols = symbols.substr(threadStart, threadSize);
        auto threadResultStart = result.begin() + threadStart;
        futures.emplace_back(std::async([threadSymbols, threadResultStart] {
            rna(threadSymbols.begin(), threadSymbols.end(), threadResultStart);
        }));
    }

    for (auto& future : futures)
    {
        future.wait();
    }
    return result;
}

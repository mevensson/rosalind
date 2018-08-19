#include "rna.hpp"

#include <algorithm>
#include <future>
#include <string>
#include <vector>

auto rna_ser(const std::string_view& symbols) -> std::string
{
    auto result = std::string{};
    result.resize(symbols.size());
    std::replace_copy(symbols.begin(), symbols.end(), result.begin(), 'T', 'U');
    return result;
}

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
            std::replace_copy(
                threadSymbols.begin(),
                threadSymbols.end(),
                threadResultStart,
                'T',
                'U');
            return;
        }));
    }

    for (auto& future : futures)
    {
        future.wait();
    }
    return result;
}

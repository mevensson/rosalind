#include "rna.hpp"

#include <algorithm>
#include <future>
#include <string>
#include <vector>

template<class InputIt, class OutputIt>
auto rna(
    const InputIt inputBegin,
    const InputIt inputEnd,
    const OutputIt outputBegin)
{
    std::replace_copy(inputBegin, inputEnd, outputBegin, 'T', 'U');
}

auto rna_ser(const std::string_view& symbols) -> std::string
{
    auto result = std::string{};
    result.resize(symbols.size());
    rna(symbols.begin(), symbols.end(), result.begin());
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
            rna(threadSymbols.begin(), threadSymbols.end(), threadResultStart);
        }));
    }

    for (auto& future : futures)
    {
        future.wait();
    }
    return result;
}

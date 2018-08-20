#include "revc.hpp"

#include <algorithm>
#include <future>
#include <string>
#include <vector>

template<class InputIt, class OutputIt>
auto revc(
    const InputIt inputBegin,
    const InputIt inputEnd,
    const OutputIt outputBegin)
{
    std::transform(inputBegin, inputEnd, outputBegin, [](const auto& s) {
        switch (s)
        {
        case 'A':
            return 'T';
        case 'C':
            return 'G';
        case 'G':
            return 'C';
        case 'T':
            return 'A';
        default:
            return s;
        }
    });
    const auto inputSize = inputEnd - inputBegin;
    const auto outputEnd = outputBegin + inputSize;
    std::reverse(outputBegin, outputEnd);
}

auto revc_ser(const std::string_view& symbols) -> std::string
{
    auto result = std::string{};
    result.resize(symbols.size());
    revc(symbols.begin(), symbols.end(), result.begin());
    return result;
}

auto revc_par(const std::string_view& symbols, int nthreads) -> std::string
{
    auto result = std::string{};
    result.resize(symbols.size());

    const auto threadSize = (symbols.size() - 1) / nthreads + 1; // Round up
    auto futures = std::vector<std::future<void>>{};
    for (auto i = 0; i < nthreads; ++i)
    {
        const auto threadStart = i * threadSize;
        const auto threadSymbols = symbols.substr(threadStart, threadSize);
        auto threadResultStart =
            result.end() - threadStart - threadSymbols.size();
        futures.emplace_back(std::async([threadSymbols, threadResultStart] {
            revc(threadSymbols.begin(), threadSymbols.end(), threadResultStart);
        }));
    }

    for (auto& future : futures)
    {
        future.wait();
    }
    return result;
}

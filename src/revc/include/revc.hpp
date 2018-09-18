#ifndef ROSALIND_REVC_H
#define ROSALIND_REVC_H

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

template<class RandomIt>
auto revc_ser(const RandomIt first, const RandomIt last)
{
    auto result = std::string{};
    result.resize(last - first);
    revc(first, last, result.begin());
    return result;
}

template<class RandomIt>
auto revc_par(const RandomIt first, const RandomIt last, int nthreads)
{
    const auto size = last - first;
    auto result = std::string{};
    result.resize(size);

    const auto threadSize = (size - 1) / nthreads + 1; // Round up
    auto futures = std::vector<std::future<void>>{};
    for (auto i = 0; i < nthreads; ++i)
    {
        const auto threadFirst = first + i * threadSize;
        const auto threadLast = threadFirst + threadSize;
        auto threadResultFirst = result.end() - (i + 1) * threadSize;
        futures.emplace_back(std::async(
            [](const auto& first, const auto& last, const auto& out) {
                revc(first, last, out);
            },
            threadFirst,
            threadLast > last ? last : threadLast,
            threadResultFirst < result.begin() ? result.begin()
                                               : threadResultFirst));
    }

    for (auto& future : futures)
    {
        future.wait();
    }
    return result;
}
#endif // ROSALIND_REVC_H

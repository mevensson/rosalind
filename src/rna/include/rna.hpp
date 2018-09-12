#ifndef ROSALIND_RNA_H
#define ROSALIND_RNA_H

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

template<class RandomIt>
auto rna_ser(const RandomIt first, const RandomIt last)
{
    auto result = std::string{};
    result.resize(last - first);
    rna(first, last, result.begin());
    return result;
}

template<class RandomIt>
auto rna_par(const RandomIt first, const RandomIt last, const int nthreads)
{
    auto result = std::string{};
    const auto size = last - first;
    result.resize(size);

    const auto threadSize = (size - 1) / nthreads + 1; // Round up
    auto futures = std::vector<std::future<void>>{};
    for (auto i = 0; i < nthreads; ++i)
    {
        const auto threadFirst = first + i * threadSize;
        const auto threadLast = threadFirst + threadSize;
        auto threadResultFirst = result.begin() + i * threadSize;
        futures.emplace_back(std::async(
            [](const auto& first, const auto& last, const auto& out) {
                rna(first, last, out);
            },
            threadFirst,
            threadLast > last ? last : threadLast,
            threadResultFirst));
    }

    for (auto& future : futures)
    {
        future.wait();
    }
    return result;
}

#endif // ROSALIND_RNA_H

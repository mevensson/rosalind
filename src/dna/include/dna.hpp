#ifndef ROSALIND_DNA_H
#define ROSALIND_DNA_H

#include <future>
#include <numeric>
#include <string>
#include <vector>

struct DnaSymbolCount
{
    int a;
    int c;
    int g;
    int t;

    auto operator+(const char symbol) const
    {
        auto result = *this;
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
        default:
            throw std::domain_error("Invalid symbol");
        }
        return result;
    }
};

template<class InputIt>
auto dna_ser(const InputIt first, const InputIt last)
{
    const auto init = DnaSymbolCount{};
    return std::accumulate(
        first, last, init, [](const auto& a, const auto& b) { return a + b; });
}

template<class RandomIt>
auto dna_par(const RandomIt first, const RandomIt last, const int nthreads)
{
    const auto threadSize = (last - first - 1) / nthreads + 1; // Round up
    auto futures = std::vector<std::future<DnaSymbolCount>>{};
    for (auto i = 0; i < nthreads; ++i)
    {
        const auto threadFirst = first + i * threadSize;
        const auto threadLast = threadFirst + threadSize;
        futures.emplace_back(std::async(
            [](const auto& first, const auto& last) {
                return dna_ser(first, last);
            },
            threadFirst,
            threadLast > last ? last : threadLast));
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

#endif // ROSALIND_DNA_H

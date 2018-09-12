#ifndef ROSALIND_DNA_H
#define ROSALIND_DNA_H

#include <numeric>
#include <string>

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

auto dna_par(const std::string_view& symbols, const int nthreads)
    -> DnaSymbolCount;

#endif // ROSALIND_DNA_H

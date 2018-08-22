#ifndef ROSALIND_DNA_H
#define ROSALIND_DNA_H

#include <string>

struct DnaSymbolCount
{
    int a;
    int c;
    int g;
    int t;

    auto operator+(const char symbol) const;
};

auto dna_ser(const std::string_view& symbols) -> DnaSymbolCount;

auto dna_par(const std::string_view& symbols, const int nthreads)
    -> DnaSymbolCount;

#endif // ROSALIND_DNA_H

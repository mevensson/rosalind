#ifndef ROSALIND_DNA_H
#define ROSALIND_DNA_H

#include <string>
#include <tuple>

struct DnaSymbolCount
{
    int a;
    int c;
    int g;
    int t;
};

auto dna_ser(const std::string_view& symbols) -> DnaSymbolCount;

auto dna_par(const std::string_view& symbols, const int nthreads)
    -> DnaSymbolCount;

#endif // ROSALIND_DNA_H

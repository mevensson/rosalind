#ifndef ROSALIND_RNA_H
#define ROSALIND_RNA_H

#include <algorithm>
#include <string>

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

auto rna_par(const std::string_view& symbols, const int nthreads)
    -> std::string;

#endif // ROSALIND_RNA_H

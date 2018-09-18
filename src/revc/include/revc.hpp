#ifndef ROSALIND_REVC_H
#define ROSALIND_REVC_H

#include <algorithm>
#include <string>

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

auto revc_par(const std::string_view& symbols, int nthreads) -> std::string;

#endif // ROSALIND_REVC_H

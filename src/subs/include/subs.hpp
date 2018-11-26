#ifndef ROSALIND_SUBS_H
#define ROSALIND_SUBS_H

#include <algorithm>
#include <stdexcept>
#include <string>
#include <vector>

template<class RandomIt>
auto subs(const RandomIt first, const RandomIt last)
{
    auto inputLast = std::find(first, last, '\n');
    if (inputLast == last)
    {
        throw std::domain_error("missing newline");
    }
    auto subFirst = inputLast + 1;
    auto subLast = std::find(subFirst, last, '\n');

    auto result = std::vector<int>{};
    for (auto match = std::search(first, inputLast, subFirst, subLast);
         match != inputLast;
         match = std::search(match + 1, inputLast, subFirst, subLast))
    {
        result.push_back(match - first + 1);
    }

    return result;
}

#endif // ROSALIND_SUBS_H

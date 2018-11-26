#ifndef ROSALIND_SUBS_H
#define ROSALIND_SUBS_H

#include <algorithm>
#include <future>
#include <stdexcept>
#include <string>
#include <vector>

template<class RandomIt>
auto subs_split_input(const RandomIt first, const RandomIt last)
{
    auto inputFirst = first;
    auto inputLast = std::find(first, last, '\n');
    if (inputLast == last)
    {
        throw std::domain_error("missing newline");
    }

    auto subFirst = inputLast + 1;
    auto subLast = std::find(subFirst, last, '\n');

    return std::tuple{inputFirst, inputLast, subFirst, subLast};
}

template<class RandomIt>
auto subs(
    const RandomIt inputFirst,
    const RandomIt inputLast,
    const RandomIt subFirst,
    const RandomIt subLast)
{
    auto result = std::vector<int>{};
    for (auto match = std::search(inputFirst, inputLast, subFirst, subLast);
         match != inputLast;
         match = std::search(match + 1, inputLast, subFirst, subLast))
    {
        result.push_back(match - inputFirst + 1);
    }

    return result;
}

template<class RandomIt>
auto subs_ser(const RandomIt first, const RandomIt last)
{
    auto [inputFirst, inputLast, subFirst, subLast] =
        subs_split_input(first, last);

    return subs(inputFirst, inputLast, subFirst, subLast);
}

template<class RandomIt>
auto subs_par(const RandomIt first, const RandomIt last, const int nthreads)
{
    auto [inputFirst, inputLast, subFirst, subLast] =
        subs_split_input(first, last);

    const auto size = inputLast - inputFirst;
    const auto subSize = subLast - subFirst;
    const auto threadSize = (size - 1) / nthreads + 1; // Round up
    auto futures = std::vector<std::future<std::vector<int>>>{};
    for (auto i = 0; i < nthreads; ++i)
    {
        const auto threadFirst = inputFirst + i * threadSize;
        const auto threadLast = threadFirst + threadSize + subSize;
        futures.emplace_back(std::async(
            [](const auto& inputFirst,
               const auto& inputLast,
               const auto& subFirst,
               const auto& subLast) {
                return subs(inputFirst, inputLast, subFirst, subLast);
            },
            threadFirst,
            threadLast > inputLast ? inputLast : threadLast,
            subFirst,
            subLast));
    }

    auto result = std::vector<int>{};
    for (int i = 0; i < futures.size(); ++i)
    {
        const auto& newResult = futures[i].get();
        for (auto& item : newResult)
        {
            result.push_back(item + i * threadSize);
        }
    }
    return result;
}

#endif // ROSALIND_SUBS_H

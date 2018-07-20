#include "dna.hpp"

std::tuple<int, int, int, int> dna(const std::string& symbols)
{
    auto numA = 0;
    auto numC = 0;
    auto numG = 0;
    auto numT = 0;
    for (auto&& symbol : symbols)
    {
        switch (symbol)
        {
        case 'A':
            numA += 1;
            break;
        case 'C':
            numC += 1;
            break;
        case 'G':
            numG += 1;
            break;
        case 'T':
            numT += 1;
            break;
        }
    }

    return std::make_tuple(numA, numC, numG, numT);
}
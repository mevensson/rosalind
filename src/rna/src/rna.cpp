#include "rna.hpp"

#include <algorithm>
#include <string>

auto rna(const std::string_view& symbols) -> std::string
{
    auto result = std::string{};
    result.resize(symbols.size());
    std::replace_copy(symbols.begin(), symbols.end(), result.begin(), 'T', 'U');
    return result;
}

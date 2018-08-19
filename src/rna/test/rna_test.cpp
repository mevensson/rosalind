#include "rna.hpp"

#include "catch.hpp"

#include <string>

using namespace std::string_literals;

SCENARIO("rna strings", "[rna]")
{
    GIVEN("an empty input string")
    {
        const auto input = ""s;

        WHEN("transcribing DNA into RNA")
        {
            auto result = rna(input); // NOLINT

            THEN("the return empty string")
            {
                CHECK(result == ""s);
            }
        }
    }
}

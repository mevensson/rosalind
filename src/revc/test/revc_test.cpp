#include "revc.hpp"

#include "catch.hpp"

#include <string>

using namespace std::string_literals;

SCENARIO("DNA reverse complement", "[rna]")
{
    GIVEN("an empty input string")
    {
        const auto input = ""s;

        WHEN("taking the reverse complement")
        {
            auto result = revc(input);

            THEN("the return empty string")
            {
                CHECK(result == ""s);
            }
        }
    }
}

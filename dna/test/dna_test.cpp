#include "dna.hpp"

#include "catch.hpp"

SCENARIO("dna strings", "[dna]")
{
    GIVEN("an empty input string")
    {
        const std::string input = {""};

        WHEN("counting DNA nucleotides")
        {
            auto [a, c, g, t] = dna(input);

            THEN("the return 0 A, 0 C, 0 G, and 0 T")
            {
                CHECK(a == 0);
                CHECK(g == 0);
                CHECK(c == 0);
                CHECK(t == 0);
            }
        }
    }
}

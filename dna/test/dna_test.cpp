#include "dna.hpp"

#include "catch.hpp"

SCENARIO("dna strings", "[dna]" )
{
    GIVEN("an empty input string")
    {
        const std::string input = {""};

        WHEN("counting DNA nucleotides")
        {
            auto result = dna(input);

            THEN("the return 0 A, 0 C, 0 G, and 0 T")
            {
                CHECK(std::get<0>(result) == 0);
                CHECK(std::get<1>(result) == 0);
                CHECK(std::get<2>(result) == 0);
                CHECK(std::get<3>(result) == 0);
            }
        }
    }
}

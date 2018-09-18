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
            auto result = revc_ser(input.begin(), input.end());

            THEN("the return empty string")
            {
                CHECK(result == ""s);
            }
        }
    }
    GIVEN("an input string with two A:s")
    {
        const auto input = "AA"s;

        WHEN("taking the reverse complement")
        {
            auto result = revc_ser(input.begin(), input.end());

            THEN("the return string with two T:s")
            {
                CHECK(result == "TT"s);
            }
        }
    }
    GIVEN("an input string with two C:s")
    {
        const auto input = "CC"s;

        WHEN("taking the reverse complement")
        {
            auto result = revc_ser(input.begin(), input.end());

            THEN("the return string with two G:s")
            {
                CHECK(result == "GG"s);
            }
        }
    }
    GIVEN("an input string with two G:s")
    {
        const auto input = "GG"s;

        WHEN("taking the reverse complement")
        {
            auto result = revc_ser(input.begin(), input.end());

            THEN("the return string with two C:s")
            {
                CHECK(result == "CC"s);
            }
        }
    }
    GIVEN("an input string with two T:s")
    {
        const auto input = "TT"s;

        WHEN("taking the reverse complement")
        {
            auto result = revc_ser(input.begin(), input.end());

            THEN("the return string with two A:s")
            {
                CHECK(result == "AA"s);
            }
        }
    }
    GIVEN("an input string containing 'AC'")
    {
        const auto input = "AC"s;

        WHEN("taking the reverse complement")
        {
            auto result = revc_ser(input.begin(), input.end());

            THEN("the return the string 'GT'")
            {
                CHECK(result == "GT"s);
            }
        }
    }
    GIVEN("an input string with lots of A, C, G, and T's")
    {
        const auto input = "AAAACCCGGT"s;

        WHEN("taking the reverse complement")
        {
            auto result = revc_ser(input.begin(), input.end());

            THEN("the return the reverse complement string")
            {
                CHECK(result == "ACCGGGTTTT"s);
            }
        }
        WHEN("taking the reverse complement using 3 threads")
        {
            auto result = revc_par(input.begin(), input.end(), 3);

            THEN("the return the reverse complement string")
            {
                CHECK(result == "ACCGGGTTTT"s);
            }
        }
    }
}

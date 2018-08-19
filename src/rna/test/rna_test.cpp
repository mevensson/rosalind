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
            auto result = rna_ser(input);

            THEN("the return empty string")
            {
                CHECK(result == ""s);
            }
        }
    }
    GIVEN("an input string with two A's")
    {
        const auto input = "AA"s;

        WHEN("transcribing DNA into RNA")
        {
            auto result = rna_ser(input);

            THEN("the return sring with two A's")
            {
                CHECK(result == "AA"s);
            }
        }
    }
    GIVEN("an input string with two C's")
    {
        const auto input = "CC"s;

        WHEN("transcribing DNA into RNA")
        {
            auto result = rna_ser(input);

            THEN("the return string with two C's")
            {
                CHECK(result == "CC"s);
            }
        }
    }
    GIVEN("an input string with two G's")
    {
        const auto input = "GG"s;

        WHEN("transcribing DNA into RNA")
        {
            auto result = rna_ser(input);

            THEN("the return string with two G's")
            {
                CHECK(result == "GG"s);
            }
        }
    }
    GIVEN("an input string with two T's")
    {
        const auto input = "TT"s;

        WHEN("transcribing DNA into RNA")
        {
            auto result = rna_ser(input);

            THEN("the return string with two U's")
            {
                CHECK(result == "UU"s);
            }
        }
    }
    GIVEN("an input string with lots of A, C, G, and T's")
    {
        const auto input =
            "AGCTTTTCATTCTGACTGCAACGGGCAATATGTCTCTGTGTGGATTAAAAAAAGAGTGTCTGATAGCAGC"s;

        WHEN("transcribing DNA into RNA")
        {
            auto result = rna_ser(input);

            THEN("the return string with all T's replaced with U's")
            {
                CHECK(
                    result
                    == "AGCUUUUCAUUCUGACUGCAACGGGCAAUAUGUCUCUGUGUGGAUUAAAAAAAGAGUGUCUGAUAGCAGC"s);
            }
        }
    }
    GIVEN("an input string with lots of A, C, G, and T's")
    {
        const auto input =
            "AGCTTTTCATTCTGACTGCAACGGGCAATATGTCTCTGTGTGGATTAAAAAAAGAGTGTCTGATAGCAGC"s;

        WHEN("transcribing DNA into RNA using 3 threads")
        {
            auto result = rna_par(input, 3);

            THEN("the return string with all T's replaced with U's")
            {
                CHECK(
                    result
                    == "AGCUUUUCAUUCUGACUGCAACGGGCAAUAUGUCUCUGUGUGGAUUAAAAAAAGAGUGUCUGAUAGCAGC"s);
            }
        }
    }
}

#include "dna.hpp"

#include "catch.hpp"

#include <string>

using namespace std::string_literals;

SCENARIO("dna strings", "[dna]")
{
    GIVEN("an empty input string")
    {
        const auto input = ""s;

        WHEN("counting DNA nucleotides")
        {
            auto [a, c, g, t] = dna_ser(input.begin(), input.end()); // NOLINT

            THEN("the return 0 A, 0 C, 0 G, and 0 T")
            {
                CHECK(a == 0);
                CHECK(c == 0);
                CHECK(g == 0);
                CHECK(t == 0);
            }
        }
    }
    GIVEN("an input string with two A's")
    {
        const auto input = "AA"s;

        WHEN("counting DNA nucleotides")
        {
            auto [a, c, g, t] = dna_ser(input.begin(), input.end()); // NOLINT

            THEN("the return 2 A, 0 C, 0 G, and 0 T")
            {
                CHECK(a == 2);
                CHECK(c == 0);
                CHECK(g == 0);
                CHECK(t == 0);
            }
        }
    }
    GIVEN("an input string with two C's")
    {
        const auto input = "CC"s;

        WHEN("counting DNA nucleotides")
        {
            auto [a, c, g, t] = dna_ser(input.begin(), input.end()); // NOLINT

            THEN("the return 0 A, 2 C, 0 G, and 0 T")
            {
                CHECK(a == 0);
                CHECK(c == 2);
                CHECK(g == 0);
                CHECK(t == 0);
            }
        }
    }
    GIVEN("an input string with two G's")
    {
        const auto input = "GG"s;

        WHEN("counting DNA nucleotides")
        {
            auto [a, c, g, t] = dna_ser(input.begin(), input.end()); // NOLINT

            THEN("the return 0 A, 0 C, 2 G, and 0 T")
            {
                CHECK(a == 0);
                CHECK(c == 0);
                CHECK(g == 2);
                CHECK(t == 0);
            }
        }
    }
    GIVEN("an input string with two T's")
    {
        const auto input = "TT"s;

        WHEN("counting DNA nucleotides")
        {
            auto [a, c, g, t] = dna_ser(input.begin(), input.end()); // NOLINT

            THEN("the return 0 A, 0 C, 0 G, and 2 T")
            {
                CHECK(a == 0);
                CHECK(c == 0);
                CHECK(g == 0);
                CHECK(t == 2);
            }
        }
    }
    GIVEN("an input string with lots of A, C, G, and T's")
    {
        const auto input =
            "AGCTTTTCATTCTGACTGCAACGGGCAATATGTCTCTGTGTGGATTAAAAAAAGAGTGTCTGATAGCAGC"s;

        WHEN("counting DNA nucleotides")
        {
            auto [a, c, g, t] = dna_ser(input.begin(), input.end()); // NOLINT

            THEN("the return the count of A, C, G, and T's")
            {
                CHECK(a == 20);
                CHECK(c == 12);
                CHECK(g == 17);
                CHECK(t == 21);
            }
        }
    }
    GIVEN("an input string with lots of A, C, G, and T's")
    {
        const auto input =
            "AGCTTTTCATTCTGACTGCAACGGGCAATATGTCTCTGTGTGGATTAAAAAAAGAGTGTCTGATAGCAGC"s;

        WHEN("counting DNA nucleotides using 3 threads")
        {
            auto [a, c, g, t] = dna_par(input, 3); // NOLINT

            THEN("the return the count of A, C, G, and T's")
            {
                CHECK(a == 20);
                CHECK(c == 12);
                CHECK(g == 17);
                CHECK(t == 21);
            }
        }
    }
}

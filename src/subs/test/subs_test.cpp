#include "subs.hpp"

#include "catch.hpp"

#include <string>

using namespace Catch::Matchers;
using namespace std::string_literals;

SCENARIO("finding substrings", "[subs]")
{
    GIVEN("an empty input string and substring")
    {
        const auto input = ""s;

        WHEN("finding substrings")
        {
            THEN("throw exception")
            {
                REQUIRE_THROWS(subs_ser(input.begin(), input.end()));
            }
        }
    }
    GIVEN("an empty input string and substring")
    {
        const auto input = "\n"s;

        WHEN("finding sub strings")
        {
            auto result = subs_ser(input.begin(), input.end());

            THEN("the return empty vector")
            {
                CHECK(result.empty());
            }
        }
    }
    GIVEN("same input string and substring")
    {
        const auto input = "ATCG\nATCG"s;

        WHEN("finding sub strings")
        {
            auto result = subs_ser(input.begin(), input.end());

            THEN("the return postion 1")
            {
                CHECK_THAT(result, Equals(std::vector<int>{1}));
            }
        }
    }
    GIVEN("input string with repeated substring")
    {
        const auto input = "ATCGATCG\nATCG"s;

        WHEN("finding sub strings")
        {
            auto result = subs_ser(input.begin(), input.end());

            THEN("the return both positions")
            {
                CHECK_THAT(result, Equals(std::vector<int>{1, 5}));
            }
        }
    }
    GIVEN("input string with repeated overlapping substring")
    {
        const auto input = "ATATATAT\nATAT"s;

        WHEN("finding sub strings")
        {
            auto result = subs_ser(input.begin(), input.end());

            THEN("the return all positions")
            {
                CHECK_THAT(result, Equals(std::vector<int>{1, 3, 5}));
            }
        }
    }
    GIVEN("input string, substring, and extra newline")
    {
        const auto input = "ATCG\nATCG\n"s;

        WHEN("finding sub strings")
        {
            auto result = subs_ser(input.begin(), input.end());

            THEN("the return postion")
            {
                CHECK_THAT(result, Equals(std::vector<int>{1}));
            }
        }
    }
    GIVEN("complex input string and substring")
    {
        const auto input = "GATATATGCATATACTT\nATAT"s;

        WHEN("finding sub strings")
        {
            auto result = subs_ser(input.begin(), input.end());

            THEN("the return all positions")
            {
                CHECK_THAT(result, Equals(std::vector<int>{2, 4, 10}));
            }
        }
        WHEN("finding sub strings using 3 threads")
        {
            auto result = subs_par(input.begin(), input.end(), 3);

            THEN("the return all positions")
            {
                CHECK_THAT(result, Equals(std::vector<int>{2, 4, 10}));
            }
        }
    }
}

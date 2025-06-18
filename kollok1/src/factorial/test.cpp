#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "./FACTORIAL.hpp"

TEST_CASE("Factorial handles zero", "[factorial]") {
    auto res = calculateFactorials(0);
    REQUIRE(res.empty());
}

TEST_CASE("Factorial calculates correctly", "[factorial]") {
    auto res = calculateFactorials(5);
    REQUIRE(res.size() == 5);
    REQUIRE(res[0] == 1);  // 0!
    REQUIRE(res[1] == 1);  // 1!
    REQUIRE(res[2] == 2);  // 2!
    REQUIRE(res[3] == 6);  // 3!
    REQUIRE(res[4] == 24); // 4!
}

TEST_CASE("Factorial throws on negative input", "[factorial]") {
    REQUIRE_THROWS_AS(calculateFactorials(-1), std::invalid_argument);
}

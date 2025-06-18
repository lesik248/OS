#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "./array.cpp" // подключаем реализацию removeDuplicates

TEST_CASE("Handles empty input", "[removeDuplicates]") {
    std::vector<int> empty;
    auto res = removeDuplicates(empty);
    REQUIRE(res.empty());
}

TEST_CASE("Removes duplicates", "[removeDuplicates]") {
    std::vector<int> input = { 1, 2, 2, 3, 3, 4 };
    auto res = removeDuplicates(input);
    REQUIRE(res.size() == 4);
}

TEST_CASE("Preserves input order", "[removeDuplicates]") {
    std::vector<int> input = { 3, 1, 2, 1, 4 };
    auto res = removeDuplicates(input);

    REQUIRE(res.size() == 4);
    REQUIRE(res[0] == 3);
    REQUIRE(res[1] == 1);
    REQUIRE(res[2] == 2);
    REQUIRE(res[3] == 4);
}

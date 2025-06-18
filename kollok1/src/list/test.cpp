#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "./list.cpp"

TEST_CASE("ReverseList handles empty list", "[reverse]") {
    std::shared_ptr<ListNode<int>> empty;
    auto res = reverseListRecursive(empty);
    REQUIRE(res == nullptr);
}

TEST_CASE("ReverseList reverses list correctly", "[reverse]") {
    auto head = std::make_shared<ListNode<int>>(1);
    head->next = std::make_shared<ListNode<int>>(2);
    head->next->next = std::make_shared<ListNode<int>>(3);

    auto reversed = reverseListRecursive(head);

    REQUIRE(reversed->data == 3);
    REQUIRE(reversed->next->data == 2);
    REQUIRE(reversed->next->next->data == 1);
    REQUIRE(reversed->next->next->next == nullptr);
}

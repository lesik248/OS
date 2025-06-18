#include "factorial.hpp"
#include <stdexcept>

std::vector<int> calculateFactorials(int n) {
    if (n < 0) {
        throw std::invalid_argument("Negative input is not allowed");
    }

    std::vector<int> result;
    int factorial = 1;
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            factorial *= i;
        }
        result.push_back(factorial);
    }
    return result;
}

#include "array.hpp"
#include <unordered_set>

template<typename T>
std::vector<T> removeDuplicates(const std::vector<T>& input) {
    std::unordered_set<T> seen;
    std::vector<T> result;

    for (const auto& item : input) {
        if (seen.insert(item).second) {
            result.push_back(item);
        }
    }
    return result;
}

// Explicit instantiation to avoid linker error with templates
template std::vector<int> removeDuplicates<int>(const std::vector<int>&);

#include "functions.h"

std::string delete_spaces(const std::string& string) {
    auto result = string;
    size_t i = result.find(' ');
    while (i != result.npos) {
        result.replace(i, 1, "");
        i = result.find(' ');
    }
    return result;
}
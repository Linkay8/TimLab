#include "template_functions.h"

template<typename T>
T string_to_num(const std::string& string) {
    return T();
}

template<>
int64_t string_to_num<int64_t>(const std::string& string) {
    if (string.size() > INT64_STRING_SIZE) {
        throw CalcRangeError("Number " + string + " out of int64_t range");
    }
    int64_t result = 0;
    for (size_t i = 0; i < string.size(); ++i) {
        if (result > INT64_MAX / 10) {
            throw CalcRangeError("Number " + string + " out of int64_t range");
        } else if (result == INT64_MAX / 10) {
            if (static_cast<int64_t>(string[i] - '0') > INT64_MAX % 10) {
                throw CalcRangeError("Number " + string + " out of int64_t range");
            }
        }

        result *= 10;
        result += static_cast<int64_t>(string[i] - '0');
    }
    return result;
}

template<>
double string_to_num<double>(const std::string& string) {
    return stod(string);
}

num_t factorial(num_t n) {
    if (n < 0 || abs(n - int64_t(n)) > pow(10, -6)) {
        return sqrt(-1);
    }
    num_t res = 1;
    for (uint64_t i = 1; i <= n; ++i) {
        res *= i;
    }
    return res;
}
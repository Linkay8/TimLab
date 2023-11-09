#ifndef TEMPLATE_FUNCTIONS_H
#define TEMPLATE_FUNCTIONS_H

#include "functions.h"

template<typename T>
T string_to_num(const std::string& string);

template<>
int64_t string_to_num<int64_t>(const std::string& string);

template<>
double string_to_num<double>(const std::string& string);

num_t factorial(num_t n);

#endif // TEMPLATE_FUNCTIONS_H

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "calc_exception.h"
#include "calc_variable.h"

num_t calculate_expression(const std::string& string);

#endif // CALCULATOR_H
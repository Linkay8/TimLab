#include "calculator.h"
#include "expressions.h"


num_t calculate_expression(const std::string& string) {
    auto data = tokenize(string);
    for (size_t i = 0; i < data.size(); ++i) {
        if (UnknownToken* token = dynamic_cast<UnknownToken*>(data[i].get())) {
            throw CalcInvalidArgument(token->get_value() + " is unknown token");
        }
        if (VariableToken* token = dynamic_cast<VariableToken*>(data[i].get())) {
            throw CalcInvalidArgument("The calculator expression must not contain a variable");
        }
    }
    return parse_expression(data)->calculate();
}
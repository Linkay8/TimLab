#include "expressions.h"
#include <math.h>

Constant::Constant(const num_t& value) : value_(value) {
}

num_t Constant::calculate() {
    return value_;
}

IUnaryOperation::IUnaryOperation(const std::shared_ptr<IExpression>& operand) : operand_(operand) {
}

num_t IUnaryOperation::calculate() {
    return perform_operation(operand_->calculate());
}

Minus::Minus(const std::shared_ptr<IExpression>& operand) : IUnaryOperation(operand) {
}

num_t Minus::perform_operation(const num_t& operand) {
    return -operand;
}

Plus::Plus(const std::shared_ptr<IExpression>& operand) : IUnaryOperation(operand) {
}

num_t Plus::perform_operation(const num_t& operand) {
    return operand;
}

Abs::Abs(const std::shared_ptr<IExpression>& operand) : IUnaryOperation(operand) {
}

num_t Abs::perform_operation(const num_t& operand) {
    return operand < 0 ? -operand : operand;
}

Sqrt::Sqrt(const std::shared_ptr<IExpression>& operand) : IUnaryOperation(operand) {
}

num_t Sqrt::perform_operation(const num_t& operand) {
    if (operand < 0) {
        throw CalcInvalidArgument("Sqrt argument is negative number");
    }
    return sqrt(operand);
}

Sin::Sin(const std::shared_ptr<IExpression>& operand) : IUnaryOperation(operand) {
}

num_t Sin::perform_operation(const num_t& operand) {
    return sin(operand);
}

Cos::Cos(const std::shared_ptr<IExpression>& operand) : IUnaryOperation(operand) {
}

num_t Cos::perform_operation(const num_t& operand) {
    return cos(operand);
}

Tan::Tan(const std::shared_ptr<IExpression>& operand) : IUnaryOperation(operand) {
}

num_t Tan::perform_operation(const num_t& operand) {
    return tan(operand);
}

Cot::Cot(const std::shared_ptr<IExpression>& operand) : IUnaryOperation(operand) {
}

num_t Cot::perform_operation(const num_t& operand) {
    return 1 / tan(operand);
}

IBinaryOperation::IBinaryOperation(const std::shared_ptr<IExpression>& left_operand, const std::shared_ptr<IExpression>& right_operand) : 
    left_operand_(left_operand), right_operand_(right_operand) {
}

num_t IBinaryOperation::calculate() {
    return perform_operation(left_operand_.get()->calculate(), right_operand_.get()->calculate());
}

Sum::Sum(const std::shared_ptr<IExpression>& left_operand, const std::shared_ptr<IExpression>& right_operand) : 
    IBinaryOperation(left_operand, right_operand) {

}

num_t Sum::perform_operation(const num_t& left_operand, const num_t& right_operand) {
    return left_operand + right_operand;
}

Subtract::Subtract(const std::shared_ptr<IExpression>& left_operand, const std::shared_ptr<IExpression>& right_operand) :
    IBinaryOperation(left_operand, right_operand) {

}

num_t Subtract::perform_operation(const num_t& left_operand, const num_t& right_operand) {
    return left_operand - right_operand;
}

Multiply::Multiply(const std::shared_ptr<IExpression>& left_operand, const std::shared_ptr<IExpression>& right_operand) :
    IBinaryOperation(left_operand, right_operand) {

}

num_t Multiply::perform_operation(const num_t& left_operand, const num_t& right_operand) {
    return left_operand * right_operand;
}

Divide::Divide(const std::shared_ptr<IExpression>& left_operand, const std::shared_ptr<IExpression>& right_operand) :
    IBinaryOperation(left_operand, right_operand) {

}

num_t Divide::perform_operation(const num_t& left_operand, const num_t& right_operand) {
    return left_operand / right_operand;
}

Pow::Pow(const std::shared_ptr<IExpression>& left_operand, const std::shared_ptr<IExpression>& right_operand) :
    IBinaryOperation(left_operand, right_operand) {

}

num_t Log::perform_operation(const num_t& left_operand, const num_t& right_operand) {
    return log2(right_operand) / log2(left_operand);
}

Log::Log(const std::shared_ptr<IExpression>& left_operand, const std::shared_ptr<IExpression>& right_operand) :
    IBinaryOperation(left_operand, right_operand) {

}

num_t Pow::perform_operation(const num_t& left_operand, const num_t& right_operand) { 
    auto res = pow(left_operand, right_operand);
    if (isnan(res)) {
        throw CalcInvalidArgument("Pow invalid argument");
    }
    return res;
}

std::shared_ptr<IExpression> parse_expression(const std::vector<std::shared_ptr<IToken>>& data) {
    if (!data.size()) {
        throw CalcInvalidArgument("Data of size == 0");
    }

    if (data.size() == 1) {
        if (NumberToken* token = dynamic_cast<NumberToken*>(data[0].get())) {
            return std::make_shared<Constant>(token->get_value());
        }
        if (VariableToken* token = dynamic_cast<VariableToken*>(data[0].get())) {
            return std::make_shared<Constant>(token->get_value());
        }
        throw CalcInvalidArgument("Data of size == 1 is not a constant");
    }

    int64_t is_in_bracket = 0;
    std::vector<size_t> first_priority_operations;  // Sum, Subtract
    std::vector<size_t> second_priority_operations;  // Multiple, Divide
    std::vector<size_t> third_priority_operations;  // Minus, Plus
    std::vector<size_t> fourth_priority_operations;  // Pow
    std::vector<size_t> fifth_priority_operations;  // Abs, Sqrt, Sin, Cos, Tan, Cot
    std::vector<size_t> sixth_priority_operations;  // Factorial
    std::vector<size_t> seventh_priority_operations;  // Log
    size_t beg = 0;
    
    if (MinusToken() == data[0]) {
        third_priority_operations.push_back(0);
        beg = 1;
    }

    if (PlusToken() == data[0]) {
        third_priority_operations.push_back(0);
        beg = 1;
    }

    if (AbsToken() == data[0]) {
        fifth_priority_operations.push_back(0);
        beg = 1;
    }

    if (SqrtToken() == data[0]) {
        fifth_priority_operations.push_back(0);
        beg = 1;
    }

    if (SinToken() == data[0]) {
        fifth_priority_operations.push_back(0);
        beg = 1;
    }

    if (CosToken() == data[0]) {
        fifth_priority_operations.push_back(0);
        beg = 1;
    }

    if (TanToken() == data[0]) {
        fifth_priority_operations.push_back(0);
        beg = 1;
    }

    if (CotToken() == data[0]) {
        fifth_priority_operations.push_back(0);
        beg = 1;
    }

    if (LogToken() == data[0]) {
        seventh_priority_operations.push_back(0);
        beg = 1;
    }

    for (size_t i = beg; i < data.size(); ++i) {
        if (OpeningBracketToken() == data[i]) {
            ++is_in_bracket;
        }

        if (ClosingBracketToken() == data[i]) {
            --is_in_bracket;
            if (is_in_bracket < 0) {
                throw CalcInvalidArgument("Expression consist wrong bracket sequence");
            }
        }

        if (!is_in_bracket && MinusToken() == data[i]) {
            first_priority_operations.push_back(i);
        }

        if (!is_in_bracket && PlusToken() == data[i]) {
            first_priority_operations.push_back(i);
        }

        if (!is_in_bracket  && DivideToken() == data[i]) {
            second_priority_operations.push_back(i);
        }

        if (!is_in_bracket && MultiplyToken() == data[i]) {
            second_priority_operations.push_back(i);
        }

        if (!is_in_bracket && PowToken() == data[i]) {
            fourth_priority_operations.push_back(i);
        }

        if (!is_in_bracket && FactorialToken() == data[i]) {
            sixth_priority_operations.push_back(i);
        }

        if (is_in_bracket == 1 && CommaToken() == data[i]) {
            seventh_priority_operations.push_back(i);
        }
    }

    if (first_priority_operations.size()) {
        std::vector<std::shared_ptr<IToken>> left_operand;
        std::copy(data.begin(), data.begin() + first_priority_operations[0], std::back_inserter(left_operand));
        auto left_exp = parse_expression(left_operand);
        auto end_iter = data.end();
        for (size_t i = 0; i < first_priority_operations.size(); ++i) {
            std::vector<std::shared_ptr<IToken>> right_operand;
            if (i + 1 == first_priority_operations.size()) {
                end_iter = data.end();
            } else {
                end_iter = data.begin() + first_priority_operations[i + 1];
            }
            std::copy(data.begin() + first_priority_operations[i] + 1, end_iter, std::back_inserter(right_operand));
            if (dynamic_cast<PlusToken*>(data[first_priority_operations[i]].get())) {
                left_exp = std::make_shared<Sum>(left_exp, parse_expression(right_operand));
            }
            if (dynamic_cast<MinusToken*>(data[first_priority_operations[i]].get())) {
                left_exp = std::make_shared<Subtract>(left_exp, parse_expression(right_operand));
            }
        }
        return left_exp;
    }

    if (second_priority_operations.size()) {
        std::vector<std::shared_ptr<IToken>> left_operand;
        std::copy(data.begin(), data.begin() + second_priority_operations[0], std::back_inserter(left_operand));
        auto left_exp = parse_expression(left_operand);
        auto end_iter = data.end();

        for (size_t i = 0; i < second_priority_operations.size(); ++i) {
            std::vector<std::shared_ptr<IToken>> right_operand;
            if (i + 1 == second_priority_operations.size()) {
                end_iter = data.end();
            } else {
                end_iter = data.begin() + second_priority_operations[i + 1];
            }
            std::copy(data.begin() + second_priority_operations[i] + 1, end_iter, std::back_inserter(right_operand));
            if (dynamic_cast<MultiplyToken*>(data[second_priority_operations[i]].get())) {
                left_exp = std::make_shared<Multiply>(left_exp, parse_expression(right_operand));
            }
            if (dynamic_cast<DivideToken*>(data[second_priority_operations[i]].get())) {
                left_exp = std::make_shared<Divide>(left_exp, parse_expression(right_operand));
            }
        }
        return left_exp;
    }

    if (third_priority_operations.size()) {
        std::vector<std::shared_ptr<IToken>> operand;
        std::copy(data.begin() + 1, data.end(), std::back_inserter(operand));
        if (MinusToken() == data[third_priority_operations[0]]) {
            return std::make_shared<Minus>(parse_expression(operand));
        }
        if (PlusToken() == data[third_priority_operations[0]]) {
            return std::make_shared<Plus>(parse_expression(operand));
        }
    }

    if (fourth_priority_operations.size()) {
        std::vector<std::shared_ptr<IToken>> right_operand;
        std::copy(data.begin() + fourth_priority_operations[fourth_priority_operations.size() - 1] + 1,
            data.end(), std::back_inserter(right_operand));
        auto right_exp = parse_expression(right_operand);
        auto beg_iter = data.begin();

        for (size_t i = fourth_priority_operations.size(); i > 0; --i) {
            std::vector<std::shared_ptr<IToken>> left_operand;
            if (i == 1) {
                beg_iter = data.begin();
            } else {
                beg_iter = data.begin() + fourth_priority_operations[i - 2] + 1;
            }
            std::copy(beg_iter, data.begin() + fourth_priority_operations[i - 1], std::back_inserter(left_operand));
            if (dynamic_cast<PowToken*>(data[fourth_priority_operations[i - 1]].get())) {
                right_exp = std::make_shared<Pow>(parse_expression(left_operand), right_exp);
            }
        }
        return right_exp;
    }

    if (fifth_priority_operations.size()) {
        std::vector<std::shared_ptr<IToken>> operand;
        std::copy(data.begin() + 1, data.end(), std::back_inserter(operand));
        if (AbsToken() == data[fifth_priority_operations[0]]) {
            return std::make_shared<Abs>(parse_expression(operand));
        }
        if (SqrtToken() == data[fifth_priority_operations[0]]) {
            return std::make_shared<Sqrt>(parse_expression(operand));
        }
        if (SinToken() == data[fifth_priority_operations[0]]) {
            return std::make_shared<Sin>(parse_expression(operand));
        }
        if (CosToken() == data[fifth_priority_operations[0]]) {
            return std::make_shared<Cos>(parse_expression(operand));
        }
        if (TanToken() == data[fifth_priority_operations[0]]) {
            return std::make_shared<Tan>(parse_expression(operand));
        }
        if (CotToken() == data[fifth_priority_operations[0]]) {
            return std::make_shared<Cot>(parse_expression(operand));
        }
    }

    if (sixth_priority_operations.size()) {
        std::vector<std::shared_ptr<IToken>> operand;
        std::copy(data.begin(), data.begin() + sixth_priority_operations[sixth_priority_operations.size() - 1], std::back_inserter(operand));
        if (FactorialToken() == data[sixth_priority_operations[sixth_priority_operations.size() - 1]]) {
            return std::make_shared<Factorial>(parse_expression(operand));
        }
    }

    if (seventh_priority_operations.size()) {
        std::vector<std::shared_ptr<IToken>> left_operand;
        std::vector<std::shared_ptr<IToken>> right_operand;
        std::copy(data.begin() + 2, data.begin() + seventh_priority_operations[1], std::back_inserter(left_operand));
        std::copy(data.begin() + seventh_priority_operations[1] + 1, data.end() - 1, std::back_inserter(right_operand));
        if (LogToken() == data[seventh_priority_operations[0]]) {
            return std::make_shared<Log>(parse_expression(left_operand), parse_expression(right_operand));
        }
    }

    if (!is_in_bracket) {
        if (OpeningBracketToken() == data[0] && ClosingBracketToken() == data[(data.size() - 1)]) {
            std::vector<std::shared_ptr<IToken>> data_copy;
            std::copy(data.begin() + 1, data.end() - 1, std::back_inserter(data_copy));
            return parse_expression(data_copy);
        }
        throw CalcInvalidArgument("Parse expression error");
    }

    throw CalcInvalidArgument("No operation out of brackets");
}

Factorial::Factorial(const std::shared_ptr<IExpression>& operand) : IUnaryOperation(operand) {
}

num_t Factorial::perform_operation(const num_t& operand) {
    return factorial(operand);
}

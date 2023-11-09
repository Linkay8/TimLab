#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H

#include "tokenize.h"
#include "calc_exception.h"
#include "calc_variable.h"
#include "template_functions.h"

class IExpression {
public:
    virtual num_t calculate() = 0;
};

class Constant : public IExpression {
private:
    num_t value_;

public:
    Constant(const num_t& value);
    virtual num_t calculate();
};

class IUnaryOperation : public IExpression {
private:
    std::shared_ptr<IExpression> operand_;
public:
    IUnaryOperation(const std::shared_ptr<IExpression>& operand);
    virtual num_t perform_operation(const num_t& operand) = 0;
    num_t calculate();
};

class Minus : public IUnaryOperation {
public:
    Minus(const std::shared_ptr<IExpression>& operand);
    num_t perform_operation(const num_t& operand);
};

class Plus : public IUnaryOperation {
public:
    Plus(const std::shared_ptr<IExpression>& operand);
    num_t perform_operation(const num_t& operand);
};

class Abs : public IUnaryOperation {
public:
    Abs(const std::shared_ptr<IExpression>& operand);
    num_t perform_operation(const num_t& operand);
};

class Sqrt : public IUnaryOperation {
public:
    Sqrt(const std::shared_ptr<IExpression>& operand);
    num_t perform_operation(const num_t& operand);
};

class Sin : public IUnaryOperation {
public:
    Sin(const std::shared_ptr<IExpression>& operand);
    num_t perform_operation(const num_t& operand);
};

class Cos : public IUnaryOperation {
public:
    Cos(const std::shared_ptr<IExpression>& operand);
    num_t perform_operation(const num_t& operand);
};

class Tan : public IUnaryOperation {
public:
    Tan(const std::shared_ptr<IExpression>& operand);
    num_t perform_operation(const num_t& operand);
};

class Cot : public IUnaryOperation {
public:
    Cot(const std::shared_ptr<IExpression>& operand);
    num_t perform_operation(const num_t& operand);
};

class Factorial : public IUnaryOperation {
public:
    Factorial(const std::shared_ptr<IExpression>& operand);
    num_t perform_operation(const num_t& operand);
};

class IBinaryOperation : public IExpression {
private:
    std::shared_ptr<IExpression> left_operand_;
    std::shared_ptr<IExpression> right_operand_;
public:
    IBinaryOperation(const std::shared_ptr<IExpression>& left_operand, const std::shared_ptr<IExpression>& right_operand);
    virtual num_t perform_operation(const num_t& left_operand, const num_t& right_operand) = 0;
    num_t calculate();
};

class Sum : public IBinaryOperation {
public:
    Sum(const std::shared_ptr<IExpression>& left_operand, const std::shared_ptr<IExpression>& right_operand);
    num_t perform_operation(const num_t& left_operand, const num_t& right_operand);
};

class Subtract : public IBinaryOperation {
public:
    Subtract(const std::shared_ptr<IExpression>& left_operand, const std::shared_ptr<IExpression>& right_operand);
    num_t perform_operation(const num_t& left_operand, const num_t& right_operand);
};

class Multiply : public IBinaryOperation {
public:
    Multiply(const std::shared_ptr<IExpression>& left_operand, const std::shared_ptr<IExpression>& right_operand);
    num_t perform_operation(const num_t& left_operand, const num_t& right_operand);
};

class Divide : public IBinaryOperation {
public:
    Divide(const std::shared_ptr<IExpression>& left_operand, const std::shared_ptr<IExpression>& right_operand);
    num_t perform_operation(const num_t& left_operand, const num_t& right_operand);
};

class Pow : public IBinaryOperation {
public:
    Pow(const std::shared_ptr<IExpression>& left_operand, const std::shared_ptr<IExpression>& right_operand);
    num_t perform_operation(const num_t& left_operand, const num_t& right_operand);
};

class Log : public IBinaryOperation {
public:
    Log(const std::shared_ptr<IExpression>& left_operand, const std::shared_ptr<IExpression>& right_operand);
    num_t perform_operation(const num_t& left_operand, const num_t& right_operand);
};

std::shared_ptr<IExpression> parse_expression(const std::vector<std::shared_ptr<IToken>>& data);

#endif // EXPRESSIONS_H

#ifndef TOKENIZE_H
#define TOKENIZE_H

#include <string>
#include <memory>
#include <vector>
#include "calc_variable.h"

// Token declaration
class IToken {
public:
    virtual bool operator==(const std::shared_ptr<IToken>& token) = 0;
};


// PlusToken declaration
class PlusToken : public IToken {
public:
    bool operator==(const std::shared_ptr<IToken>& token);
};


// MinusToken declaration
class MinusToken : public IToken {
public:
    bool operator==(const std::shared_ptr<IToken>& token);
};


// MultiplyToken declaration
class MultiplyToken : public IToken {
public:
    bool operator==(const std::shared_ptr<IToken>& token);
};


// DivideToken declaration
class DivideToken : public IToken {
public:
    bool operator==(const std::shared_ptr<IToken>& token);
};


// OpeningBracketToken declaration
class OpeningBracketToken : public IToken {
public:
    bool operator==(const std::shared_ptr<IToken>& token);
};


// ClosingBracketToken declaration
class ClosingBracketToken : public IToken {
public:
    bool operator==(const std::shared_ptr<IToken>& token);
};


// AbsToken declaration
class AbsToken : public IToken {
public:
    bool operator==(const std::shared_ptr<IToken>& token);
};


// SqrtToken declaration
class SqrtToken : public IToken {
public:
    bool operator==(const std::shared_ptr<IToken>& token);
};


// SinToken declaration
class SinToken : public IToken {
public:
    bool operator==(const std::shared_ptr<IToken>& token);
};


// CosToken declaration
class CosToken : public IToken {
public:
    bool operator==(const std::shared_ptr<IToken>& token);
};


// TanToken declaration
class TanToken : public IToken {
public:
    bool operator==(const std::shared_ptr<IToken>& token);
};


// CotToken declaration
class CotToken : public IToken {
public:
    bool operator==(const std::shared_ptr<IToken>& token);
};


// PowToken declaration
class PowToken : public IToken {
public:
    bool operator==(const std::shared_ptr<IToken>& token);
};


// LogToken declaration
class LogToken : public IToken {
public:
    bool operator==(const std::shared_ptr<IToken>& token);
};


// CommaToken declaration
class CommaToken : public IToken {
public:
    bool operator==(const std::shared_ptr<IToken>& token);
};

// FactorialToken declaration
class FactorialToken : public IToken {
public:
    bool operator==(const std::shared_ptr<IToken>& token);
};

// NumberToken declaration
class NumberToken : public IToken {
private:
    num_t value_;
public:
    NumberToken(const num_t& value);
    const num_t& get_value() const;
    bool operator==(const std::shared_ptr<IToken>& token);
};

// VariableToken declaration
class VariableToken : public IToken {
private:
    num_t value_;
public:
    VariableToken();
    VariableToken(const num_t& value);
    const num_t& get_value() const;
    void set_value(const num_t& value);
    bool operator==(const std::shared_ptr<IToken>& token);
};


// UnknownToken declaration
class UnknownToken : public IToken {
private:
    std::string value_;
public:
    UnknownToken(std::string value = "");
    const std::string& get_value() const;
    bool operator==(const std::shared_ptr<IToken>& token);
};

// Tokens functions declaration
bool operator==(const std::shared_ptr<IToken>& first, const std::shared_ptr<IToken>& second);

// Tokenize function declaration
std::vector<std::shared_ptr<IToken>> tokenize(const std::string& data);

#endif // TOKENIZE_H
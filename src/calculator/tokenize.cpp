#include "tokenize.h"
#include "template_functions.h"

// UnknownToken definition
UnknownToken::UnknownToken(std::string value) : value_(value) {
}

const std::string& UnknownToken::get_value() const {
    return value_;
}

bool UnknownToken::operator==(const std::shared_ptr<IToken>& token) {
    if (this == token.get()) {
        return true;
    }

    if (UnknownToken* u_token = dynamic_cast<UnknownToken*>(token.get())) {
        if (u_token->get_value() != get_value()) {
            return false;
        }
        return true;
    }
    
    return false;
}

// NumberToken definition
NumberToken::NumberToken(const num_t& value) : value_(value) {
}

const num_t& NumberToken::get_value() const {
    return value_;
}

bool NumberToken::operator==(const std::shared_ptr<IToken>& token) {
    if (this == token.get()) {
        return true;
    }

    if (NumberToken* u_token = dynamic_cast<NumberToken*>(token.get())) {
        if (u_token->get_value() != get_value()) {
            return false;
        }
        return true;
    }

    return false;
}

// VariableToken definition
VariableToken::VariableToken(const num_t& value) : value_(value) {
}

VariableToken::VariableToken() {
}


const num_t& VariableToken::get_value() const {
    return value_;
}

void VariableToken::set_value(const num_t& value) {
    value_ = value;
}

bool VariableToken::operator==(const std::shared_ptr<IToken>& token) {
    if (this == token.get()) {
        return true;
    }

    if (VariableToken* u_token = dynamic_cast<VariableToken*>(token.get())) {
        return true;
    }

    return false;
}

// PlusToken definition
bool PlusToken::operator==(const std::shared_ptr<IToken>& token) {
    if (this == token.get()) {
        return true;
    }

    return dynamic_cast<PlusToken*>(token.get());
}


// SqrtToken definition
bool SqrtToken::operator==(const std::shared_ptr<IToken>& token) {
    if (this == token.get()) {
        return true;
    }

    return dynamic_cast<SqrtToken*>(token.get());
}


// LogToken definition
bool LogToken::operator==(const std::shared_ptr<IToken>& token) {
    if (this == token.get()) {
        return true;
    }

    return dynamic_cast<LogToken*>(token.get());
}


// CommaToken definition
bool CommaToken::operator==(const std::shared_ptr<IToken>& token) {
    if (this == token.get()) {
        return true;
    }

    return dynamic_cast<CommaToken*>(token.get());
}


// PowToken definition
bool PowToken::operator==(const std::shared_ptr<IToken>& token) {
    if (this == token.get()) {
        return true;
    }

    return dynamic_cast<PowToken*>(token.get());
}


// MinusToken definition
bool MinusToken::operator==(const std::shared_ptr<IToken>& token) {
    if (this == token.get()) {
        return true;
    }
    return dynamic_cast<MinusToken*>(token.get());
}


// OpeningBracketToken definition
bool OpeningBracketToken::operator==(const std::shared_ptr<IToken>& token) {
    if (this == token.get()) {
        return true;
    }

    return dynamic_cast<OpeningBracketToken*>(token.get());
}


// ClosingBracketToken definition
bool ClosingBracketToken::operator==(const std::shared_ptr<IToken>& token) {
    if (this == token.get()) {
        return true;
    }

    return dynamic_cast<ClosingBracketToken*>(token.get());
}


// AbsToken definition
bool AbsToken::operator==(const std::shared_ptr<IToken>& token) {
    if (this == token.get()) {
        return true;
    }

    return dynamic_cast<AbsToken*>(token.get());
}


// MultiplyToken definition
bool MultiplyToken::operator==(const std::shared_ptr<IToken>& token) {
    if (this == token.get()) {
        return true;
    }

    return dynamic_cast<MultiplyToken*>(token.get());
}


// DivideToken definition
bool DivideToken::operator==(const std::shared_ptr<IToken>& token) {
    if (this == token.get()) {
        return true;
    }

    return dynamic_cast<DivideToken*>(token.get());
}


// SinToken definition
bool SinToken::operator==(const std::shared_ptr<IToken>& token) {
    if (this == token.get()) {
        return true;
    }

    return dynamic_cast<SinToken*>(token.get());
}


// CosToken definition
bool CosToken::operator==(const std::shared_ptr<IToken>& token) {
    if (this == token.get()) {
        return true;
    }

    return dynamic_cast<CosToken*>(token.get());
}


// TanToken definition
bool TanToken::operator==(const std::shared_ptr<IToken>& token) {
    if (this == token.get()) {
        return true;
    }

    return dynamic_cast<TanToken*>(token.get());
}


// CotToken definition
bool CotToken::operator==(const std::shared_ptr<IToken>& token) {
    if (this == token.get()) {
        return true;
    }

    return dynamic_cast<CotToken*>(token.get());
}


// Tokens function definition
bool operator==(const std::shared_ptr<IToken>& first, const std::shared_ptr<IToken>& second) {
    return (*first) == second;
}

// Tokenize function definition
std::vector<std::shared_ptr<IToken>> tokenize(const std::string& data) {
    std::vector<std::shared_ptr<IToken>> result;
    auto data_copy = delete_spaces(data);
    std::string unknown_string = "";
    std::string number_string = "";
    for (size_t i = 0; i < data_copy.size(); ++i) {
        switch (data_copy[i]) {
        case '+':
            if (number_string.size()) {
                result.push_back(std::make_shared<NumberToken>(string_to_num<num_t>(number_string)));
                number_string = "";
            }
            if (unknown_string.size()) {
                result.push_back(std::make_shared<UnknownToken>(unknown_string));
                unknown_string = "";
            }
            result.push_back(std::make_shared<PlusToken>());
            break;
        case '^':
            if (number_string.size()) {
                result.push_back(std::make_shared<NumberToken>(string_to_num<num_t>(number_string)));
                number_string = "";
            }
            if (unknown_string.size()) {
                result.push_back(std::make_shared<UnknownToken>(unknown_string));
                unknown_string = "";
            }
            result.push_back(std::make_shared<PowToken>());
            break;
        case '-':
            if (number_string.size()) {
                result.push_back(std::make_shared<NumberToken>(string_to_num<num_t>(number_string)));
                number_string = "";
            }
            if (unknown_string.size()) {
                result.push_back(std::make_shared<UnknownToken>(unknown_string));
                unknown_string = "";
            }
            result.push_back(std::make_shared<MinusToken>());
            break;
        case ',':
            if (number_string.size()) {
                result.push_back(std::make_shared<NumberToken>(string_to_num<num_t>(number_string)));
                number_string = "";
            }
            if (unknown_string.size()) {
                result.push_back(std::make_shared<UnknownToken>(unknown_string));
                unknown_string = "";
            }
            result.push_back(std::make_shared<CommaToken>());
            break;
        case '/':
            if (number_string.size()) {
                result.push_back(std::make_shared<NumberToken>(string_to_num<num_t>(number_string)));
                number_string = "";
            }
            if (unknown_string.size()) {
                result.push_back(std::make_shared<UnknownToken>(unknown_string));
                unknown_string = "";
            }
            result.push_back(std::make_shared<DivideToken>());
            break;
        case '*':
            if (number_string.size()) {
                result.push_back(std::make_shared<NumberToken>(string_to_num<num_t>(number_string)));
                number_string = "";
            }
            if (unknown_string.size()) {
                result.push_back(std::make_shared<UnknownToken>(unknown_string));
                unknown_string = "";
            }
            result.push_back(std::make_shared<MultiplyToken>());
            break;
        case '(':
            if (number_string.size()) {
                result.push_back(std::make_shared<NumberToken>(string_to_num<num_t>(number_string)));
                number_string = "";
            }
            if (unknown_string.size()) {
                result.push_back(std::make_shared<UnknownToken>(unknown_string));
                unknown_string = "";
            }
            result.push_back(std::make_shared<OpeningBracketToken>());
            break;
        case ')':
            if (number_string.size()) {
                result.push_back(std::make_shared<NumberToken>(string_to_num<num_t>(number_string)));
                number_string = "";
            }
            if (unknown_string.size()) {
                result.push_back(std::make_shared<UnknownToken>(unknown_string));
                unknown_string = "";
            }
            result.push_back(std::make_shared<ClosingBracketToken>());
            break;
        case '!':
            if (number_string.size()) {
                result.push_back(std::make_shared<NumberToken>(string_to_num<num_t>(number_string)));
                number_string = "";
            }
            if (unknown_string.size()) {
                result.push_back(std::make_shared<UnknownToken>(unknown_string));
                unknown_string = "";
            }
            result.push_back(std::make_shared<FactorialToken>());
            break;
        default:
            if (DIGITS_STRING.find(data_copy[i]) == DIGITS_STRING.npos) {
                if (number_string.size()) {
                    result.push_back(std::make_shared<NumberToken>(string_to_num<num_t>(number_string)));
                    number_string = "";
                }
                unknown_string.push_back(data_copy[i]);
            } else {
                if (unknown_string.size()) {
                    result.push_back(std::make_shared<UnknownToken>(unknown_string));
                    unknown_string = "";
                }
                number_string.push_back(data_copy[i]);
            }
            if (unknown_string == "abs") {
                result.push_back(std::make_shared<AbsToken>());
                unknown_string = "";
            }
            if (unknown_string == "sqrt") {
                result.push_back(std::make_shared<SqrtToken>());
                unknown_string = "";
            }
            if (unknown_string == "sin") {
                result.push_back(std::make_shared<SinToken>());
                unknown_string = "";
            }
            if (unknown_string == "cos") {
                result.push_back(std::make_shared<CosToken>());
                unknown_string = "";
            }
            if (unknown_string == "tan") {
                result.push_back(std::make_shared<TanToken>());
                unknown_string = "";
            }
            if (unknown_string == "cot") {
                result.push_back(std::make_shared<CotToken>());
                unknown_string = "";
            }
            if (unknown_string == "PI") {
                result.push_back(std::make_shared<NumberToken>(PI));
                unknown_string = "";
            }
            if (unknown_string == "E") {
                result.push_back(std::make_shared<NumberToken>(E));
                unknown_string = "";
            }
            if (unknown_string == "x") {
                result.push_back(std::make_shared<VariableToken>());
                unknown_string = "";
            }
            if (unknown_string == "log") {
                result.push_back(std::make_shared<LogToken>());
                unknown_string = "";
            }
            break;
        }
    }

    if (number_string.size()) {
        result.push_back(std::make_shared<NumberToken>(string_to_num<num_t>(number_string)));
        number_string = "";
    }
    if (unknown_string.size()) {
        result.push_back(std::make_shared<UnknownToken>(unknown_string));
        unknown_string = "";
    }

    return result;
}

// FactorialToken definition
bool FactorialToken::operator==(const std::shared_ptr<IToken>& token) {
    if (this == token.get()) {
        return true;
    }

    return dynamic_cast<FactorialToken*>(token.get());
}

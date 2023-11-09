#include "numbers_exception.h"

const std::string NumException::kName = "NumException";

NumException::NumException(const std::string& message) : message_(message) {
}

const std::string& NumException::name() const {
    return kName;
}

const std::string& NumException::what() const {
    return message_;
}

const std::string NumRuntimeError::kName = "NumRuntimeError";

NumRuntimeError::NumRuntimeError(const std::string& message) : NumException(message) {
}

const std::string& NumRuntimeError::name() const {
    return kName;
}

const std::string NumLogicError::kName = "NumLogicError";

NumLogicError::NumLogicError(const std::string& message) : NumException(message) {
}

const std::string& NumLogicError::name() const {
    return kName;
}

const std::string NumDivisionByZero::kName = "NumDivisionByZero";

NumDivisionByZero::NumDivisionByZero(const std::string& message) : NumLogicError(message) {
}

const std::string& NumDivisionByZero::name() const {
    return kName;
}
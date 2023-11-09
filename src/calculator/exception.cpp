#include "exception.h"

const std::string Exception::kName = "Exception";

Exception::Exception(const std::string& message) : message_(message) {
}

const std::string& Exception::name() const {
    return kName;
}

const std::string& Exception::what() const {
    return message_;
}

const std::string RuntimeError::kName = "RuntimeError";

RuntimeError::RuntimeError(const std::string& message) : Exception(message) {
}

const std::string& RuntimeError::name() const {
    return kName;
}

const std::string LogicError::kName = "LogicError";

LogicError::LogicError(const std::string& message) : Exception(message) {
}

const std::string& LogicError::name() const {
    return kName;
}
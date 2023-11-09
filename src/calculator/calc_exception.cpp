#include "calc_exception.h"

const std::string CalcException::kName = "CalcException";

CalcException::CalcException(const std::string& message) : message_(message) {
}

const std::string& CalcException::name() const {
    return kName;
}

const std::string& CalcException::what() const {
    return message_;
}

const std::string CalcRuntimeError::kName= "CalcRuntimeError";

CalcRuntimeError::CalcRuntimeError(const std::string& message) : CalcException(message) {
}

const std::string& CalcRuntimeError::name() const {
    return kName;
}

const std::string CalcRangeError::kName = "CalcRangeError";

CalcRangeError::CalcRangeError(const std::string& message ) : CalcRuntimeError(message) {
}

const std::string& CalcRangeError::name() const {
    return kName;
}

const std::string CalcLogicError::kName = "CalcLogicError";

CalcLogicError::CalcLogicError(const std::string& message) : CalcException(message) {
}

const std::string& CalcLogicError::name() const {
    return kName;
}

const std::string CalcInvalidArgument::kName = "CalcInvalidArgument";

CalcInvalidArgument::CalcInvalidArgument(const std::string& message) : CalcLogicError(message) {
}

const std::string& CalcInvalidArgument::name() const {
    return kName;
}
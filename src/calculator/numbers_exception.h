#ifndef NUMBERS_EXCEPTION_H
#define NUMBERS_EXCEPTION_H

#include "exception.h"

class NumException : public Exception {
private:
    const std::string message_;
    static const std::string kName;
public:
    NumException(const std::string& message = "");
    const std::string& what() const;
    virtual const std::string& name() const;
};

class NumRuntimeError : public NumException, public Exception {
private:
    static const std::string kName;
public:
    NumRuntimeError(const std::string& message = "");
    virtual const std::string& name() const;
};

class NumLogicError : public NumException, public Exception {
private:
    static const std::string kName;
public:
    NumLogicError(const std::string& message = "");
    virtual const std::string& name() const;
};

class NumDivisionByZero : public NumLogicError, public LogicError {
private:
    static const std::string kName;
public:
    NumDivisionByZero(const std::string& message = "");
    virtual const std::string& name() const;
};

#endif // NUMBERS_EXCEPTION_H
#ifndef CALC_EXCEPTION_H
#define CALC_EXCEPTION_H

#include <string> 
#include "exception.h"

class CalcException : public Exception {
private:
    const std::string message_;
    static const std::string kName;
public:
    CalcException(const std::string& message = "");
    const std::string& what() const;
    virtual const std::string& name() const;
};

class CalcRuntimeError : public CalcException, public Exception {
private:
    static const std::string kName;
public:
    CalcRuntimeError(const std::string& message = "");
    virtual const std::string& name() const;
};

class CalcRangeError : public CalcRuntimeError, public RuntimeError {
private:
    static const std::string kName;
public:
    CalcRangeError(const std::string& message = "");
    virtual const std::string& name() const;
};

class CalcLogicError : public CalcException, public Exception {
private:
    static const std::string kName;
public:
    CalcLogicError(const std::string& message = "");
    virtual const std::string& name() const;
};

class CalcInvalidArgument : public CalcLogicError, public LogicError {
private:
    static const std::string kName;
public:
    CalcInvalidArgument(const std::string& message = "");
    virtual const std::string& name() const;
};

#endif // CALC_EXCEPTION_H

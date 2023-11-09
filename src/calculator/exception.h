#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string> 

class Exception {
private:
    const std::string message_;
    static const std::string kName;
public:
    Exception(const std::string& message = "");
    const std::string& what() const;
    virtual const std::string& name() const;
};

class RuntimeError : public Exception {
private:
    static const std::string kName;
public:
    RuntimeError(const std::string& message = "");
    virtual const std::string& name() const;
};

class LogicError : public Exception {
private:
    static const std::string kName;
public:
    LogicError(const std::string& message = "");
    virtual const std::string& name() const;
};

#endif // EXCEPTION_H

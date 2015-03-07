#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include <stdexcept>
#include <string>

class I2CException : public std::runtime_error
{
public:
    explicit I2CException(const std::string& what)
        : std::runtime_error{what} {}

    explicit I2CException(const char* what)
        : std::runtime_error{what} {}
};

class LogReaderException : public std::runtime_error
{
public:
    explicit LogReaderException(const std::string& what)
        : std::runtime_error{what} {}

    explicit LogReaderException(const char* what)
        : std::runtime_error{what} {}
};

#endif

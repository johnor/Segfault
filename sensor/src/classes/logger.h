#ifndef LOG_H_
#define LOG_H_

#include "../headers/smart_pointer_typedefs.h"

#include <fstream>
#include <sstream>
#include <string>

enum class LogLevel
{
	Debug = 0,
	Info,
	Warning,
	Error
};

std::string GetLogLevelString(const LogLevel level);

class Logger
{
public:
    static LogStreamPtr Log(const LogLevel level = LogLevel::Debug);
    static void Log(const std::string& message, const LogLevel level = LogLevel::Debug);

    static LogStreamPtr LogToFile(const LogLevel level = LogLevel::Debug);
    static void LogToFile(const std::string& message, const LogLevel level = LogLevel::Debug);

    static LogStreamPtr LogToConsole(const LogLevel level = LogLevel::Debug);
    static void LogToConsole(const std::string& message, const LogLevel level = LogLevel::Debug);

    static void SetLogFile(const std::string& fileName);
private:
    static std::string FormatMessage(const std::string& message, const LogLevel level);
    static void WriteMessageToConsole(const std::string& message);
    static void WriteMessageToFile(const std::string& message);

    static std::ofstream fileStream;
};

class LogStream : public std::ostringstream
{
public:
    virtual ~LogStream() {}
protected:
    explicit LogStream(const LogLevel level);
    const LogLevel logLevel;
private:
    LogStream(const LogStream&) = delete;
    LogStream& operator=(const LogStream&) = delete;
};

class ConsoleLogStream : public LogStream
{
public:
    explicit ConsoleLogStream(const LogLevel level);
    virtual ~ConsoleLogStream();
private:
    ConsoleLogStream(const ConsoleLogStream&) = delete;
    ConsoleLogStream& operator=(const ConsoleLogStream&) = delete;
};

class FileLogStream : public LogStream
{
public:
    explicit FileLogStream(const LogLevel level);
    virtual ~FileLogStream();
private:
    FileLogStream(const FileLogStream&) = delete;
    FileLogStream& operator=(const FileLogStream&) = delete;
};

class FileAndConsoleLogStream : public LogStream
{
public:
    explicit FileAndConsoleLogStream(const LogLevel level);
    virtual ~FileAndConsoleLogStream();
private:
    FileAndConsoleLogStream(const FileAndConsoleLogStream&) = delete;
    FileAndConsoleLogStream& operator=(const FileAndConsoleLogStream&) = delete;
};

template<typename T>
const LogStreamPtr& operator<<(const LogStreamPtr& lhs, const T& rhs)
{
    *lhs << rhs;
    return lhs;
}

#endif

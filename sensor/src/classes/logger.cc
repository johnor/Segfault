#include "logger.h"
#include <iostream>

std::string GetLogLevelString(const LogLevel level)
{
    switch (level)
    {
    case LogLevel::Debug:
        return "Debug";
    case LogLevel::Info:
        return "Info";
    case LogLevel::Warning:
        return "Warning";
    case LogLevel::Error:
        return "Error";
    default:
        return "";
    }
}

/* ------------------- LOGGER ------------------- */

LogStreamPtr Logger::Log(const LogLevel level)
{
    LogStreamPtr streamPtr{new FileAndConsoleLogStream{level}};
    return streamPtr;
}

void Logger::Log(const std::string& message, const LogLevel level)
{
    const std::string formattedMessage{FormatMessage(message, level)};
    if (level >= LogLevel::Warning)
    {
        WriteMessageToFile(formattedMessage);
        WriteMessageToConsole(formattedMessage);
    }
}

LogStreamPtr Logger::LogToFile(const LogLevel level)
{
    LogStreamPtr streamPtr{new FileLogStream{level}};
    return streamPtr;
}

void Logger::LogToFile(const std::string& message, const LogLevel level)
{
    WriteMessageToFile(FormatMessage(message, level));
}

LogStreamPtr Logger::LogToConsole(const LogLevel level)
{
    LogStreamPtr streamPtr{new ConsoleLogStream{level}};
    return streamPtr;
}

void Logger::LogToConsole(const std::string& message, const LogLevel level)
{
    WriteMessageToConsole(FormatMessage(message, level));
}

void Logger::SetLogFile(const std::string& fileName)
{
    fileStream.close();
    fileStream.open(fileName);
}

std::string Logger::FormatMessage(const std::string& message, const LogLevel level)
{
    std::ostringstream stream;
    stream << '[' << GetLogLevelString(level) << "]: " << message << '\n';
    return stream.str();
}

void Logger::WriteMessageToConsole(const std::string& message)
{
    std::cout << message;
}

void Logger::WriteMessageToFile(const std::string& message)
{
    fileStream << message;
}

std::ofstream Logger::fileStream{"log.txt"};

/* ------------------- LOG STREAM ------------------- */

LogStream::LogStream(const LogLevel level)
    : logLevel{level}
{
}

ConsoleLogStream::ConsoleLogStream(const LogLevel level)
    : LogStream{level}
{
}

ConsoleLogStream::~ConsoleLogStream()
{
    Logger::LogToConsole(str(), logLevel);
}

FileLogStream::FileLogStream(const LogLevel level)
    : LogStream{level}
{
}

FileLogStream::~FileLogStream()
{
    Logger::LogToFile(str(), logLevel);
}

FileAndConsoleLogStream::FileAndConsoleLogStream(const LogLevel level)
    : LogStream{level}
{
}

FileAndConsoleLogStream::~FileAndConsoleLogStream()
{
    Logger::Log(str(), logLevel);
}

#include "logger.h"
#include <iostream>

/* Log stream */
LogStream::LogStream(Logger& logger_, const LogLevel level_) :
std::ostringstream{}, logger(logger_), level(level_)
{
}

LogStream::LogStream(const LogStream& ls) :
std::basic_ios<char>{}, std::ostringstream{}, logger(ls.logger), level(ls.level)
{
}

LogStream::~LogStream()
{
    logger.FormatMessageAndLog(level, str());
}

/* Logger implementation */
std::string Logger::rootLoggerFilename = "log.txt";

Logger::Logger(const std::string &filename)
{
    fileStream.open(filename);
    fileStream << "Logger created!" << std::endl;
}

void Logger::SetRootLoggerFilename(const std::string &filename)
{
    rootLoggerFilename = filename;
}

LogStream Logger::Log()
{
	auto logger = Logger::GetRootInstance();
	return LogStream(*logger, LogLevel::Info);
}

LogStream Logger::Log(const LogLevel level)
{
	auto logger = Logger::GetRootInstance();
	return LogStream(*logger, level);
}


LogStream Logger::operator()()
{
    return LogStream(*this, LogLevel::Info);
}

LogStream Logger::operator()(const LogLevel level)
{
    return LogStream(*this, level);
}


/* Logger private function implementations */
Logger::Logger()
{
	fileStream.open(rootLoggerFilename);
	fileStream << "Logger created!" << std::endl;
}

void Logger::WriteMessageToFile(const std::string &message)
{
    fileStream << message << std::endl;
    std::cout << message << std::endl;
}

void Logger::FormatMessageAndLog(const LogLevel level, const std::string &message)
{
    std::stringstream fullMessage;
    fullMessage << "[" << GetStringFromLogLevel(level) << "] ";
    fullMessage << message;

    WriteMessageToFile(fullMessage.str());
}

std::shared_ptr<Logger>& Logger::GetRootInstance()
{
	static std::shared_ptr<Logger> instance = nullptr;

	if (instance == nullptr)
	{
		instance = std::shared_ptr<Logger>{new Logger};
	}
	return instance;
}

std::string Logger::GetStringFromLogLevel(const LogLevel level)
{
	std::string res;

	switch (level)
	{
	case LogLevel::Debug:
		res = "Debug";
		break;
	case LogLevel::Error:
		res = "Error";
		break;
	case LogLevel::Info:
		res = "Info";
		break;
	case LogLevel::Warning:
		res = "Warning";
		break;
	default:
		return "";
	}
	return res;
}

